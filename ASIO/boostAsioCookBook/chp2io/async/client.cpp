//creation d'un simple client

#include <iostream>
#include <boost/asio.hpp>
#include <array>

using boost::asio::ip::tcp;

struct Session
{
	std::shared_ptr<tcp::socket> sock;
	std::string buff;
};

void callback(const boost::system::error_code& ec, size_t bytes_transfered, std::shared_ptr<Session> s)
{
	if(ec)
	{
		std::cerr<<"Callback Error, Errorcode = "<<ec.value()<<" Message: "<<ec.message()<<std::endl;
		return;
	}
	std::cout<<"message sended"<<std::endl;
	
}

void writeToSocket(std::shared_ptr<tcp::socket> sock)
{
	std::shared_ptr<Session> s(new Session);

	s->buff = std::string("hello");
	s->sock = sock;

	boost::asio::async_write(*sock, boost::asio::buffer(s->buff), std::bind(callback, std::placeholders::_1, std::placeholders::_2, s));
}



int main(int argc, char* argv[])
{
	std::string raw_ip_address = "127.0.0.1";
	unsigned short port_num = 3333;

	try
	{
		tcp::endpoint ep(boost::asio::ip::address::from_string(raw_ip_address), port_num);

		boost::asio::io_context io_svc;

		std::shared_ptr<tcp::socket> sock{new tcp::socket{io_svc, ep.protocol()}};

		sock->connect(ep);

		writeToSocket(sock);

		io_svc.run();
	}
	catch(std::exception& ex)
	{
		std::cerr<<"error: "<<ex.what()<<std::endl;
		return 1; 
	}

	return 0;
}
