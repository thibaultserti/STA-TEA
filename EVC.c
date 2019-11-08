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
    speed = argv[4];
    do {
        int socket_desc;
        int connection;
        int rval;
        int reqack, entier;

        printf("Trying to connect to RBC\n");

        //Création de la socket
        socket_desc = SocketCreate();
        //Vérification de la création
        if (socket_desc == -1) {
            perror("Could not create socket\n");
            //on reprend la boucle while
            continue;
        }

        //Connection au server
        SocketConnect(socket_desc, argv[1]);

        printf("Connected\n");

        if (!(send_data(socket_desc, REQUEST, ADD_TRAIN, id, localisation, speed))){
            continue;
        }
        char response[SIZEOF_MSG] = "";
        connection = SocketReceive(socket_desc, response, SIZEOF_MSG);
        /* Listening to RBC */
        do {
            sprintf(speed, "%d", get_speed());
            sprintf(localisation, "%d", get_localisation());
            send_data(socket_desc, REQUEST, LOCATION_REPORT, id, localisation, speed);

            memset(response, 0, sizeof(response));
            rval = read(socket_desc, response, SIZEOF_MSG);
            if (rval < 0) {
                perror("Reading stream message");
            } else if (rval == 0) {
                perror("Ending connection\n");
                break;
            } else {

                parse_data(response, &reqack, &entier, &id, &localisation, &speed);

                switch (entier) {
                    case ADD_TRAIN :
                        switch (reqack) {
                            case RESPONSE :
                                printf("Train added\n");
                                break;
                            case ERROR :
                                perror("Too many trains !\n");
                                exit(0);
                        }
                        break;

                    case LOCATION_REPORT :
                        switch (reqack) {
                            case RESPONSE :
                                printf("Position has been transmitted\n");
                                break;
                            case ERROR :
                                break;
                        }
                        break;
                    //This use case is not a part of the project
                    /*case DELETE_TRAIN :
                        switch (reqack){
                            case REQUEST :
                                break;
                            case RESPONSE :
                                break;
                            case ERROR :
                                break;

                        }
                        break;*/

                    case MOVEMENT :
                        switch (reqack){
                            case REQUEST :
                                send_data(socket_desc, RESPONSE, MOVEMENT, id, localisation, speed);
                                change_speed();
                                break;
                            case ERROR :
                                break;
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
        sleep(3);
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

int get_localisation(void){
    int localisation = 10;
    return localisation;
}
int get_speed(void){
    int speed = 1;
    return speed;
}

void change_speed(void) {

}
