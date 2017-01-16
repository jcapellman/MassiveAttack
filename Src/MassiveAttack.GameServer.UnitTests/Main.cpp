#include "Main.h"

int main(int argc, char * argv[])
{
	IPaddress ip;
	char * host;
	Uint16 port;

	host = "127.0.0.1";
	port = 8885;

	if (SDL_Init(0) == -1) {
		printf("SDL_Init: %s\n", SDL_GetError());
		exit(1);
	}
	if (SDLNet_Init() == -1) {
		printf("SDLNet_Init: %s\n", SDLNet_GetError());
		exit(2);
	}

	if (SDLNet_ResolveHost(&ip, host, port) == -1)
	{
		printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		exit(4);
	}

	UDPsocket udpsock;

	udpsock = SDLNet_UDP_Open(0);
	if (!udpsock) {
		printf("SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(2);
	}

	UDPpacket *packet;
	packet = SDLNet_AllocPacket(65535);

	/* bind server address to channel 0 */
	if (SDLNet_UDP_Bind(udpsock, 0, &ip) == -1)
	{
		printf("SDLNet_UDP_Bind: %s\n", SDLNet_GetError());
		exit(7);
	}

	int numsent;

	numsent = SDLNet_UDP_Send(udpsock, 0, packet);
	if (!numsent) {
		printf("SDLNet_UDP_Send: %s\n", SDLNet_GetError());
	}

	while (true) { }

	SDLNet_UDP_Close(udpsock);
	udpsock = NULL;

	SDLNet_Quit();

	return 0;
}