#include <iostream>
#include <boost/asio.hpp>
#include <array>

int main(int argc, char* argv[])
{
	try
	{
		if(argc != 2)
		{
			std::cerr<<"Usage: client <host>"<<std::endl;
			return 1;
		}

		//creation du context
		boost::asio::io_context io_context;

		//creation du resolver
		boost::asio::ip::tcp::resolver resolver{io_context};
		//creation du endpoint
		boost::asio::ip::tcp::resolver::results_type endpoints= resolver.resolve(argv[1], "daytime");

		//connect socket
		boost::asio::ip::tcp::socket  socket{io_context};
		boost::asio::connect(socket, endpoints);
		
		//receive data
		for(;;)
		{	
			std::array<char, 128>buf;
			boost::system::error_code  ec;
			size_t len = socket.read_some(boost::asio::buffer(buf), ec);

			//test error
			if(ec == boost::asio::error::eof)
				break;
			else if(ec)
				throw boost::system::system_error(ec);

			std::cout.write(buf.data(), len);
		}
	}
	catch(std::exception& ex)
	{
		std::cerr<<ex.what()<<std::endl;
	}	

	return 0;
}
