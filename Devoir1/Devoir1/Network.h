#pragma once
#include <winsock2.h>

class Network
{
public:
	Network();
	~Network();

	void launch();

private:
	SOCKET previous;
	SOCKET next;

	void listen_thread(SOCKET s);

	void execute();
};

