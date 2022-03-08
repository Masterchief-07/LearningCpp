#pragma once

#include "net_common.h"
#include "net_message.h"
#include "net_tsqueue.h"
#include "net_connection.h"

namespace olc
{
	namespace net
	{
		template<typename T>
		class client_interface
		{
			public:
				client_interface() : m_socket(m_context)
				{

				}

				virtual ~client_interface()
				{
					Disconnect();
				}


			public:
				//connect to server with hostname/ip-address and port
				bool Connect(const std::string& host, const uint16_t port)
				{
					try
					{
						//create connection
						m_connection = std::unique_ptr<connection<T>>();

						//resolve hostname
						asio::ip::tcp::resolver resolver(m_context);
						m_endpoints = resolver.resolve(host, std::to_string(port));
				
						//connect to the server
						m_connection->ConnectToServer(m_endpoints);

						//start Context Thread
						thrContext = std::thread([this]() { m_context.run();});
					}
					catch(std::exception& e)
					{
						std::cerr<<"Client Exception: "<<e.what()<<"\n";
						return false;
					}
					return true;

				}

				//disconnect from server
				void Disconnect()
				{
					if(IsConnected())
						m_connection->Disconnect();

					m_context.stop();

					if (thrContext.joinable())
						thrContext.join();

					m_connection.release();

				}

				//check if the client is actualy connected
				bool IsConnected()
				{
					if(m_connection)
						return m_connection->IsConnected();
					else
						return false;

				}

				//retrieve queue of message from server
				tsqueue<owned_message<T>>& Incoming()
				{
					return m_qMessagesIn;
				}

			protected:
				//asio context
				asio::io_context m_context;
				//thread to execute the context
				std::thread thrContext;
				//socket 
				asio::ip::tcp::socket m_socket;
				//endpoints
				asio::ip::tcp::resolver::iterator m_endpoints;
				//connection object
				std::unique_ptr<connection<T>> m_connection;
				
			private:
				tsqueue<owned_message<T>> m_qMessagesIn;
		};
	}
}
