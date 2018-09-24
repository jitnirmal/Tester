#pragma once
#include <boost/asio.hpp>
#include <iostream>
#include <vector>

using namespace boost;

class SyncTCPClient {
public:
	SyncTCPClient(const std::string& raw_ip_address,
		unsigned short port_num) :
		m_ep(asio::ip::address::from_string(raw_ip_address),
			port_num),
		m_sock(m_ios) {
		m_sock.open(m_ep.protocol());
	}

	void connect() {
		m_sock.connect(m_ep);
	}

	void close() {
		m_sock.shutdown(
			boost::asio::ip::tcp::socket::shutdown_both);
		m_sock.close();
	}

	std::string queryServer(
		unsigned int clientID) {
		std::string request = "Client Request id : "
			+ std::to_string(clientID)
			+ "\n";
		sendRequest(request);
		return receiveResponse();
	};

private:
	void sendRequest(const std::string& request) {
		asio::write(m_sock, asio::buffer(request));
	}

	std::string receiveResponse() {
		asio::streambuf buf;
		asio::read_until(m_sock, buf, '\n');

		std::istream input(&buf);

		std::string response;
		std::getline(input, response);

		return response;
	}

private:
	asio::io_service m_ios;

	asio::ip::tcp::endpoint m_ep;
	asio::ip::tcp::socket m_sock;
};

int TestSyncTCPClient()
{
	const std::string raw_ip_address = "127.0.0.1";
	const unsigned short port_num = 3333;
	auto clientHandler = [&](int clientId) {
		SyncTCPClient client(raw_ip_address, port_num);
		client.connect();
	//	std::cout << "Sending request to the server for clientID : " << clientId << std::endl;
		std::string response = client.queryServer(clientId);
	//	std::cout << "Response received: " << response << std::endl;
		client.close();
	};
	try {
		std::vector<std::thread> ClientThreads;
		const int NumOfClients { 5 } ;
		for (int i = 0; i < NumOfClients; ++i)
		{
			ClientThreads.push_back(std::thread(clientHandler,i));
		}
		for (auto& thread : ClientThreads)
		{
			thread.join();
		}
		
	}
	catch (system::system_error &e) {
		std::cout << "Error occured! Error code = " << e.code()
			<< ". Message: " << e.what();

		return e.code().value();
	}

	return 0;
}