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
    int number_train;
    int datasock = *(int*)sock;
    int rval;
    int wval;
    char data[1024];
    char *signal = "START";
    if (datasock == -1) {
        perror("Accept");
    } else do {
        /* Authorisation to move forward */
        wval = send(datasock, signal, strlen(signal), 0);
        if(wval < 0)
        {
            perror("Writing stream message");
        }
        else{
            puts("Data sent :");
            puts(signal);
        }

        /* If the train stopped, wait until he has authorisation */
        if(strcmp(signal,"STOP")==0)
        {
            while(trains.trains[number_train] -> eoa <= trains.trains[number_train] -> local){
                sleep(1);
            }
            signal = "START";
        }

        memset(data, 0, sizeof(data));
        if ((rval  = read(datasock, data,  1024)) < 0)
        {
            perror("Reading stream message");
        }
        else if (rval == 0)
            printf("Ending connection\n");
        else {
            //printf("-->%s\n", data);
            char *id, *local = NULL;
            id = strtok(data,separator);
            local = strtok(NULL,separator);
            short signed local_ = atoi(local);
            
            Train *t = malloc(sizeof(Train));
            for (int i = 0; i < MAX_LENGTH_ID; i++) {
                t -> id[i] = id[i];
            }
            t -> local = local_;
            t -> eoa = 100;
            bool is_added = add_to_rbc(t);
            if (!is_added){
                update_local_rbc(t -> id, t -> local);
            }
            if (t -> local == 100)
            {
                remove_from_rbc(t);
            }
            update_eoa_rbc();

            /* Go through array of trains to get the right number of train*/
            for(int i =0; i<trains.nb_trains; i++)
            {
                if(strncmp(trains.trains[i] -> id,t -> id,MAX_LENGTH_ID)){
                    number_train = i;
                    break;
                }
            }
            if (trains.trains[number_train] -> eoa <= trains.trains[number_train] -> local)
            {
                puts("Arrêt du train");
                signal = "STOP";
            }
        }
    } while (rval > 0);
    puts("Connection ended");
    close(datasock);
	free(sock);	
    return 0;
}


bool add_to_rbc(Train *t)
{
    // We first check if the train is not already in our structure
    for (int i = 0; i < (trains.nb_trains); i++){
        if (strncmp(t -> id, (trains.trains)[i] -> id, MAX_LENGTH_ID) == 0){
            //perror("The train has not been added because it was already registered.\n");
            return false;
        }
    }
    // Then if the numebr of trains is less than 100, we add the new train to the structure
    if ((trains.nb_trains) < 100){
        // We add the train at the right place (trains.trains is sorted by growing localisation)
        int j = trains.nb_trains;
        for (int i = 0; i < (trains.nb_trains); i++){
            if ((trains.trains[i] -> local) > (t -> local)){
                j = i;
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
        perror("Max trains has been reached ! Train not added !\n");
        return false;
    }
}

bool remove_from_rbc(Train *t)
{
    bool removable = false;
    int i;
    for (i = 0; i < (trains.nb_trains); i++){
        if (strncmp(t -> id, (trains.trains)[i] -> id, MAX_LENGTH_ID) == 0)
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
        perror("The train doesn't exist !\n");
        return false;
    }
}

bool update_local_rbc(char* id, short local)
{
    for (int i=0; i < (trains.nb_trains); i++){
        if (strncmp(id, (trains.trains)[i] -> id, MAX_LENGTH_ID) == 0){
            (trains.trains)[i] -> local = local;
            //perror("The localisation has been updated.\n");
            return true;
        }
    }
    perror("The train has not been found.\n");
    return false;
}

bool update_eoa_rbc(void){
    // The structure trains.trains must be sorted by growing local
    for (int i=0; i < (trains.nb_trains) - 1; i++){
        (trains.trains)[i] -> eoa = ((trains.trains)[i+1] -> local) - 1;
    }
    //perror("The EOA has been updated.\n");
    return true;
}

void* print_trains(void* arg){
    while (1) {
        printf("NAME   LOC EOA\n");
        for (int i = 0; i < (trains.nb_trains); i++) {
            printf("%s %d %d\n", (trains.trains)[i] -> id, (trains.trains)[i] -> local, (trains.trains)[i] -> eoa);
        }
        sleep(1);    
    }
}


int main()
{

    /* Initialization of the structure trains */
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
    
    pthread_t thread;
    pthread_create(&thread, NULL, print_trains, NULL);

    /* Accepting incoming connections */
    listen(sock, MAX_REQUEST);
    int c = sizeof(struct sockaddr_in);
    int new_socket;
    while ((new_socket = accept(sock, (struct sockaddr *)&client, (socklen_t*)&c)))
    {
        pthread_t thread;
        int *new_sock = malloc(1);
        *new_sock = new_socket;

        /* Start a new thread to handle the connection */
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
    pthread_join(thread,NULL);
    return 0;
}