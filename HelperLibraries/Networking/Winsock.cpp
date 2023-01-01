#include "Winsock.h"


int InitializeWinsock() {

	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return ERROR;
	}

	//success
	return SUCCESS;
}

SOCKET CreateSocket() {

	SOCKET s;

	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}

	return s;
}

int ConnectToServer(SOCKET s, string ip, int port) {

	struct sockaddr_in server;

	server.sin_addr.s_addr = inet_addr(ip.c_str());
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	//Connect to remote server
	if (connect(s, (struct sockaddr*)&server, sizeof(server)) < 0)
	{
		puts("connect error");
		return ERROR;
	}

	return SUCCESS;


}

int SendString(SOCKET s, string message) {
	//last char in buffer from message will always be ';' to show where
	//message string ends
	char sendBuffer[BUFFER_SIZE];

	for (int i = 0; i < message.size(); i++) {
		sendBuffer[i] = message.at(i);

		//handle trailing ';'
		if (i == (message.size() - 1)) {
			sendBuffer[i + 1] = ';';
		}

	}


	if (send(s, sendBuffer, BUFFER_SIZE, 0) < 0)
	{
		puts("Send failed");
		return ERROR;
	}

	return SUCCESS;

}




int BindServer(SOCKET s, int port) {
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(port);

	if (bind(s, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
		return ERROR;
	}

	return SUCCESS;
}

SOCKET AcceptConnection(SOCKET s) {
	SOCKET new_socket;
	struct sockaddr_in client;
	int c = sizeof(struct sockaddr_in);
	new_socket = accept(s, (struct sockaddr*)&client, &c);
	if (new_socket == INVALID_SOCKET)
	{
		printf("accept failed with error code : %d", WSAGetLastError());
		//maybe close system?
	}

	return new_socket;

}

string ReceiveString(SOCKET new_socket) {

	char server_reply[BUFFER_SIZE];
	int recv_size;
	string returnVal;
	if ((recv_size = recv(new_socket, server_reply, BUFFER_SIZE, 0)) == SOCKET_ERROR)
	{
		//recv failed
		returnVal = "ERROR";
		return returnVal;


	}
	else {
		for (int i = 0; i < BUFFER_SIZE; i++) {
			if (server_reply[i] != ';') {
				returnVal += server_reply[i];
			}
			else {
				break;
			}
		}
	}
	return returnVal;

}