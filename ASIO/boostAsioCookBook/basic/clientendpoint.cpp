#include<iostream>
#include<boost/asio.hpp>

int main()
{
	std::string raw_ip_address = "127.0.0.1";
	unsigned short port_num = 3333;

	boost::system::error_code ec;

	boost::asio::ip::address ip_address = boost::asio::ip::address::from_string(raw_ip_address, ec);

	if(ec)
	{
		std::cout<<"FAILED TO PARSE THE IP ADDRESS, ERROR CODE" <<ec.message();
		return ec.value();
	}

	boost::asio::ip::tcp::endpoint ep(ip_address, port_num);

	return 0;
}


