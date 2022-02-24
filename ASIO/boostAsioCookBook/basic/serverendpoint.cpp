#include<iostream>
#include<boost/asio.hpp>

int main()
{
	//allocation manuel du port 
	unsigned short port_num = 3333;

	//allocation automatique d'une address libre qu'on peut utiliser comme server
	boost::asio::ip::address ip_address = boost::asio::ip::address_v6::any();

	//creation du endpoint server
	boost::asio::ip::tcp::endpoint ep(ip_address, port_num);

	std::cout<<"endpoint: "<<ep<<".\n";

	return 0;
}


