#pragma once

#include <Windows.h>
#include "SDL\SDL.h"
#include "SDL\SDL_net.h"

#include <iostream>

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_net.lib")

using namespace std;

class GameServer
{
public:
	void Init()
	{
		if (SDL_Init(0) == -1)
		{
			exit(1);
		}

		if (SDLNet_Init() == -1)
		{
			exit(2);
		}

		if (!(sock = SDLNet_UDP_Open(port)))
		{
			exit(4);
		}

		if (!(out = SDLNet_AllocPacket(65535)))
		{
			exit(5);
		}
		if (!(in = SDLNet_AllocPacket(65535)))
		{
			exit(5);
		}

		if (!(packets = SDLNet_AllocPacketV(32, len)))
		{
			exit(6);
		}
	}

	void Shutdown()
	{
		SDLNet_UDP_Close(sock);

		SDLNet_FreePacket(out);
		SDLNet_FreePacket(in);
		SDLNet_FreePacketV(packets);

		SDLNet_Quit();

		SDL_Quit();
	}
private:
	Uint16 port;
	Uint32 ipnum, ack;
	IPaddress ip;
	UDPsocket sock;
	UDPpacket *out, *in, **packets, *outs[32];
	int len = 1400, plen, err = 0;
};