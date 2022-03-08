#include<boost/asio.hpp>
#include<iostream>
#include<thread>
#include<memory>
#include <mutex>
#include <map>

using namespace boost;
using boost::asio::ip::tcp;
typedef void(*Callback) (unsigned int request_id, const std::string& response, const system::error_code& ec);

struct Session
{
	Session(asio::io_service& ios, const std::string& raw_ip_address, unsigned short port_num, const std::string& request, unsigned int id, Callback callback):m_sock{ios}, m_ep{asio::ip::make_address(raw_ip_address), port_num}, m_request{request}, m_id{id}, m_callback(callback), m_was_cancelled{false}
		{
		}	
	asio::ip::tcp::socket m_sock;
	asio::ip::tcp::endpoint m_ep;
	std::string m_request;

	asio::streambuf m_response_buf;
	std::string m_response;

	system::error_code m_ec;

	unsigned int m_id;

	Callback m_callback;

	bool m_was_cancelled;

	std::mutex m_cancel_guard;

};

class AsyncTCPClient : public boost::asio::noncopyable
{
	public:
		AsyncTCPClient()
		{
			m_work.reset(new boost::asio::io_service::work(m_ios));

			m_thread.reset(new std::thread([this](){
								m_ios.run();
								}));
		}

		void emulateLongComputationOp(unsigned int duration_sec, const std::string& raw_ip_address, unsigned short port_num, Callback callback, unsigned int request_id)
		{
			std::string request  = "EMULATE_LONG_CALC_OP" + std::to_string(duration_sec)+"\n";

			std::shared_ptr<Session> session = std::shared_ptr<Session>(new Session(m_ios, raw_ip_address, port_num, request, request_id, callback));

			session->m_sock.open(session->m_ep.protocol());

			std::unique_lock<std::mutex> lock(m_active_sessions_guard);
			m_active_sessions[request_id] = session;

			lock.unlock();

			session->m_sock.async_connect(session->m_ep, [this, session] (const system::error_code& ec)
					{
						if(ec.value() != 0)
						{
							session->m_ec = ec;
							onRequestComplete(session);
							return;
						}
						std::unique_lock<std::mutex> cancel_lock(session->m_cancel_guard);
						if(session->m_was_cancelled)
						{
							onRequestComplete(session);
							return;
						}
						asio::async_write(session->m_sock, asio::buffer(session->m_request),[this, session](const boost::system::error_code& ec, size_t bytes_transfered)
							{
								if(ec.value() !=0)
								{
									session->m_ec = ec;
									onRequestComplete(session);
									return;
								}
								
								std::unique_lock<std::mutex>cancel_lock(session->m_cancel_guard);

								if(session->m_was_cancelled)
								{
									onRequestComplete(session);
									return;
								}
								asio::async_read_until(session->m_sock, session->m_response_buf, '\n', 
									[this, session](const boost::system::error_code& ec, size_t bytes_transfered)
									{
										if(ec.value() != 0)
										{
											session->m_ec = ec;
										}
										else
										{
											std::istream strm(&session->m_response_buf);
											std::getline(strm, session->m_response);
										}
										onRequestComplete(session);
									});
							});
					});
		};

		void cancelRequest(unsigned int request_id)
		{
			std::unique_lock<std::mutex> lock(m_active_sessions_guard);

			auto it = m_active_sessions.find(request_id);
			if(it != m_active_sessions.end())
			{
				std::unique_lock<std::mutex> cancel_lock(it->second->m_cancel_guard);
				it->second->m_was_cancelled = true;
				it->second->m_sock.cancel();
			}
		}

		void close()
		{
			m_work.reset(NULL);

			m_thread->join();
		}

	private:
		void onRequestComplete(std::shared_ptr<Session> session)
		{
			boost::system::error_code ignored_ec;

			session->m_sock.shutdown(asio::ip::tcp::socket::shutdown_both, ignored_ec);

			std::unique_lock<std::mutex> lock(m_active_sessions_guard);

			auto it = m_active_sessions.find(session->m_id);
			if(it != m_active_sessions.end())
				m_active_sessions.erase(it);

			lock.unlock();

			boost::system::error_code ec;

			if(session->m_ec.value() == 0 && session->m_was_cancelled)
				ec = asio::error::operation_aborted;
			else
				ec = session->m_ec;

			//the callback
			session->m_callback(session->m_id, session->m_response, ec);
		};

	private:
		asio::io_service m_ios;
		std::map<int, std::shared_ptr<Session>> m_active_sessions;
		std::mutex m_active_sessions_guard;
		std::unique_ptr<boost::asio::io_service::work> m_work;
		std::unique_ptr<std::thread> m_thread;
};

void handler(unsigned int request_id, const std::string& response, const system::error_code& ec)
{
	if(!ec)
	{
		std::cout<<"Request #"<<request_id<<" has completed. Response: "<<response<<std::endl;
	}
	else if(ec == asio::error::operation_aborted)
	{
		std::cout<<"Request #"<<request_id<<" has been cancelled by the user."<<std::endl;
	}
	else
	{
		std::cout<<"Request #"<<request_id<<" failed! Error code = "<<ec.value()<<". Error message= "<<ec.message()<<std::endl;
	}
	return;
}

int main()
{
	try{
		AsyncTCPClient client;

		client.emulateLongComputationOp(10, "127.0.0.1", 3333, handler, 1);

		std::this_thread::sleep_for(std::chrono::seconds(5));

		client.emulateLongComputationOp(11, "127.0.0.1", 3334, handler, 2);

		client.cancelRequest(1);

		std::this_thread::sleep_for(std::chrono::seconds(6));
		
		client.emulateLongComputationOp(12, "127.0.0.1", 3335, handler, 3);

		std::this_thread::sleep_for(std::chrono::seconds(15));

		client.close();
	}
	catch(boost::system::system_error& e)
	{
		std::cerr<<"Error occured! Error code = "<<e.code()<<". Message= "<<e.what()<<std::endl;
		return e.code().value();
	}
	return 0;
}
