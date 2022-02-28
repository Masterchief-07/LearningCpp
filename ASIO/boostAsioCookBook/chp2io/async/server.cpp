#include<iostream>
#include<boost/asio.hpp>

using boost::asio::ip::tcp;

struct Session
{
	std::shared_ptr<tcp::socket> sock;
	std::unique_ptr<char[]> buff;
	size_t total_bytes_read;
	unsigned int buff_size;	

};

void callback(const boost::system::error_code &ec, size_t bytes_transfered, std::shared_ptr<Session> s)
{
	if(ec)
	{
		std::cerr<<"Error occured! Error code = "<<ec.value()<<" Message: "<<ec.message()<<std::endl;
		return;
	}
	
	s->total_bytes_read += bytes_transfered;

	if(s->total_bytes_read == s->buff_size)
		return;

	s->sock->async_read_some(boost::asio::buffer(s->buff.get()+s->total_bytes_read, s->buff_size - s->total_bytes_read), std::bind(callback, std::placeholders::_1, std::placeholders::_2, s));
}

void callback2(const boost::system::error_code &ec, size_t bytes_transfered)
{
	if(ec)
	{
		std::cerr<<"Error occured! Error code = "<<ec.value()<<" Message: "<<ec.message()<<std::endl;
		return;
	}

	std::cout<<"received"<<"\n";	
}
void readFromSocket(std::shared_ptr<tcp::socket> sock)
{
	const unsigned int MESSAGE_SIZE = 7;

	std::shared_ptr<Session> s{new Session};
	s->sock = sock;
	s->buff.reset(new char[MESSAGE_SIZE]);
	s->total_bytes_read = 0;
	s->buff_size = MESSAGE_SIZE;

	s->sock->async_read_some(boost::asio::buffer(s->buff.get(), s->buff_size), std::bind(callback, std::placeholders::_1, std::placeholders::_2, s)); 
	std::cout.write(s->buff.get(), s->buff_size);
}
void readFromSocketAdvance(std::shared_ptr<tcp::socket> sock)
{
	const unsigned int MESSAGE_SIZE = 7;

	std::shared_ptr<Session> s{new Session};
	s->sock = sock;
	s->buff.reset(new char[MESSAGE_SIZE]);
	s->total_bytes_read = 0;
	s->buff_size = MESSAGE_SIZE;

	boost::asio::async_read(*s->sock, boost::asio::buffer(s->buff.get(), s->buff_size), std::bind(callback2, std::placeholders::_1,std::placeholders::_2));

	std::cout.write(s->buff.get(), s->buff_size);
}


int main(int argc, char *argv[])
{

	//creation du context
	boost::asio::io_context io_context;
	//creation du endpoint
	tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 3333);
	std::cout<<"server: "<<endpoint<<"\n";
	//creation du server socket
	tcp::acceptor acceptor{io_context, endpoint};

	boost::system::error_code ec;
	std::shared_ptr<tcp::socket> socket{new tcp::socket{io_context}};
	acceptor.accept(*socket, ec);
	
	if(ec)
	{
		std::cerr<<"failed to connect"<<std::endl;
		return -1;	
	}
	std::cout<<"connected"<<std::endl;

	readFromSocketAdvance(socket);
	return 0;
}
