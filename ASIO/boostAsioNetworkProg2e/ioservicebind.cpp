#include<iostream>
#include <boost/bind/bind.hpp>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

void WorkerThread(boost::shared_ptr<boost::asio::io_service> iosvc, int counter)
{
	std::cout<<counter<<"\n";
	iosvc->run();
	std::cout<<"End \n";
}

int main()
{
	boost::shared_ptr<boost::asio::io_service> io_svc{ new boost::asio::io_service };
	boost::shared_ptr<boost::asio::io_service::work> worker{ new boost::asio::io_service::work(*io_svc)};

	std::cout<<"PRESS ENTER TO EXIT"<<std::endl;

	boost::thread_group threads;

	for(int i = 1; i <= 5; ++i)
		threads.create_thread(boost::bind(&WorkerThread, io_svc, i));
	
	std::cin.get();
	
	io_svc->stop();

	threads.join_all();

	return 0;
}
