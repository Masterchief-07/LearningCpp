//try asio concurrent
//
#include <iostream>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

auto main() -> int
{
	boost::asio::io_service io_svc; //gestion du IO(InputOutput)
	boost::shared_ptr<boost::asio::io_service::work> worker{ new boost::asio::io_service::work(io_svc)}; //donne du travail au IO

	worker.reset();

	io_svc.run();

	std::cout<<"we will see this ligne in the console"<<std::endl;
	
	return 0;
}
