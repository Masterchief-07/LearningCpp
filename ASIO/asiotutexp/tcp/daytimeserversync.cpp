
#include <ctime>
#include<iostream>
#include<boost/asio.hpp>
#include <string>
using boost::asio::ip::tcp;

std::string make_daytime_string()
{
	using namespace std;
	time_t now  = time(0);
	return ctime(&now);
}

int main()
{
	try
	{
		//creation du context
		boost::asio::io_context io_context;

		//creation du acceptor, ou server socket
		tcp::endpoint endpoint{tcp::v4(), 13};
		tcp::acceptor acceptor{io_context, endpoint};

		std::cout<<"server created: "<<endpoint<<"\n";

		for(;;)
		{
			//creation du active socket, qui va permet de relier le server au client
			tcp::socket socket{io_context};
			acceptor.accept(socket);
			//message envoyer au client a chaque connexion
			std::string message = "hello the time is: " + make_daytime_string();

			boost::system::error_code ec;
			//envoie du message
			boost::asio::write(socket, boost::asio::buffer(message), ec);
		}
	}
	catch(std::exception &ex)
	{
		std::cerr<<ex.what()<<std::endl;
	}	
	return 0;
}
