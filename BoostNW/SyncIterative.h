#pragma once
#include <boost/asio.hpp>

#include <thread>
#include <atomic>
#include <memory>
#include <iostream>

using namespace boost;

class SIService {
public:
	SIService() {}

	void HandleClient(asio::ip::tcp::socket& sock) {
		try {
			asio::streambuf request;
			asio::read_until(sock, request, '\n');

			std::istream is(&request);
			std::string line;
			std::getline(is, line);
			auto address = sock.remote_endpoint().port();

			std::cout << "Received request from " << line << "on socket " << address << std::endl;
			std::string response = "Response for " + line + "\n";
			while (true) {
				std::this_thread::sleep_for(
					std::chrono::milliseconds(1000));
			}

			asio::write(sock, asio::buffer(response));
		}
		catch (system::system_error &e) {
			std::cout << "Error occured! Error code = "
				<< e.code() << ". Message: "
				<< e.what();
		}
	}
};

class SIAcceptor {
public:
	SIAcceptor(asio::io_service& ios, unsigned short port_num) :
		m_ios(ios),
		m_acceptor(m_ios,
			asio::ip::tcp::endpoint(
				asio::ip::address_v4::any(),
				port_num))
	{
		m_acceptor.listen();
	}

	void Accept() {
		asio::ip::tcp::socket sock(m_ios);
		m_acceptor.accept(sock);
		SIService svc;
		svc.HandleClient(sock);
	}

private:
	asio::io_service& m_ios;
	asio::ip::tcp::acceptor m_acceptor;
};

class SIServer {
public:
	SIServer() : m_stop(false) {}

	void Start(unsigned short port_num) {
		m_thread.reset(new std::thread([this, port_num]() {
			Run(port_num);
		}));
	}

	void Stop() {
		m_stop.store(true);
		m_thread->join();
	}

private:
	void Run(unsigned short port_num) {
		SIAcceptor acc(m_ios, port_num);

		while (!m_stop.load()) {
			acc.Accept();
		}
	}

	std::unique_ptr<std::thread> m_thread;
	std::atomic<bool> m_stop;
	asio::io_service m_ios;
};

int TestSyncIterative()
{
	unsigned short port_num = 3333;

	try {
		SIServer srv;
		srv.Start(port_num);

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