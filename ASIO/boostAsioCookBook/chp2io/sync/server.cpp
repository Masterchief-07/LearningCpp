#include<iostream>
#include<boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char *argv[])
{

	//creation du context
	boost::asio::io_context io_context;
	//creation du endpoint
	tcp::endpoint endpoint(tcp::v4(), 3333);
	std::cout<<"server: "<<endpoint<<"\n";
	//creation du server socket
	tcp::acceptor acceptor{io_context, endpoint};

	boost::system::error_code ec;
	tcp::socket socket{io_context};
	acceptor.accept(socket, ec);
	
	if(ec)
	{
		std::cerr<<"failed to connect"<<std::endl;
		return -1;	
	}
	std::cout<<"connected"<<std::endl;

	std::string hello{"HELLO WORLD\n"};
	boost::asio::write(socket, boost::asio::buffer(hello), ec);
	return 0;
}
