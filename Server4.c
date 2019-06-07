#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

#include <string.h>
#include <unistd.h>
int main ()
{



	char serverMessage[256] = "You have reached the server! \n";
	int serverSocket;
	struct sockaddr_in serverAddress;

	char addServerInfo[];
	strcpy(addServerInfo, "S[4]");

	int clientSocket;
	char clientMessage[27];

	//create the server socket
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	//define the server address
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(9006);
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	
	//bind the socket to our specified IP and port
	bind (serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
	
	//listen
	int listenStatus = listen(serverSocket, 5);

	if (listenStatus != -1)
	{
		clientSocket = accept(serverSocket, NULL, NULL);
		if (clientSocket != -1)
		{
			//receive a message form client
			recv(clientSocket, &clientMessage, sizeof(clientMessage), 0);
			printf("The server received the data: %s \n", clientMessage);
			//send back the message
			send(clientSocket, serverMessage, sizeof(clientMessage), 0);
			//close sockets
			close(serverSocket);
		}
		else close(serverSocket);
	}
	else close(serverSocket);



//-----------------------------------------------
// Send information

	int lastServerSocket;
	struct sockaddr_in lastServerAddress;

	int sameClientSocket;
	//create the server socket
	lastServerSocket = socket(AF_INET, SOCK_STREAM, 0);

	//define the server address
	lastServerAddress.sin_family = AF_INET;
	lastServerAddress.sin_port = htons(9007);
	lastServerAddress.sin_addr.s_addr = INADDR_ANY;
	
	//bind the socket to our specified IP and port
	bind (lastServerSocket, (struct sockaddr *) &lastServerAddress, sizeof(lastServerAddress));

	//listen
	int newListenStatus = listen(lastServerSocket, 5);


	if (newListenStatus != -1)
	{
		sameClientSocket = accept(lastServerSocket, NULL, NULL);
		if (sameClientSocket != -1)
		{
			//send the message
			strcat(clientMessage, addServerInfo);
			send(sameClientSocket, clientMessage, sizeof(clientMessage), 0);
			printf("The server sent forward the data: %s \n", clientMessage);
			//close sockets
			close(lastServerSocket);
		}
		else close(lastServerSocket);
	}
	else close(lastServerSocket);


	return 0;
}

