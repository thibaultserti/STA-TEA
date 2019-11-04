#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include "EVC.h"

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
    id = argv[2];
    localisation = argv[3];
    do {
	    int socket_desc;
	    int connection;
        char data[12];

	    printf("Trying to connect to RBC\n");

	    //Création de la socket
	    socket_desc = SocketCreate();
	    //Vérification de la création
	    if (socket_desc == -1)
	    {
		    perror("Could not create socket\n");
		    //on reprend la boucle while
		    //continue;
	    }

	    //Connection au server
	    SocketConnect(socket_desc, argv[1]);
	
	    printf("Connected\n");

	    sprintf(data, "%d", ADD_TRAIN);
	    sprintf(data, "%d", REQUEST);
	    strcat(data,id);
	    strcat(data,localisation);
        if (send(socket_desc, data, strlen(data), 0)<0)
            perror("Writing stream message");
        else{
            printf("Sending the following request : %s\n",data);
        }

        char response[SIZEOF_MSG] = "";
        connection = SocketReceive(socket_desc, response, SIZEOF_MSG);
        //Vérification de la connexion
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
        while (true){
            sleep(5);
        }
	} while(true);
	return 1;
}
