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