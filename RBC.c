#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "RBC.h"

Trains trains;
const char* separator = ":";

/*
 * This will handle connection for each client
 * */
void* connection_handler(void *sock)
{

    int datasock = *(int*)sock;
    int rval;
    char data[1024];
    if (datasock == -1) {
        perror("Accept");
    } else do {
        memset(data, 0, sizeof(data));
        if ((rval  = read(datasock, data,  1024)) < 0)
        {
            perror("Reading stream message");
        }
        else if (rval == 0)
            printf("Ending connection\n");
        else {
            printf("-->%s\n", data);
            char *id, *local = NULL;
            id = strtok(data,separator);
            local = strtok(NULL,separator);
            short signed local_ = atoi(local);
            
            Train *t = malloc(sizeof(Train));
            t -> id = id;
            t -> local = local_;
            t -> eoa = 100;
            bool is_added = add_to_rbc(t);
            if (!is_added){
                update_local_rbc(t -> id, t -> local);
            }
            if (t -> local == 100) {
                remove_from_rbc(t);
                }
            update_eoa_rbc();
            print_trains();
        }
    } while (rval > 0);
    close(datasock);
	free(sock);	
    return 0;
}


bool add_to_rbc(Train *t)
{
    // We first check if the train is not already in our structure
    for (int i = 0; i < (trains.nb_trains); i++){
        if (strcmp(t -> id, (trains.trains)[i] -> id) == 0){
            printf("The train has not been added because it was already registered.\n");
            return false;
        }
    }
    // Then if the numebr of trains is less than 100, we add the new train to the structure
    if ((trains.nb_trains) < 100){
        // We add the train at the right place (trains.trains is sorted by growing localisation)
        int j = trains.nb_trains;
        for (int i = 0; i < (trains.nb_trains); i++){
            if ((trains.trains[i] -> local) > (t -> local)){
                j = i - 1;
                break;
            }
        }
        for (int i = trains.nb_trains - 1; i >= j; i --){
            trains.trains[i+1] = trains.trains[i];
        }
        (trains.trains)[j] = t;
        (trains.nb_trains) ++;
        printf("The train has been added.\n");
        return true;
    }
    else {
        printf("Max trains has been reached ! Train not added !\n");
        return false;
    }
}

bool remove_from_rbc(Train *t)
{
    bool removable = false;
    int i;
    for (i = 0; i < (trains.nb_trains); i++){
        if (strcmp(t -> id, (trains.trains)[i] -> id) == 0)
        {
            removable = true;
            break;
        }
    }
    if (removable){
        (trains.trains)[i] = 0;
        trains.nb_trains --;
        printf("The train has properly been removed.\n");
        return true;
    }
    else{
        printf("The train doesn't exist !\n");
        return false;
    }
}

bool update_local_rbc(char* id, short local)
{
    for (int i=0; i < (trains.nb_trains); i++){
        if (strcmp(id, (trains.trains)[i] -> id) == 0){
            (trains.trains)[i] -> local = local;
            printf("The localisation has been updated.\n");
            return true;
        }
    }
    printf("The train has not been found.\n");
    return false;
}

bool update_eoa_rbc(void){
    // The structure trains.trains must be sorted by growing local
    for (int i=0; i < (trains.nb_trains) - 1; i++){
        (trains.trains)[i] -> eoa = ((trains.trains)[i+1] -> local) - 1;
    }
    printf("The EOA has been updated.\n");
    return true;
}

void print_trains(void){
    printf("NAME   LOC EOA\n");
    for (int i = 0; i < (trains.nb_trains); i++) {
        printf("%s %d %d\n", (trains.trains)[i] -> id, (trains.trains)[i] -> local, (trains.trains)[i] -> eoa);
    }
}


int main()
{

    // Initialization of the structure trains
    trains.nb_trains = 0;
    for (int i = 0; i < sizeof(trains.trains) / sizeof(Train); i++){
        (trains.trains)[i] = NULL;
    }

    int sock, length;
    struct sockaddr_in server, client;

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
    printf("Getsockname\n");

    if (getsockname(sock, (struct sockaddr *) &server, (socklen_t * restrict) &length)) {
        perror("Getting socket name");
        exit(1);
    }
    printf("Socket has port #%d\n", ntohs(server.sin_port));

    /* Accepting incoming connections */
    listen(sock, MAX_REQUEST);
    int c = sizeof(struct sockaddr_in);
    int new_socket;
    while ((new_socket = accept(sock, (struct sockaddr *)&client, (socklen_t*)&c)))
    {
        pthread_t thread;
        int *new_sock = malloc(1);
        *new_sock = new_socket;

        if(pthread_create(&thread, NULL, connection_handler, (void*) new_sock)<0)
        {
            perror("Could not create thread");
            return 1;
        }

        puts("New connection assigned to handler");
    }

    if(new_socket<0)
    {
        perror("Could not accept connection");
        return 1;
    }

    return 0;
}