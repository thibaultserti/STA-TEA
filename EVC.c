#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include "EVC.h"

#define ENOUGH ((CHAR_BIT * sizeof(int) - 1) / 3 + 2)

char *separator = ":";

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
		puts("Could not connect to RBC");
		return 1;
	}
	
	puts("Connected");
	puts("Train starting to move…");
	char data[9];
	char* id = argv[2];
	char* localisation = argv[3];
	strcat(data,id);
	strcat(data,separator);
	strcat(data,localisation);

	int localisation_ = atoi(localisation);
	do{
		sleep(atoi(argv[4]));
		localisation_++;
		sprintf(localisation, "%d", localisation_);
		char temp[9] = "";
		strcat(temp,id);
		strcat(temp,separator);
		strcat(temp,localisation);

		if (send(socket_desc, temp, strlen(temp), 0)<0)
			puts("Could not send data to RBC, dropping signal");
		else{
			puts("Data sent : ");
			puts(temp);
		}
	}while(localisation_ <= 100);
	return 1;
}
