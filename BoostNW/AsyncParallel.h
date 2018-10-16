#pragma once
#include "Common.h"
#include <boost/asio.hpp>
#include <thread>
#include <atomic>
#include <memory>
#include <iostream>
#include <strstream>
#include <mutex>

using namespace boost;

/// <summary>
/// listening server must do
///		1. socket() : creates an endpoint for communication and returns a descriptor.
///					-- AF_INET, address family(IP4, IP6), SOCK_STREAM (TCP), SOCK_DGRAM (UDP)
///		2. bind()	: (HOST, PORT) port should be an integer from 1-65535 (0 is reserved)
///		3. listen() :  It listens for connections from clients. 
///						listen() has a backlog parameter. number of unaccepted connections that OS will allow before refusing new connections
///		4. accept()	; blocking call, When a client connects, the server calls accept() to accept, or complete, the connection.
///					-- accepts return new socket object and it’s the socket used to communicate with the client. 
///						It’s distinct from the listening socket that the server is using to accept new connections:
/// 
///	client 
///		connect() : The client calls connect() to establish a connection to the server and initiate the three-way handshake. 
///					--- client can reach the server and vice-versa. 
///		send()   :  data is exchanged between the client and server 
///		recv()  :  data is exchanged between the client and server 
///		close() : close both client and server
/// 
/// 
/// Viewing Socket State
///		a) netstat -an
///		b) lsof -n | grep TCP | head -4
///		
/// TCP_NODELAY option on the socket, which disables the Nagle algorithm.
/// TCP_CORK option when you're sure that you will be sending multiple data sets together
/// Silly Window Syndrome (SWS) is a problem that can arise in poor implementations of the transmission control protocol (TCP)
///  when the receiver is only able to accept a few bytes at a time or when the sender transmits data in small segments repeatedly.
/// 
/// </summary>
/// 


/// <summary>
///  Boost ASIO : Asio stands for asynchronous input/output
///		Boost.Asio starts asynchronous operations typically used to achieve greater efficiency. 
///		With no need to wait for an operation to finish, a program can perform other tasks in between
///		Boost.Asio for asynchronous data processing are based on 
///			a) I/O services : the operating system API, single global class
///			b) I/O objects : knows its I/O service and task oriented
///				--  boost::asio::ip::tcp::socket
///				--  boost::asio::serial_port
///				-- boost::asio::steady_timer
/// 
/// 
/// 
///		-- Wtih boost::asio::io_service run() the associated handlers are invoked within the same thread. 
///		-- By using multiple threads, a program can call run() multiple times. Once an asynchronous operation is complete, 
///			the I/O service object will execute the handler in one of these threads. 
///		
///		-- On Windows, boost::asio::io_service is usually based on IOCP (I/O Completion Ports)
///					on Linux, it is based on epoll(). 
///		-- Having several I/O service objects means that several I/O completion ports will be used or epoll() will be called multiple times
///			
/// </summary>


class APService {
public:
	APService(std::shared_ptr<asio::ip::tcp::socket> sock) :
		m_sock(sock)
	{
	}

	void StartHandling() {

		asio::async_read_until(*m_sock.get(),
			m_request,'\n',	[this] (const boost::system::error_code& ec, std::size_t bytes_transferred)
		{
			onRequestReceived(ec,bytes_transferred);
		});
	}

private:
	void onRequestReceived(const boost::system::error_code& ec,
		std::size_t bytes_transferred) {
		if (ec.value() != 0) {
			std::cout << "Error occured! Error code = "
				<< ec.value()
				<< ". Message: " << ec.message();

			onFinish();
			return;
		}

		// Process the request.
		m_response = ProcessRequest(m_request);

		// Initiate asynchronous write operation.
		asio::async_write(*m_sock.get(),
			asio::buffer(m_response),
			[this](
				const boost::system::error_code& ec,
				std::size_t bytes_transferred)
		{
			onResponseSent(ec,
				bytes_transferred);
		});
	}

	void onResponseSent(const boost::system::error_code& ec,
		std::size_t bytes_transferred) {
		if (ec.value() != 0) {
			std::cout << "Error occured! Error code = "
				<< ec.value()
				<< ". Message: " << ec.message();
		}

		onFinish();
	}

