#pragma once

#include <net_common.h>

namespace olc
{
	namespace net
	{
		template<typename T>
		class tsqueue
		{
			public:
				tsqueue() = default;
				tsqueue(const tsqueue<T>&) = delete;

			public:
				//return item at the front of the queue
				const T& front()
				{
					std::scoped_lock lock(muxQueue);
					return deqQueue.front();
				}
				//return item at the back of the queue
				const T& back()
				{
					std::scoped_lock lock(muxQueue);
					return deqQueue.back();
				}

				//add item
				void push_back(const T& item)
				{
					std::scoped_lock lock(muxQueue);
					deqQueue.emplace_back(std::move(item));
				}

				//add item to the front
				void push_front(const T& item)
				{
					std::scoped_lock lock(muxQueue);
					deqQueue.emplace_front(std::move(item));
				}

				//return true if Queue has no item
				bool empty()
				{
					std::scoped_lock lock(muxQueue);
					return deqQueue.size() == 0;
				}
				void clear()
				{
					std::scoped_lock lock(muxQueue);
					deqQueue.clear();
				}
				T pop_front()
				{
					std::scoped_lock lock(muxQueue);
					auto t = std::move(deqQueue.front());
					deqQueue.pop_front();
					return t;
				}
				T pop_back()
				{
					std::scoped_lock lock(muxQueue);
					auto t = std::move(deqQueue.back());
					deqQueue.pop_back();
					return t;
				}

			protected:
				std::mutex muxQueue;
				std::deque<T> deqQueue;
		};
	}
}
