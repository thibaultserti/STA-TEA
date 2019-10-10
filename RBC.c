#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "RBC.h"

#define TRUE 1

Trains *trains;

bool add_to_rbc(Train *t)
{
    // We first check if the train is not already in our structure
    for (int i = 0; i < (trains -> trains)[trains -> nb_trains]; i++){
        if (strcmp(t -> id, ((trains -> trains)[i]) -> id)){
            return false;
        }
    }
    // THen if the numebr of trains is less than 100, we add the new train to the structure
    if ((trains -> nb_trains) < 100){
        (trains -> trains)[trains -> nb_trains] = t;
        (trains -> nb_trains) ++;
        return true;
    }
    else {
        return false;
    }
}

bool remove_to_rbc(Train *t)
{
    bool removable = false;
    int i;
    for (i = 0; i < (trains -> trains)[trains -> nb_trains]; i++){
        if (strcmp(t -> id, ((trains -> trains)[i]) -> id)){
            removable = true;
            break;
        }
    }
    if(removable){
        (trains -> trains)[i] = 0;
    }
    else{
        return false;
    }
}

bool update_local_rbc(char* id, short local)
{
    for (int i=0; i < (trains -> trains)[trains -> nb_trains]; i++){
        if (strcmp(id, ((trains -> trains)[i]) -> id)){
            ((trains -> trains)[i] -> local) = local;
            return true;
        }
    }
    return false;
}


int main()
{
    // Initialization of the structure trains
    trains -> nb_trains = 0;
    for (int i = 0; i < sizeof(trains -> trains) / sizeof(Train); i++){
        (trains -> trains)[i] = NULL;
    }

    int sock, length;
    struct sockaddr_in server;
    int msgsock;
    char buf[1024];
    int rval;

    /* Create socket */
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Opening stream socket");
        exit(1);
    }
    /* Name socket using wildcards */
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(4242);
    if (bind(sock, (struct sockaddr *)&server, sizeof(server))) {
        perror("Binding stream socket");
        exit(1);
    }
    /* Find out assigned port number and print it out */
    length = sizeof(server);
    if (getsockname(sock, (struct sockaddr *)&server, &length)) {
        perror("Getting socket name");
        exit(1);
    }
    printf("Socket has port #%d\n", ntohs(server.sin_port));

    /* Start accepting connections */
    listen(sock, 5);
    do {
        msgsock = accept(sock, 0, 0);
        if (msgsock == -1) {
            perror("Accept");
            return EXIT_FAILURE;
        } else do {
            memset(buf, 0, sizeof(buf));
            if ((rval  = read(msgsock, buf,  1024)) < 0)
                perror("Reading stream message");
            else if (rval == 0)
                printf("Ending connection\n");
            else
                printf("-->%s\n", buf);
        } while (rval > 0);
        close(msgsock);
    } while (TRUE);
}