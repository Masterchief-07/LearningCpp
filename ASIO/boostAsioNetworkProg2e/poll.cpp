#include<iostream>
#include<boost/asio.hpp>

auto main() -> int
{
	boost::asio::io_service io_svc;
	boost::asio::io_service::work work(io_svc); //give work to the io

	for(int i=0; i<5; i++)
	{
		io_svc.poll();
		std::cout<<"line: "<<i<<"\n";
	}
	
}
