#include <iostream>
#include <boost/asio.hpp>

using namespace boost;
using boost::asio::ip::tcp;


class SyncUDPClient
{
	public:
		//connect to a udp socket
		SyncUDPClient(): m_sock(m_ios)
		{
			m_sock.open(asio::ip::udp::v4());
		}

		std::string emulateLongComputationOp(const unsigned int duration, const std::string& raw_ip_address, const unsigned short port )
		{
			std::string request = "EMULATE_LONG_OP" + std::to_string(duration) + "\n";

			asio::ip::udp::endpoint ep{asio::ip::address::from_string(raw_ip_address), port};

			sendRequest(ep, request);

			return receiveResponse(ep);
		}

	private:
		void sendRequest(const asio::ip::udp::endpoint& ep, const std::string request)
		{
			m_sock.send_to(asio::buffer(request), ep);
		}

		std::string receiveResponse(asio::ip::udp::endpoint& ep)
		{
			char buff[6];

			auto bytes_received = m_sock.receive_from(asio::buffer(buff), ep);

			m_sock.shutdown(asio::ip::udp::socket::shutdown_both);
			
			return std::string(buff, bytes_received);
		}

		asio::io_context m_ios;
		asio::ip::udp::socket m_sock;
};


int main()
{
	const std::string raw_ip_address = "127.0.0.1";
	const unsigned short port = 3333;
	const std::string raw_ip_address2 = "127.0.0.1";
	const unsigned short port2 = 3333;

	try
	{
		SyncUDPClient client;

		std::cout<<"Sending request Server# 1"<<std::endl;
		std::string response = client.emulateLongComputationOp(10, raw_ip_address, port);
		std::cout<<"Response frome Server#1 "<<response <<std::endl;

		
		std::cout<<"Sending request Server#2"<<std::endl;
		std::string response2 = client.emulateLongComputationOp(10, raw_ip_address2, port2);
		std::cout<<"Response frome Server#2 "<<response2 <<std::endl;
	}
	catch(system::system_error ec)
	{
		std::cerr<<"Error code: "<<ec.code()<<" Message: "<<ec.what()<<std::endl;
		return ec.code().value();
	}

	return 0;
}
