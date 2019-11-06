#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include "EVC.h"

int main(int argc , char *argv[]) {
    id = argv[2];
    localisation = argv[3];
    do {
        int socket_desc;
        int connection;
        int rval;
        int reqack;
        int entier;
        char data[12];

        printf("Trying to connect to RBC\n");

        //Création de la socket
        socket_desc = SocketCreate();
        //Vérification de la création
        if (socket_desc == -1) {
            perror("Could not create socket\n");
            //on reprend la boucle while
            //continue;
        }

        //Connection au server
        SocketConnect(socket_desc, argv[1]);

        printf("Connected\n");

        sprintf(data, "%d", REQUEST);
        sprintf(data, "%d", ADD_TRAIN);
        strcat(data, id);
        strcat(data, localisation);
        if (send(socket_desc, data, strlen(data), 0) < 0)
            perror("Writing stream message");
        else {
            printf("Sending the following message : %s\n", data);
        }

        char response[SIZEOF_MSG] = "";
        connection = SocketReceive(socket_desc, response, SIZEOF_MSG);
        /* Listening to RBC */
        do {
            memset(response, 0, sizeof(response));
            rval = read(socket_desc, response, SIZEOF_MSG);
            if (rval < 0) {
                perror("Reading stream message");
            } else if (rval == 0) {
                perror("Ending connection\n");
                break;
            } else {
                reqack = str_sub(data, 0, 2);
                entier = str_sub(entier, 2, 3);
                switch (entier) {
                    case ADD_TRAIN :
                        switch (reqack) {
                            case RESPONSE :
                                ;
                            case ERROR :
                                ;
                        }
                        break;

                    case LOCATION_REPORT :
                        switch (reqack) {
                            case REQUEST : //Necessary ?
                            /* Does the RBC needs it or EVC ? */
                                ;
                            case RESPONSE :
                                ;
                            case ERROR :
                                ;
                        }
                        break;

                    case DELETE_TRAIN :
                        switch (reqack){
                            case REQUEST :
                                ;
                            case RESPONSE :
                                ;
                            case ERROR :
                                ;

                        }
                        break;

                    case MOVEMENT :
                        switch (reqack){
                            case RESPONSE :
                                ;
                            case ERROR :
                                ;
                        }
                        break;
                }
            }
        }while (true);

        //Vérification de la connexion
        if (connection == 0) {
            perror("Ending connection\n");
            continue;
        }

        } while (true);
        return 1;
    }


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
