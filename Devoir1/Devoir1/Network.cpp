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

enum Message_Type { SEND_ID, SEND_ID_BACK, GET_ID };

Network::Network()
{
	next = -1;
	previous = -1;
	msgRcv = -1;
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

	std::cout << "Port d'ecoute : ";
	std::cin >> tempSocketPort;
	rightPort = tempSocketPort;
	leftPort = rightPort - 1;

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
		std::cout << "Connecte au port d'ecoute n" << tempSocketPort-1 << std::endl;
	}

	//Start to listen previous thread
	std::thread thread_listen_previous(&Network::listen_thread, this, previous);
	std::thread thread_main(&Network::execute, this);

	//Listen for tempSocket
	listen(tempSocket, 1);
	int sizeof_csin = sizeof(tempSocketSin);
	SOCKADDR_IN clientSin;
	SOCKET aux;
	while ((aux = accept(tempSocket, (SOCKADDR *)&clientSin, &sizeof_csin)) == INVALID_SOCKET);
	next = aux;
	std::cout << "Le port d'ecoute s'est connecte a un noeud" << std::endl;

	closesocket(tempSocket);

	std::thread thread_listen_next(&Network::listen_thread, this, next);

	thread_listen_previous.join();
	thread_listen_next.join();
	thread_main.join();

	//Cleanup
	WSACleanup();
}

void Network::listen_thread(SOCKET s) {
	// if socket is still connected try to receive from him
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
	int iResult;

	while (true) {
		iResult = recv(s, recvbuf, recvbuflen -1, 0);
		if (iResult > 0) {
			recvbuf[iResult] = '\0';
			process_message(recvbuf, s);
		}
		else if (iResult == 0)
			printf("Connection closed\n");
		else {
			// Connection aborted : try to reconnect to another node
			if (s == previous) {
				previous = -1;
				reconnect_left_socket(s);
				previous = s;
			} else if (s == next) {
				next = -1;
				reconnect_right_socket(s);
				next = s;
			}
		}
	}
}

void Network::process_message(const char* msg, SOCKET s) {
	if (strlen(msg) < 1)
		return;

	Message message(msg);
	SOCKET other = (s == next) ? previous : next;

	switch (message.typeMessage) {
		case SEND_ID:
			if (other == -1) {
				if (s != -1) {
					message.id += GetCurrentProcessId();
					message.typeMessage = SEND_ID_BACK;
					message.serialize();
					send_message(message.bin, s);
				}
			}
			else {
				message.id += GetCurrentProcessId();
				message.serialize();
				send_message(message.bin, other);
			}
			break;
		case GET_ID:
			std::cout << " Somme des ids : "<< message.id << std::endl;
			send_message(message.bin, other);
			break;
		case SEND_ID_BACK:
			if (message.origin == GetCurrentProcessId()) {
				msgRcv++;
				idSum += message.id;
				if (msgRcv == 2) {
					idSum += GetCurrentProcessId();
					std::cout << " Somme des ids : " << idSum << std::endl;
					message.typeMessage = GET_ID;
					message.id = idSum;

					message.serialize();
					send_message(message.bin, previous);
					send_message(message.bin, next);

					msgRcv = -1;
				}
			}
			else {
				send_message(message.bin, other);
			}
			break;
		default:
			return;
			break;
	}

}


void Network::execute() {
	int choice = -1;
	int iResult;

	while (choice != 0) {
		//listen for tempSocket
		system("pause");
		Message msg(SEND_ID, GetCurrentProcessId(), 0);

		if (msgRcv == -1) {
			msgRcv = 0;
			idSum = 0;

			if (previous == -1)
				msgRcv++;
			if (next == -1)
				msgRcv++;

			send_message(msg.bin, next);
			send_message(msg.bin, previous);

			if (msgRcv == 2) {
				msgRcv = -1;
			}
		}
	}
}

void Network::send_message(const char* msg, SOCKET s) {
	int iResult;

	if (s != -1) {
		iResult = send(s, msg, (int)strlen(msg), 0);
		if (iResult == SOCKET_ERROR) {
			printf("send failed: %d\n", WSAGetLastError());
			// le précédent socket est surement non défini
		}
	}
}

void Network::reconnect_left_socket(SOCKET &s) {
	std::cout << "Port d'ecoute n" << leftPort << " deconnecte" << std::endl;
	std::cout << "Tentative de connexion au port d'ecoute n" << (leftPort - 1) << std::endl;

	SOCKET aux = socket(AF_INET, SOCK_STREAM, 0);
	leftPort --;
	msgRcv = -1;

	SOCKADDR_IN servSin;
	inet_pton(AF_INET, "127.0.0.1", &(servSin.sin_addr));
	servSin.sin_family = AF_INET;
	servSin.sin_port = htons(leftPort);

	while (connect(aux, (SOCKADDR *)&servSin, sizeof servSin) != 0);
	std::cout << "Connecte au port d'ecoute n" << leftPort << std::endl;
	s = aux;
}

void Network::reconnect_right_socket(SOCKET &s) {
	msgRcv = -1;

	std::cout << "Le noeud lie au port d'ecoute s'est deconnecte." << std::endl;
	std::cout << "Tentative de reconnexion du port d'ecoute n" << rightPort << std::endl;

	SOCKET tempSocket;

	SOCKADDR_IN tempSocketSin;
	inet_pton(AF_INET, "127.0.0.1", &(tempSocketSin.sin_addr));
	tempSocketSin.sin_family = AF_INET;
	tempSocketSin.sin_port = htons(rightPort);
	tempSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (bind(tempSocket, (SOCKADDR *)&tempSocketSin, sizeof(tempSocketSin)) == SOCKET_ERROR) {
		std::cout << "RIGHT SOCKET ERROR BIND" << std::endl;
		std::cout << WSAGetLastError() << std::endl;
	}

	//Listen for tempSocket
	listen(tempSocket, 1);
	int sizeof_csin = sizeof(tempSocketSin);
	SOCKADDR_IN clientSin;
	SOCKET aux;
	while ((aux = accept(tempSocket, (SOCKADDR *)&clientSin, &sizeof_csin)) == INVALID_SOCKET);
	s = aux;
	std::cout << "Le port d'ecoute s'est connecte a un noeud" << std::endl;

	closesocket(tempSocket);
}