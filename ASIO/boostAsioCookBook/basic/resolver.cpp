#include <iostream>
#include <string>
#include <boost/asio.hpp>


int main()
{
	try
	{
		std::string host = "www.google.com";
		std::string port = "80";	

		boost::asio::io_service io_svc;

		boost::asio::ip::tcp::resolver resolver{io_svc};
		
		boost::asio::ip::tcp::resolver::query query(host, port, boost::asio::ip::tcp::resolver::query::numeric_service);

		boost::system::error_code ec;

		boost::asio::ip::tcp::resolver::iterator it = resolver.resolve(query, ec);
		
		boost::asio::ip::tcp::resolver::iterator it_end;
		if(ec)
		{
			std::cout<<"Failed to resole Error: "<<ec.value()<<" Message: "<<ec.message()<<std::endl;
			return ec.value();
		}
		for(; it!= it_end; ++it)
			std::cout<<host<<" IP: "<<it->endpoint()<<std::endl;

		return 0;
	}
	catch(std::exception &ex)
	{
		std::cout<<"error: "<<ex.what()<<std::endl;
		return -1;
	}
}
