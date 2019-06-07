#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
int main()
{	
	char clientMessage[6] = "Labas";
	int networkSocket;	
	struct sockaddr_in serverAddress;
	char serverResponse[256];

	//create a socket
	networkSocket = socket(AF_INET, SOCK_STREAM, 0);

	//specify an address for the socket
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(9002);
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	int connectionStatus = connect(networkSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
	
	//check for error with the connection
	if (connectionStatus == -1)
	{
		printf("There was an error making a connection to the remote socket. \n");
	}
	else 
	{
		//send data to a server
		send(networkSocket, clientMessage , strlen(clientMessage) , 0);
		//recieve data from the server
		recv(networkSocket, &serverResponse, sizeof(serverResponse), 0);
		//print out the server's response
		printf("The server sent the data. %s", serverResponse);
	}
	//close the socket
	close(networkSocket);
	sleep(8);
//------- Socket for the last Server
	int lastServerNetworkSocket;	
	struct sockaddr_in lastServerAddress;
	char lastServerResponse[26];

	//create a socket
	lastServerNetworkSocket= socket(AF_INET, SOCK_STREAM, 0);

	//specify an address for the socket
	lastServerAddress.sin_family = AF_INET;
	lastServerAddress.sin_port = htons(9007);
	lastServerAddress.sin_addr.s_addr = INADDR_ANY;

	int connectionStatus1 = connect(lastServerNetworkSocket, (struct sockaddr *) &lastServerAddress, sizeof(lastServerAddress));
	
	//check for error with the connection
	if (connectionStatus1 == -1)
	{
		printf("There was an error making a connection to the remote socket. \n");
	}
	else 
	{
		//recieve data from the server
		recv(lastServerNetworkSocket, &lastServerResponse, sizeof(lastServerResponse), 0);
		//print out the server's response
		printf("The client received the data. %s \n", lastServerResponse);
	}
	//close the socket
	close(lastServerNetworkSocket);


	return 0;
}
