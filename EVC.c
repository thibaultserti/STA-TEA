#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include "EVC.h"

char *separator = ":";

int main(int argc , char *argv[])
{
	int socket_desc;
	struct sockaddr_in server;
	is_moving = true;
	
	//Create socket
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket\n");
	}
		
	server.sin_addr.s_addr = inet_addr(argv[1]);
	server.sin_family = AF_INET;
	server.sin_port = htons(4242);

	//Connect to remote server
	if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("Could not connect to RBC\n");
		return 1;
	}
	
	puts("Connected");
	puts("Train starting to move…");
	char data[11];
	char* id = argv[2];
	char* localisation = argv[3];
	strcat(data,id);
	strcat(data,separator);
	strcat(data,localisation);

	int localisation_ = atoi(localisation);
	if (socket_desc == -1)
	{
		perror("Accept");
	} else do {
		if(is_moving) // Simulates the train moving at the speed of argv[4]
		{
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
		}
		else // If the train stopped moving
		{
			int rcv;
			if((rcv = read(socket_desc, data, 1024)) < 0)
			{
				perror("Reading stream message");
			}
			else if (rcv == 0)
			{
				perror("Ending connection\n");
			}
			else
			{
				is_moving = true;
			}
		}
		
	} while(localisation_ < 100);
	return 1;
}
