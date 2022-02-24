#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>

boost::mutex global_stream_lock;

void WorkerThread(boost::shared_ptr<boost::asio::io_service> iosvc, int counter)
{
	global_stream_lock.lock();
	std::cout<<"Thread"<<counter<<" Start. \n";
	global_stream_lock.unlock();

	while(true)
	{
		try
		{	
			boost::system::error_code ec;
			iosvc->run(ec);
			if(ec)
			{
				global_stream_lock.lock();
				std::cout<<"Error Message: "<<ec<<".\n";
				global_stream_lock.unlock();
			}
			break;
		}
		catch(std::exception &e)
		{
			global_stream_lock.lock();
			std::cout<<"Exception Message: "<<e.what()<<"\n";
			global_stream_lock.unlock();
		}
	}
	global_stream_lock.lock();
	std::cout<<"Thread"<<counter<<" End. \n";
	global_stream_lock.unlock();
}

void TimerHandler(const boost::system::error_code &ec)
{
	if(ec)
	{
		global_stream_lock.lock();
		std::cout<<"Error Message: "<<ec<<".\n";
		global_stream_lock.unlock();
	}
	else
	{
		global_stream_lock.lock();
		std::cout<<"you see this line because you have waited for 10s \n";
		std::cout<<"press Enter to exit\n";
		global_stream_lock.unlock();
	}

}

int main()
{
	boost::shared_ptr<boost::asio::io_service> io_svc{new boost::asio::io_service};
	boost::shared_ptr<boost::asio::io_service::work> worker{ new boost::asio::io_service::work(*io_svc) };
	
	global_stream_lock.lock();
	std::cout<<"wait for 10s to see what happen\n";
	std::cout<<"otherwise press Enter to exit\n";
	global_stream_lock.unlock();

	boost::thread_group threads;
	for(int i=1; i<=5; i++)
		threads.create_thread(boost::bind(&WorkerThread, io_svc, i));

	boost::asio::deadline_timer timer{*io_svc};
	timer.expires_from_now(boost::posix_time::seconds(10));
	timer.async_wait(TimerHandler);
	
	std::cin.get();

	io_svc->stop();

	threads.join_all();

	return 0;
}


