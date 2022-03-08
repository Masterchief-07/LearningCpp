/* server side
 * simple client to server chat app
 * using asio
*/

#include<iostream>
#include<thread>
#include <boost/asio.hpp>
#include <chrono>

using namespace boost;
using asio::ip::tcp;

int main()
{
	const std::string address = "127.0.0.1";
	const unsigned short port = 3333;
	try
	{
		//creation of the context
		asio::io_context ctx;

		//creation of server endpoint
		tcp::endpoint endpoint{asio::ip::address::from_string(address), port};

		//creation of the acceptor
		tcp::acceptor acceptor{ctx, endpoint};

		//connecting the server to a client
		tcp::socket socket{ctx};
		acceptor.accept(socket);
		std::cout<<"connected "<<socket.remote_endpoint()<<"\n";
	
		while(1)
		{
			//read
			asio::streambuf buff;
			asio::read_until(socket, buff, "\n");
			std::string read;
			std::istream reader(&buff);
			std::getline(reader, read);
			std::cout<<"client: "<<read<<"\n";
			if(read == "end")
				break;
			//write
			std::string message;
			std::cout<<"server: ";
			std::getline(std::cin, message);
			asio::write(socket, asio::buffer(message+"\n"));
			if(message == "end")
				break;

		}
		//shutdown the connection
		system::error_code ec;
		socket.shutdown(tcp::socket::shutdown_both,ec);
		socket.close(ec);
		ctx.stop();
	}
	catch(boost::system::system_error& e)
	{
		std::cerr<<"ERROR CODE: "<<e.code()<<" Message: "<<e.what()<<std::endl;
	}

	return 0;
}
