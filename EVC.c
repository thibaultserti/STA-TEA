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
	while (true)
	{
	    return_value = connect(socket_desc, (struct sockaddr *)&server, sizeof(server));
	    perror("Connection\n");
	    if(return_value<0)
        {
            printf("Could not connect to RBC\n");
        }
	    if(return_value == 0)
        {
            break;
        }
	}
}

int SocketReceive(int socket, char* response, short rcvSize)
{
    int rcv = -1;
    while(rcv<0)
    {
        rcv = read(socket, response, rcvSize-1);
        if(rcv < 0) /*Vérification nécessaire mais pas élégante. L'idéal serait de pouvoir exécuter une instruction
            qu'après la première instance du while */
        {
            perror("Reading stream message");
        }
        if (rcv == 0)
        {
            perror("Ending connection in receive\n");
            return 0;
        }
    }
    return 1;
}

int main(int argc , char *argv[])
{
    do {
	    int socket_desc;
	    int connection;
	    is_moving = true;

	    printf("Trying to connect to RBC\n");

	    //Création de la socket
	    socket_desc = SocketCreate();
	    //Vérification de la création
	    if (socket_desc == -1)
	    {
		    perror("Could not create socket\n");
		    //on reprend la boucle while
		    continue;
	    }

	    //Connection au server
	    SocketConnect(socket_desc, argv[1]);
	
	    printf("Connected\n");

	    char data[11];
	    char* id = argv[2];
	    char* localisation = argv[3];
	    strcat(data,id);
	    strcat(data,separator);
	    strcat(data,localisation);

	    int localisation_ = atoi(localisation);

        char response[SIZEOF_MSG] = "";
        connection = SocketReceive(socket_desc, response, SIZEOF_MSG);

        if (connection == 0)
        {
            perror("Ending connection\n");
            continue;
        }

        if ((strcmp(response,"START"))==-1)
        {
            printf("%s\n",response);
            is_moving = true;
        }
        if ((strcmp(response,"STOP"))==-1)
        {
            printf("%s\n",response);
            is_moving = false;
        }

        if(is_moving)
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
                printf("Data sent : %s\n",temp);
            }
            localisation_++;
            return 1;

        }
	} while(true);
	return 1;
}
