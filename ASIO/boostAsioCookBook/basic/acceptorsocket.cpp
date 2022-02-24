#include <iostream>
#include <boost/asio.hpp>


int main()
{

	boost::asio::io_service io_svc;

	boost::asio::ip::tcp protocol = boost::asio::ip::tcp::v6();

	boost::asio::ip::tcp::acceptor acceptor{io_svc};

	boost::system::error_code ec;

	acceptor.open(protocol, ec);

	if(ec)
	{
		std::cout<<"FAILED TO OPEN THE ACCEPTOR SOCKET"<< " ERROR CODE: "<<ec.value() <<" Message: "<<ec.message()<<std::endl;

		return ec.value();
	}


	return 0;

}
