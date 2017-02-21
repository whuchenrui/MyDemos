#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

using namespace std;

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		cout << "Error: Usage is ./client <port_number>\n";
		return 1;
	}

	int portNum = atoi(argv[1]);
	int serversd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(serversd == -1)
	{
		cout << "Error creating server socket\n";
		exit(1);
	}

	// Set up a connection to the server
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons((u_short) portNum);
	struct hostent* sp = gethostbyname("localhost");
	memcpy(&server.sin_addr, sp->h_addr, sp->h_length);
	int err = connect(serversd, (sockaddr*) &server, sizeof(server));
	if(err == -1)
	{
		cout << "Error on connect\n";
		exit(1);
	}

	// Enter a loop where it constantly sends one byte to the server and gets one byte back
	while(true)
	{
		char buf = 'a';
		int bytesSent = send(serversd, &buf, 1, 0);
		if(bytesSent <= 0)
		{
			cout << "Error sending stuff to server" << endl;
		} 

		int bytesRecv = recv(serversd, &buf, 1, 0);
		if(bytesRecv > 0)
		{
			cout << "Received from client: " << buf << endl;
		}
		else
		{
			exit(1);
		}
	}

	close(serversd);
	return 0;
}