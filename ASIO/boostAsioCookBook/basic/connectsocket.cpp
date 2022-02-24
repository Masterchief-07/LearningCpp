#include <iostream>
#include <boost/asio.hpp>

int main()
{
	//target address
	std::string hostname = "www.google.com";
	std::string hostport = "80";

	//error handler
	boost::system::error_code ec;

	//creation du service
	boost::asio::io_service io_svc;

	//recuperation de l'ip address
	boost::asio::ip::tcp::resolver resolver{io_svc};
	boost::asio::ip::tcp::resolver::query query{hostname, hostport};
	boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query, ec);
	if(ec)
	{
		std::cout<<"Failed to resolve "<<hostname<<" address error_code: "<<ec.value()<<" Message: "<<ec.message()<<std::endl;
		return ec.value();
	}
	boost::asio::ip::tcp::endpoint endpoint = iterator->endpoint();
	//print endpoint
	std::cout<<"endpoint: "<<endpoint<<"\n";

	//creation d'un active socket
	boost::asio::ip::tcp::socket socket{io_svc, endpoint.protocol()};

	//connection au port
	//socket.connect(endpoint, ec);
	boost::asio::connect(socket, iterator);

	if(ec)
	{
		std::cout<<"Failed to connect Error code: "<<ec.value()<<" Message: "<<ec.message()<<std::endl;
		return ec.value();
	}

	return 0;
}


