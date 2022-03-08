#pragma once
#include "net_common.h"

namespace olc
{
	namespace net
	{
		//Message header is set a start of all messages.
		template<typename T>
		struct message_header
		{
			T id{};
			uint32_t size = 0;
		};


		template<typename T>
		struct message
		{
			message_header<T> header{};
			std::vector<uint8_t> body;
	
			//return the size of the entire message packet in bytes
			size_t size() const
			{
				return sizeof(message_header<T>) + body.size();
			}

			//creation of a compatibility with cout for describing the message
			friend std::ostream& operator << (std::ostream& os, const message<T>& msg)
			{
				os<<"ID: "<<int(msg.header.id)<<" Size: "<<msg.header.size;
				return os;
			}

			//push any POD-like data into the message buffer;
			template<typename DataType>
			friend message<T>& operator << (message<T>& msg, const DataType& data)
			{
				//check if the data being pushed is trivially copyable
				static_assert(std::is_standard_layout<DataType>::value, "Data is too Complex");

				//cache current size of vector
				size_t i  = msg.body.size();

				//resize vector to receive the data
				msg.body.resize(msg.body.size() + sizeof(DataType));

				//physically copy the data
				std::memcpy(msg.body.data() + i, &data, sizeof(DataType));

				//recalculate the message size();
				msg.header.size = msg.size();

				return msg;
			}

			//extract data from the message buffer;
			template<typename DataType>
			friend message<T>& operator >> (message<T>& msg, DataType& data)
			{
				//check if the data being pushed is trivially copyable
				static_assert(std::is_standard_layout<DataType>::value, "Data is too Complex");

				//Cache the location towards the end of the vector
				size_t i = msg.body.size() - sizeof(DataType);
				
				//physically copy the data from vector to user variable
				std::memcpy(&data, msg.body.data()+i, sizeof(DataType));

				//shrink the vector
				msg.body.resize(i);
				
				//recalculate the message size();
				msg.header.size = msg.size();

				//return target msg
				return msg;
			}

		};


		template<typename T>
		class connection;


		template<typename T>
		struct owned_message
		{
			std::shared_ptr<connection<T>> remote = nullptr;
			message<T> msg;

			//string maker
			friend std::ostream& operator << (std::ostream& os, const owned_message<T>& msg)
			{
				os << msg.msg;
				return os;
			}
		};
	}
}

