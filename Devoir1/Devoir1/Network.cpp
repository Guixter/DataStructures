#include <iostream>
#include <thread>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <WinNT.h>
#include <string>
#include "Network.h"
#pragma comment(lib, "Ws2_32.lib")

//using namespace std;
#define DEFAULT_BUFLEN 512

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

	std::cout << "Port : ";
	std::cin >> tempSocketPort;

	SOCKADDR_IN tempSocketSin;
	inet_pton(AF_INET, "127.0.0.1", &(tempSocketSin.sin_addr));
	tempSocketSin.sin_family = AF_INET;
	tempSocketSin.sin_port = htons(tempSocketPort);
	tempSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (bind(tempSocket, (SOCKADDR *)&tempSocketSin, sizeof(tempSocketSin)) == SOCKET_ERROR) {
		std::cout << "RIGHT SOCKET ERROR BIND" << std::endl;
		std::cout << WSAGetLastError() << std::endl;
	}

	// Connect to previous
	SOCKADDR_IN servSin;
	inet_pton(AF_INET, "127.0.0.1", &(servSin.sin_addr));
	servSin.sin_family = AF_INET;
	servSin.sin_port = htons(tempSocketPort-1);

	if (connect(previous, (SOCKADDR *)&servSin, sizeof servSin) == 0) {
		//Pred is define
		std::cout << "Connecte a " << tempSocketPort-1 << std::endl;
		//Start to listen 
	} else {
		std::cout << "Tentative de connexion a echoue" << std::endl;
		std::cout << WSAGetLastError() << std::endl;
	}

	//Start to listen previous thread
	std::thread thread_listen_previous(&Network::listen_thread, this, previous);
	std::thread thread_main(&Network::execute, this);

	//Listen for tempSocket
	listen(tempSocket, 1);
	int sizeof_csin = sizeof(tempSocketSin);
	SOCKADDR_IN clientSin;
	while ((next = accept(tempSocket, (SOCKADDR *)&clientSin, &sizeof_csin)) == INVALID_SOCKET);
	std::cout << tempSocketPort << " accepte" << std::endl;

	closesocket(tempSocket);

	std::thread thread_listen_next(&Network::listen_thread, this, next);

	thread_listen_previous.join();
	thread_listen_next.join();
	thread_main.join();

	//Cleanup
	WSACleanup();
}

void Network::listen_thread(SOCKET s) {
	//check if socket is connected first
	/*char error_code;
	int error_code_size = sizeof(error_code);
	if (getsockopt(s, SOL_SOCKET, SO_ERROR, &error_code, &error_code_size) == -1) {
		std::cout << "socket error" << std::endl;
		return;
	}*/

	// if socket is still connected try to receive from him
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
	int iResult;

	while (true) {
		iResult = recv(s, recvbuf, recvbuflen, 0);
		if (iResult > 0)
			printf("You received: %s\n", recvbuf);
		else if (iResult == 0)
			printf("Connection closed\n");
		//else
		//	printf("recv failed: %d\n", WSAGetLastError());

	}
}

void Network::execute() {
	int choice = -1;
	int iResult;

	while (choice != 0) {
	//listen for tempSocket
		std::cout << "Voulez vous recupérer les ids?" << std::endl;
		std::cin >> choice;
		std::cout << "Envoi" << std::endl;

		iResult = send(next, std::to_string(choice).c_str(), (int)strlen(std::to_string(choice).c_str()), 0);
		if (iResult == SOCKET_ERROR) {
			printf("send failed: %d\n", WSAGetLastError());
			// le prochain socket est surement non défini
		}

		iResult = send(previous, std::to_string(choice).c_str(), (int)strlen(std::to_string(choice).c_str()), 0);
		if (iResult == SOCKET_ERROR) {
			printf("send failed: %d\n", WSAGetLastError());
			// le précédent socket est surement non défini
		}
	}
}