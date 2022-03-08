/* client side
 * simple client to server chat app
 * using asio
 */

#include<iostream>
#include<thread>
#include <boost/asio.hpp>

using namespace boost;
using asio::ip::tcp;

int main()
{
	const std::string address = "127.0.0.1";
	const unsigned short port = 3333;
	try
	{
		//io_context
		asio::io_context ctx;

		//the endpoint to the server
		tcp::endpoint endpoint(asio::ip::address::from_string(address), port);

		//the socket
		tcp::socket socket{ctx, endpoint.protocol()};
		
		//connecting the socket to the endpoint
		socket.connect(endpoint);
		std::cout<<"connected: "<<endpoint<<"\n";
		
		while(1)
		{
			//write
			std::string message;
			std::cout<<"client: ";
			std::getline(std::cin, message);
			asio::write(socket, asio::buffer(message +"\n"));
			if(message == "end")
				break;

			//read
			asio::streambuf buff;
			asio::read_until(socket, buff, "\n");
			std::string read;
			std::istream reader(&buff);
			std::getline(reader, read);
			std::cout<<"server: "<<read<<"\n";
			if(read == "end")
				break;

		}

		//shutdown the connection
		system::error_code ec;
		socket.shutdown(tcp::socket::shutdown_both, ec);
		socket.close(ec);
		ctx.stop();
	}
	catch(boost::system::system_error& e)
	{
		std::cerr<<"ERROR CODE: "<<e.code()<<" Message: "<<e.what()<<std::endl;
	}

	return 0;
}
