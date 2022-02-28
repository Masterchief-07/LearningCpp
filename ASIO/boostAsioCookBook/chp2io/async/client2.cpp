#include<boost/asio.hpp>
#include <iostream>
#include <thread>


using boost::asio::ip::tcp;

int main()
{
	std::string raw_ip_address = "127.0.0.1";
	unsigned short port = 3333;

	try
	{
	boost::asio::io_context io_svc;

	tcp::endpoint endpoint{boost::asio::ip::address::from_string(raw_ip_address), port};

	std::shared_ptr<tcp::socket> sock {new tcp::socket{io_svc, endpoint.protocol()}};

	sock->async_connect(endpoint, [sock](boost::system::error_code ec)
			{
				if(ec)
				{
					if(ec == boost::asio::error::operation_aborted)
						std::cerr<<"Operation Cancelled\n";

					else
					{
						std::cerr<<"Error occured: "<<ec.value()<<" Message"<<ec.message()<<std::endl;
					}
					return ;
				}
			});

	std::thread worker_thread([&io_svc]()
			{
				try
				{
					io_svc.run();
				}
				catch(boost::system::system_error &e)
				{
					std::cerr<<"Error occured: "<<e.code()<<" Message: "<<e.what()<<"\n";
				}
			});

	std::this_thread::sleep_for(std::chrono::seconds(2));

	sock->cancel();

	worker_thread.join();
	
	}
	catch(boost::system::system_error &e)
	{
		std::cerr<<"Error occured: "<<e.code()<<" Message: "<<e.what()<<"\n";
		return e.code().value();
	}

	return 0;
}




