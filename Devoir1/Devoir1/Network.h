#pragma once
#include <winsock2.h>
#include <sstream>
#include <vector>
#include <string>

struct Message {
public:
	int typeMessage;
	int origin;
	int id;
	char bin[512];

	Message(int _typeMessage, int _origin, int _id) : typeMessage(_typeMessage), origin(_origin), id(_id) { serialize(); }
	Message(const char* msg) {
		std::stringstream test;
		test << msg;
		std::string segment;
		std::vector<std::string> seglist;

		while (std::getline(test, segment, '|'))
		{
			seglist.push_back(segment);
		}

		typeMessage = stoi(seglist[0]);
		origin = stoi(seglist[1]);
		id = stoi(seglist[2]);
		serialize();
	}

	void serialize() {
		std::string startMessage = std::to_string(typeMessage) + "|" + std::to_string(origin) + "|" + std::to_string(id) + '\0';
		strcpy_s(bin, startMessage.c_str());
	}
};

class Network
{
public:
	Network();
	~Network();

	void launch();

private:
	SOCKET previous;
	SOCKET next;

	int msgRcv;
	int idSum;

	void listen_thread(SOCKET s);
	void process_message(const char* msg, SOCKET s);
	void send_message(const char* msg, SOCKET s);

	void execute();
};

