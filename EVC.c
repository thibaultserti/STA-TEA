#include <stdlib.h>
#include <stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include "EVC.h"

int main(int argc , char *argv[])
{
	int socket_desc;
	struct sockaddr_in server;
	
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
		
	server.sin_addr.s_addr = inet_addr(argv[1]);
	server.sin_family = AF_INET;
	server.sin_port = htons(4242);

	//Connect to remote server
	if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("Connect error");
		return 1;
	}
	
	puts("Connected");
	puts("Sending data…");
	char data[10];
	char* id = argv[2];
	char* localisation = argv[3];
	strcat(data,id);
	strcat(data, ":");
	strcat(data,localisation);
	if (send(socket_desc, data, strlen(data), 0)<0)
	{
		puts("Failed to send data");
		return 1;
	}
	puts("Data sent");
	return 0;
}