//creation d'un simple client

#include <iostream>
#include <boost/asio.hpp>
#include <array>

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
	if(argc<2)
	{
		std::cerr<<"client <ip>"<<std::endl;
		return 1;
	}

	boost::asio::io_context io_context;
	tcp::resolver resolver{io_context};
	tcp::resolver::results_type endpoint = resolver.resolve(argv[1], "3333");
	tcp::socket socket{io_context};

	boost::system::error_code ec;
	boost::asio::connect(socket, endpoint, ec);


	if(ec)
	{
		std::cerr<<"connect error: "<<ec.value()<<" Message: "<<ec.message()<<std::endl;
		return 1;
	}

	std::cout<<"connected"<<std::endl;

	std::array<char, 128> receiveread{0};
	boost::asio::read(socket, boost::asio::buffer(receiveread), ec);
	std::cout.write(receiveread.data(), receiveread.size());

	return 0;
}


