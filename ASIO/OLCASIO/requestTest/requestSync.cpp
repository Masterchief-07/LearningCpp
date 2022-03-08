#include<iostream>
#include<boost/asio.hpp>
#include<vector>
#include<chrono>

using namespace boost;

int main()
{
	try
	{
		asio::io_context io_context;

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

		std::string request = "GET /index.html HTTP/1.1\r\nHost: example.com\r\nConnection: close\r\n\r\n";
	
		asio::write(socket, asio::buffer(request), ec);
		if(ec)
		{
			std::cerr<<"Erro code: "<<ec.value()<<" Message: "<<ec.message()<<std::endl;
			socket.close();
			return ec.value();
		}

		socket.wait(socket.wait_read);
		size_t bytes = socket.available();
		std::cout<<"Bytes available: "<<bytes<<"\n";
		if(bytes>0)
		{
			std::vector<char> vbuffer(bytes);
			asio::read(socket, asio::buffer(vbuffer), ec);

			for(auto c: vbuffer)
				std::cout<< c;
		}
	}
	catch(std::exception& ex)
	{
		std::cerr<<"Error "<<" Message: "<<ex.what()<<std::endl;
		return 1;
	}

	return 0;
}
