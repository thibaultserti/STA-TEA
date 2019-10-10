#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "RBC.h"

Trains *trains;

bool add_to_rbc(Train *t)
{
    // We first check if the train is not already in our structure
    for (int i = 0; i < (trains -> nb_trains); i++){
        if (strcmp(t -> id, ((trains -> trains)[i]) -> id)){
            return false;
        }
    }
    // Then if the numebr of trains is less than 100, we add the new train to the structure
    if ((trains -> nb_trains) < 100){
        (trains -> trains)[trains -> nb_trains] = t;
        (trains -> nb_trains) ++;
        return true;
    }
    else {
        return false;
    }
}

bool remove_to_rbc(Train t)
{
    bool removable = false;
    int i;
    char *train_id = *t.id;
    for (i = 0; i < (trains -> nb_trains); i++){
        if (strcmp(train_id, *((trains -> trains)[i])->id))
        {
            removable = true;
            break;
        }
    }
    if(removable){
        (trains -> trains)[i] = 0;
        return true;
    }
    else{
        return false;
    }
}

bool update_local_rbc(char* id, short local)
{
    for (int i=0; i < (trains -> nb_trains); i++){
        if (strcmp(id, ((trains -> trains)[i]) -> id)){
            (trains -> trains)[i] -> local = local;
            return true;
        }
    }
    return false;
}

bool update_eoa_rbc(void){
    // The structure trains.trains must be sorted by growing local
    for (int i=0; i < (trains -> nb_trains) - 1; i++){
        (trains -> trains)[i] -> eoa = ((trains -> trains)[i+1] -> local) - 1;
    }
    return true;
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
    int datasock;
    char buf[1024];
    int rval;

    /* Create socket */
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Opening stream socket");
        exit(1);
    }

    /* Name socket */
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(4242);

    /* Bind socket */
    if (bind(sock, (struct sockaddr *)&server, sizeof(server))) {
        perror("Binding stream socket");
        exit(1);
    }

    /* Find out assigned port number and print it out */
    length = sizeof(server);
    printf("getsockname");
    if (getsockname(sock, (struct sockaddr *)&server, &length)) {
        perror("Getting socket name");
        exit(1);
    }
    printf("Socket has port #%d\n", ntohs(server.sin_port));

    /* Accepting incoming connections */
    listen(sock, 5);
    do {
        datasock = accept(sock, 0, 0);
        if (datasock == -1) {
            perror("Accept");
            return EXIT_FAILURE;
        } else do {
            memset(buf, 0, sizeof(buf));
            if ((rval  = read(datasock, buf,  1024)) < 0)
            {
                perror("Reading stream message");
            }
            else if (rval == 0)
                printf("Ending connection\n");
            else
                printf("-->%s\n", buf);
        } while (rval > 0);
        close(datasock);
    } while (true);
}