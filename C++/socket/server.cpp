#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <sys/select.h>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;
/*
 * Ensure non-blocking I/O by applying select()
 */

int main(int argc, char* argv[])
{
	if(argc != 2) {
		cout << "Error: Usage is ./server <listen_port>\n";
		return 1;
	}

	int portNum = atoi(argv[1]);

	// Bind server to sd and set up listen server
	int sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in self;
	self.sin_family = AF_INET;
	self.sin_addr.s_addr = INADDR_ANY;
	self.sin_port = htons((u_short) port_num);

	if(-1 == bind(sd, (struct sockaddr*) &self, sizeof(self))) {
		cout << "Error binding the socket to the port number\n";
		exit(1);
	}
	if(-1 == listen(sd, 10)) {
		cout << "Error setting up listen queue\n";
		exit(1);
	}

	fd_set readSet;     // Set of file descriptors to listen to
	vector<int> fds;    // Keep track of each file descriptor accepted

	while(true) 
	{
		// Set up the readSet
		FD_ZERO(&readSet);
		FD_SET(sd, &readSet);
		for(int i = 0; i < (int) fds.size(); ++i) {
			FD_SET(fds[i], &readSet);
		}

		int maxfd = 0;
		if(fds.size() > 0) {
			maxfd = *max_element(fds.begin(), fds.end());
		}
		maxfd = max(maxfd, sd);

		// maxfd + 1 is important
		int err = select(maxfd + 1, &readSet, NULL, NULL, NULL);
		assert(err != -1);

		if(FD_ISSET(sd, &readSet))
		{
			int clientsd = accept(sd, NULL, NULL);
			if(clientsd == -1)
			{
				cout << "Error on accept" << endl;
			}
			else
			{
				fds.push_back(clientsd);
			}
		}

		for(int i = 0; i < (int) fds.size(); ++i)
		{
			if(FD_ISSET(fds[i], &readSet))
			{
				char buf = 'x';
				int bytesRecvd = recv(fds[i], &buf, 1, 0);
				if(bytesRecvd < 0)
				{
					cout << "Error recving bytes" << endl;
					cout << strerror(errno) << endl;
					exit(1);
				}
				else if(bytesRecvd == 0)
				{
					cout << "Connection closed" << endl;
					fds.erase(fds.begin() + i);
				}

				buf = 'a' + fds[i];
				int bytesSent = send(fds[i], &buf, 1, 0);
				if(bytesSent <= 0)
				{
					cout << "Error sending bytes" << endl;
				}
			}
		}
	}
}