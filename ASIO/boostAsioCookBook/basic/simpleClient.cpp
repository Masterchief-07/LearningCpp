#include <iostream>
#include <string>
#include <boost/asio.hpp>


int main()
{
	//creation du service
	boost::asio::io_service io_svc;

	//creation du protocol tcp
	boost::asio::ip::tcp protocol= boost::asio::ip::tcp::v4();

	//creation du socket
	boost::asio::ip::tcp::socket sock(io_svc);

	//ouvrir le protocol
	boost::system::error_code ec;
	sock.open(protocol, ec);

	if(ec)
	{
		std::cout<<"Failed to open the socket! error code = "<<ec.value() <<" Message: "<<ec.message();
		return ec.value();
	}

	return 0;
}
