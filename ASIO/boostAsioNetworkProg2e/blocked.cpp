//try asio concurrent
//
#include <iostream>
#include <boost/asio.hpp>

auto main() -> int
{
	boost::asio::io_service io_svc; //gestion du IO(InputOutput)
	boost::asio::io_service::work worker(io_svc); //donne du travail au IO

	std::cout<<"we will see this ligne in the console"<<std::endl;
	
	return 0;
}
