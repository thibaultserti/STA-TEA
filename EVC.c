#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include "EVC.h"

char *separator = ":";

int SocketCreate(void)
{
	int new_socket;
	//Create socket
	new_socket = socket(AF_INET, SOCK_STREAM, 0);
	return new_socket;
}

void SocketConnect(int socket_desc, char* adresse_hote)
{
	int return_value = -1;
	struct sockaddr_in server;
	server.sin_addr.s_addr = inet_addr(adresse_hote);
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT_NUMBER);

	//Vérification de la connection
	while (return_value < 0)
	{
	        return_value = connect(socket_desc, (struct sockaddr *)&server, sizeof(server));
		printf("Could not connect to RBC\n");
	}
}

int main(int argc , char *argv[])
{
	int socket_desc;
	bool is_moving = true;

	//Création de la socket	
	socket_desc = SocketCreate();

	//Vérification de la création
	if (socket_desc == -1)
	{
		printf("Could not create socket\n");
		return 0;
	}

	//Connection au server
	SocketConnect(socket_desc, argv[1]);
	
	printf("Connected");
	printf("Train starting to move…");
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
	} 
	else{
		do {
			char data_received[1024] = "";
			memset(data_received, 0, sizeof(data_received));
			int rcv;
			if((rcv = read(socket_desc, data_received, 1024)) < 0)
			{
				perror("Reading stream message");
			}
			if (rcv == 0)
			{
				perror("Ending connection\n");
			}
			if ((strcmp(data_received,"START"))==0)
			{
				printf("%s\n",data_received);
				is_moving = true;
			}
			if ((strcmp(data_received,"STOP"))==0)
			{
				printf("%s\n",data_received);
				is_moving = false;
			}

			if(is_moving) // Simulates the train moving at the speed of argv[4]
			{
				sleep(atoi(argv[4]));
				sprintf(localisation, "%d", localisation_);
				char temp[9] = "";
				strcat(temp,id);
				strcat(temp,separator);
				strcat(temp,localisation);

				if (send(socket_desc, temp, strlen(temp), 0)<0)
					printf("Could not send data to RBC, dropping signal\n");
				else{
					printf("Data sent : %s",temp);
				}
				localisation_++;

			}
		} while(localisation_ < 100);
	}
	return 1;
}
