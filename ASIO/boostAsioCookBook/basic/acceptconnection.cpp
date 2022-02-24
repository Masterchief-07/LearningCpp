#include<iostream>
#include <boost/asio.hpp>

int main()
{
	//port number
	unsigned short port_num = 80;

	//server endpoint
	boost::asio::ip::tcp::endpoint endpoint{boost::asio::ip::address_v4(), port_num};
	//print endpoint
	std::cout<<"endpoint: "<<endpoint<<std::endl;

	//io service
	boost::asio::io_service io_svc;

	try
	{
		//acceptor socket
		boost::asio::ip::tcp::acceptor acceptor{io_svc, endpoint.protocol()};

		//binding to endpoint
		acceptor.bind(endpoint);

		//listening to incoming connection
		//acceptor.listen(BACKLOG_SIZE);
		acceptor.listen(boost::asio::socket_base::max_connections);

		//creating a active socket
		boost::asio::ip::tcp::socket sock{io_svc};

		//connect an active socket to the client
		acceptor.accept(sock);

		//now we can send or receive data to the client
	}
	catch(boost::system::system_error &e)
	{
		std::cout<<"Error occured! code: "<<e.code()<<" Message: "<<e.what()<<std::endl;
		return e.code().value();
	}

	return 0;
}





