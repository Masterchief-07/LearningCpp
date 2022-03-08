#include<iostream>
#include<boost/asio.hpp>
#include<vector>
#include<chrono>

using namespace boost;

std::vector<char> vBuffer(1 * 1024);

void GrabSomeData(asio::ip::tcp::socket& socket)
{
	socket.async_read_some(asio::buffer(vBuffer), 
			[&](const std::error_code ec, std::size_t length)
			{
				if(!ec)
				{
					std::cout<<"\n\nRead: "<<length<<" bytes\n\n";
					for(int i=0; i<length; i++)
						std::cout<<vBuffer[i];

					GrabSomeData(socket);
				}
			}
	);
}

int main()
{
	try
	{
		asio::io_context io_context;
		asio::io_context::work work{io_context};
		std::thread thrcontext = std::thread([&]()
							{
								io_context.run();
							});

		system::error_code ec;

		//asio::ip::tcp::endpoint endpoint{asio::ip::make_address("93.184.216.34"), 80};
		asio::ip::tcp::endpoint endpoint{asio::ip::make_address("51.38.81.49"), 80};

		asio::ip::tcp::socket socket{io_context, endpoint.protocol()};

		socket.connect(endpoint, ec);
		if(ec)
		{
			std::cerr<<"Erro code: "<<ec.value()<<" Message: "<<ec.message()<<std::endl;
			return ec.value();
		}
		std::cout<<"Connected.\n";

		GrabSomeData(socket);

		std::string request = "GET /index.html HTTP/1.1\r\nHost: example.com\r\nConnection: close\r\n\r\n";
	
		asio::write(socket, asio::buffer(request), ec);
		if(ec)
		{
			std::cerr<<"Erro code: "<<ec.value()<<" Message: "<<ec.message()<<std::endl;
			socket.close();
			return ec.value();
		}
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(20000ms);

		io_context.stop();

		thrcontext.join();

	}
	catch(std::exception& ex)
	{
		std::cerr<<"Error "<<" Message: "<<ex.what()<<std::endl;
		return 1;
	}

	return 0;
}
