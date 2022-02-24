#include<iostream>
#include <boost/asio.hpp>

int main()
{

	unsigned short portnum = 3333;

	//error handler
	boost::system::error_code ec;

	//creation du IO service
	boost::asio::io_service io_svc;

	//creation du endpoint
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address_v4::any(), portnum);
	
	//creation du socket
	boost::asio::ip::tcp::acceptor acceptor{io_svc};
	acceptor.open(endpoint.protocol());

	//connecter
	acceptor.bind(endpoint, ec);

	//test error
	if(ec)
	{
		std::cout<<"Failed to bind the acceptor socket. Error code: "<<ec.value()<<" Message: "<<ec.message()<<"\n";
		return ec.value();
	}

	std::cout<<"endpoint: "<<endpoint<<"\n";
	return 0;
}
