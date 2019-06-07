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

	char addServerInfo[5];
	strcpy(addServerInfo, "S[2]");

	int clientSocket;
	char clientMessage[16];

	//create the server socket
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	//define the server address
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(9004);
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
			//receive a message from a server
			recv(clientSocket, &clientMessage, sizeof(clientMessage), 0);
			printf("The server received the data: %s \n", clientMessage);
			//send back the message
			send(clientSocket, serverMessage, sizeof(clientMessage), 0);
			//close sockets
			close(serverSocket);
			//close(serverSocketIpv6);
		}
		else close(serverSocket);
	}
	else close(serverSocket);

	sleep(1);
//-----------------------------------------------
// Send information

	int networkSocket;	
	struct sockaddr_in nextServerAddress;
	char serverResponse[256];

	//create a socket
	networkSocket = socket(AF_INET, SOCK_STREAM, 0);

	//specify an address for the socket
	nextServerAddress.sin_family = AF_INET;
	nextServerAddress.sin_port = htons(9005);
	nextServerAddress.sin_addr.s_addr = INADDR_ANY;

	int connectionStatus = connect(networkSocket, (struct sockaddr *) &nextServerAddress, sizeof(nextServerAddress));
	
	//check for error with the connection
	if (connectionStatus == -1)
	{
		printf("There was an error making a connection to the remote socket. \n");
	}
	else 
	{
		//send data to a server
		strcat(clientMessage, addServerInfo);
		send(networkSocket, clientMessage , strlen(clientMessage) , 0);

		//recieve data from the server
		recv(networkSocket, &serverResponse, sizeof(serverResponse), 0);

		//print out the server's response
		printf("The server sent forward the data: %s \n", clientMessage);
	}
	//close the socket
	close(networkSocket);
		
	return 0;
}

