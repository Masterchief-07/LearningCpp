#include<iostream>
#include<boost/asio.hpp>
#include <string>
using namespace boost;
using boost::asio::ip::tcp;
class SyncTCPClient
{
	public:
		SyncTCPClient(const std::string& raw_ip_address, const unsigned short portnum):m_ep(boost::asio::ip::address::from_string(raw_ip_address), portnum), m_sock(m_ios)
		{
			m_sock.open(m_ep.protocol());
		}

		void connect()
		{
			m_sock.connect(m_ep);
		}

		void close()
		{
			m_sock.shutdown(tcp::socket::shutdown_both);
			m_sock.close();
		}

		std::string emulateLongComputationOp(unsigned int duration)
		{
			std::string request = "EMULATE_LONG_COMP_OP" + std::to_string(duration) +"\n";
			sendRequest(request);
			
			return receiveResponse();
		}

	private:
		void sendRequest(const std::string& request)
		{
			boost::asio::write(m_sock, asio::buffer(request));
		}

		std::string receiveResponse()
		{
			boost::asio::streambuf buff;
			boost::asio::read_until(m_sock, buff, '\n');
			
			std::istream input(&buff);
			std::string response;
			std::getline(input, response);

			return response;
		}

		boost::asio::io_service m_ios;
		tcp::endpoint m_ep;
		tcp::socket m_sock;
};
			



int main()
{
	const std::string raw_ip_address = "127.0.0.1";
	const unsigned short port_num = 3333;

	try
	{
		SyncTCPClient client(raw_ip_address, port_num);

		client.connect();

		std::cout<<"sending request to server...\n";
		std::string response = client.emulateLongComputationOp(10);

		std::cout<<"response receive: "<<response<<"\n";

		client.close();
	}
	catch(system::system_error ec)
	{
		std::cerr<<"ERROR code: "<<ec.code()<<" message: "<<ec.what()<<std::endl;
		return ec.code().value();
	}

	return 0;
}