	// Here we perform the cleanup.
	void onFinish() {
		delete this;
	}

	std::string ProcessRequest(asio::streambuf& request) {
		printer("ProcessRequest");
		std::istream is(&request);
		std::string line;
		std::getline(is, line);
		auto address = m_sock->remote_endpoint().port();

		std::stringstream ss;
		ss << "Received request from " << line << " on socket " <<address;
		printer(ss.str());

		std::string response = "Response for " + line + "\n";
		while (true) {
			std::this_thread::sleep_for(
				std::chrono::milliseconds(1000));
		}

		return response;
	}

private:
	std::shared_ptr<asio::ip::tcp::socket> m_sock;
	std::string m_response;
	asio::streambuf m_request;
};

class APAcceptor {
public:
	APAcceptor(asio::io_service& ios, unsigned short port_num) :
		m_ios(ios),
		m_acceptor(m_ios,
			asio::ip::tcp::endpoint(
				asio::ip::address_v4::any(),
				port_num)),
		m_isStopped(false)
	{}

	// Start accepting incoming connection requests.
	void Start() {
		m_acceptor.listen();
		InitAccept();
	}

	// Stop accepting incoming connection requests.
	void Stop() {
		m_isStopped.store(true);
	}

private:
	void InitAccept() {
		printer("InitAccept");
		std::shared_ptr<asio::ip::tcp::socket>
			sock(new asio::ip::tcp::socket(m_ios));

		m_acceptor.async_accept(*sock.get(),
			[this, sock](
				const boost::system::error_code& error)
		{
			onAccept(error, sock);
		});
	}

	void onAccept(const boost::system::error_code& ec,
		std::shared_ptr<asio::ip::tcp::socket> sock)
	{
		printer("onAccept");
		if (ec.value() == 0) {
			(new APService(sock))->StartHandling();
		}
		else {
			std::cout << "Error occured! Error code = "
				<< ec.value()
				<< ". Message: " << ec.message();
		}

		// Init next async accept operation if
		// acceptor has not been stopped yet.
		if (!m_isStopped.load()) {
			InitAccept();
		}
		else {
			// Stop accepting incoming connections
			// and free allocated resources.
			m_acceptor.close();
		}
	}

private:
	asio::io_service& m_ios;
	asio::ip::tcp::acceptor m_acceptor;
	std::atomic<bool> m_isStopped;
};

class APServer {
public:
	APServer() {
		m_work.reset(new asio::io_service::work(m_ios));
	}

	// Start the server.
	void Start(unsigned short port_num,
		unsigned int thread_pool_size) {

		assert(thread_pool_size > 0);
		std::cout << "starting server" << std::endl;
		// Create and start Acceptor.
		acc.reset(new APAcceptor(m_ios, port_num));
		acc->Start();

		// Create specified number of threads and 
		// add them to the pool.
		for (unsigned int i = 0; i < thread_pool_size; i++) {
			std::unique_ptr<std::thread> th(
				new std::thread([this]()
			{
				m_ios.run();
			}));

			m_thread_pool.push_back(std::move(th));
		}
	}

	// Stop the server.
	void Stop() {
		acc->Stop();
		m_ios.stop();

		for (auto& th : m_thread_pool) {
			th->join();
		}
	}

private:
	asio::io_service m_ios;
	std::unique_ptr<asio::io_service::work> m_work;
	std::unique_ptr<APAcceptor> acc;
	std::vector<std::unique_ptr<std::thread>> m_thread_pool;
};


const unsigned int DEFAULT_THREAD_POOL_SIZE = 2;

int TestAsyncParallel()
{
	unsigned short port_num = 3333;

	try {
		APServer srv;
		printer("server created");
		unsigned int thread_pool_size =
			std::thread::hardware_concurrency() * 2;

		if (thread_pool_size == 0)
			thread_pool_size = DEFAULT_THREAD_POOL_SIZE;

		//srv.Start(port_num, 1);
		srv.Start(port_num, thread_pool_size);

		std::this_thread::sleep_for(std::chrono::seconds(60));

		srv.Stop();
	}
	catch (system::system_error &e) {
		std::cout << "Error occured! Error code = "
			<< e.code() << ". Message: "
			<< e.what();
	}

	return 0;
}