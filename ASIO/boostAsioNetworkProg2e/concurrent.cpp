#include <iostream>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>

void print1()
{
	for(int i = 0; i < 5; i++)
	{
		boost::this_thread::sleep_for(boost::chrono::milliseconds{500});
		std::cout<<"[print1]: "<<i<<"\n";
	}
}
void print2()
{
	for(int i = 0; i < 5; i++)
	{
		boost::this_thread::sleep_for(boost::chrono::milliseconds{500});
		std::cout<<"[print2]: "<<i<<"\n";
	}
}

auto main() -> int
{
	boost::thread_group threads;
	threads.create_thread(print1);
	threads.create_thread(print2);
	threads.join_all();
}
