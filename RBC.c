#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <sys/time.h>
#include "RBC.h"

Trains trains;
int speed;

void timer();

/*
 * This will handle connection for each client
 * */
void* connection_handler(void *sock)
{
    int datasock = *(int*)sock;
    int rval;
    int reqack, entier;
    char *id = NULL, *localisation = NULL, *speed = NULL;
    char *message;
    Fifo *fifoRequests = initialisation();

    char data[SIZEOF_MSG];
    Train *t = malloc(sizeof(Train));

    if (datasock == -1) {
        perror("Accept");
    } else do {

            data[0] = '\0';
            /* Receive first request from EVC */
            memset(data, 0, sizeof(data));
            rval = read(datasock, data, SIZEOF_MSG);
            if (rval<0)
            {
                perror("Reading stream message");
            }
            else if (rval == 0)
            {
                perror("Ending connection\n");
            }
            else
            {
                //printf("Received : %s\n", data);

                parse_EOM(fifoRequests, data);

                message = defiler(fifoRequests);
                while(message!=NULL )
                {
                    parse_data(message, &reqack, &entier, &id, &localisation, &speed);
                    switch(entier){
                        case ADD_TRAIN :
                            switch (reqack){
                                case REQUEST :
                                    ;
                                    short signed localisation_ = atoi(localisation);
                                    short signed speed_ = atoi(speed);

                                    for (int i = 0; i < MAX_LENGTH_ID; i++) {
                                        t -> id[i] = id[i];
                                    }
                                    t -> local = localisation_;
                                    t -> eoa = 100;
                                    t -> speed = speed_;
                                    bool is_added = add_to_rbc(t);

                                    if (is_added){
                                        update_local_rbc(t -> id, t -> local);
                                    }
                                    else {
                                        send_data(datasock, ERROR, ADD_TRAIN, id, localisation, speed);
                                    }

                                    update_eoa_rbc();
                                    /* Go through array of trains to get the right number of train*/
                                    for(int i =0; i<trains.nb_trains; i++)
                                    {
                                        if(strncmp(trains.trains[i] -> id, t -> id, MAX_LENGTH_ID) == 0){
                                            //num_train = i;
                                            break;
                                        }
                                    }

                                    /* Send validation request to EVC */
                                    send_data(datasock, RESPONSE, ADD_TRAIN, id, localisation, speed);
                                    break;
                                case ERROR :
                                    break;
                            }
                            break;

                        case LOCATION_REPORT :
                            switch (reqack){
                                case REQUEST :
                                    send_data(datasock, RESPONSE, LOCATION_REPORT, id, localisation, speed);
                                    break;
                                case RESPONSE :
                                    break;
                            }
                            break;

                        case MOVEMENT :
                            switch (reqack){
                                case RESPONSE :
                                    //printf("The speed request has been sent\n");
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

                    }
                    message = defiler(fifoRequests);
                }
            }
            char* speed_requested = speed;
            sprintf(speed_requested, "%d", speed_to_have());
            send_data(datasock, REQUEST, MOVEMENT, id, localisation, speed_requested);

        } while (rval > 0);
    puts("Connection ended");
    shutdown(datasock, 0);
    shutdown(datasock, 1);
    shutdown(datasock, 2);
    free(sock);
    return 0;
}


bool add_to_rbc(Train *t)
{
    // We first check if the train is not already in our structure
    for (int i = 0; i < (trains.nb_trains); i++){
        if (strncmp(t -> id, (trains.trains)[i] -> id, MAX_LENGTH_ID) == 0){
            //perror("The train has not been added because it was already registered.\n");
            return true;
        }
    }
    // Then if the number of trains is less than 100, we add the new train to the structure
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

int speed_to_have(void){
    //speed ++;
    return speed;
}

void handler_signal(int cur){
    static int count = 0;
    printf ("timer expired %d times\n", count++);
}

void timer() {
    struct sigaction sa;
    struct itimerval timer;

    /* Install timer_handler as the signal handler for SIGVTALRM. */
    memset (&sa, 0, sizeof (sa));
    sa.sa_handler = &handler_signal;
    sigaction (SIGVTALRM, &sa, NULL);

    /* Configure the timer to expire after 250 msec... */
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 250000;
    /* ... and every 250 msec after that. */
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 250000;
    /* Start a virtual timer. It counts down whenever this process is
      executing. */
    setitimer (ITIMER_VIRTUAL, &timer, NULL);
}

int main()
{

    //Set timer to trigger signal_handler
    timer();

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
    server.sin_port = htons(PORT_NUMBER);

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
