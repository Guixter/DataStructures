#include "Network.h"
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <iostream>
#include <WinNT.h>
#pragma comment(lib, "Ws2_32.lib")

using namespace std;


Network::Network()
{
}


Network::~Network()
{
}

void Network::launch() {
	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 0), &WSAData);

	previous = socket (AF_INET, SOCK_STREAM, 0);
	SOCKET tempSocket = socket(AF_INET, SOCK_STREAM, 0);

	int tempSocketPort = 0;

	cout << "Port : ";
	cin >> tempSocketPort;

	SOCKADDR_IN tempSocketSin;
	inet_pton(AF_INET, "127.0.0.1", &(tempSocketSin.sin_addr));
	tempSocketSin.sin_family = AF_INET;
	tempSocketSin.sin_port = htons(tempSocketPort);
	tempSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (bind(tempSocket, (SOCKADDR *)&tempSocketSin, sizeof(tempSocketSin)) == SOCKET_ERROR) {
		cout << "RIGHT SOCKET ERROR BIND" << endl;
		cout << WSAGetLastError() << endl;
	}

	// Connect to previous
	SOCKADDR_IN servSin;
	inet_pton(AF_INET, "127.0.0.1", &(servSin.sin_addr));
	servSin.sin_family = AF_INET;
	servSin.sin_port = htons(tempSocketPort-1);
	if (connect(previous, (SOCKADDR *)&servSin, sizeof servSin) == 0) {
		//Pred is define
		cout << "Connecte a " << tempSocketPort-1 << endl;
	} else {
		cout << "Tentative de connexion a echoue" << endl;
		cout << WSAGetLastError() << endl;
	}

	//Listen for tempSocket
	listen(tempSocket, 1);
	int sizeof_csin = sizeof(tempSocketSin);
	SOCKADDR_IN clientSin;
	while ((next = accept(tempSocket, (SOCKADDR *)&clientSin, &sizeof_csin)) == INVALID_SOCKET);
	cout << tempSocketPort << " accepte" << endl;

	closesocket(tempSocket);
	
	while (true) {
		//listen for tempSocket

		//if message is send
	}

	//Cleanup
	WSACleanup();
}