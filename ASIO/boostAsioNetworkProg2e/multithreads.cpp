#include <iostream>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

boost::asio::io_service io_svc;
int a  = 0;

void WorkerThread()
{
	std::cout<<++a<<"\n";
	io_svc.run();
	std::cout<<"End \n";
}

auto main() -> int
{
	boost::shared_ptr<boost::asio::io_service::work> worker{
		new boost::asio::io_service::work(io_svc)};

	std::cout<<"PRESS ENTER TO EXIT\n"<<std::endl;

	boost::thread_group threads;
	for(int i=0; i < 5; i++)
		threads.create_thread(WorkerThread);
	
	std::cin.get();
	io_svc.stop();
	threads.join_all();

}

