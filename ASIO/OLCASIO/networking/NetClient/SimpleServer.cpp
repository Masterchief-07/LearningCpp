#include <iostream>
#include <olc_net.h>

enum class CustomMsgTypes: uint32_t
{
	ServerAccept,
	ServerDeny,
	ServerPing,
	NessageAll,
	ServerMessage,
};

class CustomServer: public olc::net::server_interface<CustomMsgTypes>
{
	public:
		CustomServer(uint16_t port): olc::net::server_interface<CustomMsgTypes>(port)
		{

		}

	protected:
		virtual bool OnClientConnect(std::shared_ptr<olc::net::connection<CustomMsgTypes>> client)
		{
			return true;
		}

		virtual void OnClientDisconnect(std::shared_ptr<olc::net::connection<CustomMsgTypes>> client)
		{

		}

		virtual void OnMessage(std::shared_ptr<olc::net::connection<CustomMsgTypes>> client, olc::net::message<CustomMsgTypes>& message)
		{

		}
};


int main()
{
	CustomServer server(60000);
	server.Start();

	while(1)
	{
		server.Update();
	}

	return 0;
}
