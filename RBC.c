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
#include <math.h>
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
    int num_train;
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
                printf("Received : %s\n", data);

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
                                    float localisation_ = atof(localisation);
                                    float speed_ = atoi(speed);

                                    for (int i = 0; i < MAX_LENGTH_ID; i++) {
                                        t -> id[i] = id[i];
                                    }
                                    t -> local = localisation_;
                                    t -> speed = speed_;
                                    bool is_added = add_to_rbc(t);

                                    if (is_added){
                                        update_local_rbc(t -> id, t -> local);
                                    }
                                    else {
                                        send_data(datasock, ERROR, ADD_TRAIN, id, localisation, speed);
                                    }

                                    /* Go through array of trains to get the right number of train*/
                                    num_train = get_num_train(t -> id);

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
                                    trains.trains[num_train] -> speed = atof(speed);
                                    trains.trains[num_train] -> local = atof(localisation);
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
            num_train = get_num_train(id);
            char* speed_requested = speed;
            sprintf(speed_requested, "%3.1f", speed_to_have(num_train));
            send_data(datasock, REQUEST, MOVEMENT, id, localisation, speed_requested);
            usleep(1500000);

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
        // We add the train at the right place (trains.trains is sorted by decreasing localisation)
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

/* Fonction d'affichage de l'état des trains */
void* print_trains(void* arg){
    int sock_print;
    struct sockaddr_in server_print;

    /* Create socket */
    sock_print = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_print < 0) {
        perror("Opening stream socket");
        //break;
    }

    /* Name socket */
    server_print.sin_family = AF_INET;
    server_print.sin_addr.s_addr = INADDR_ANY;
    server_print.sin_port = htons(PORT_NUMBER_PRINT);

    connect(sock_print, (struct sockaddr *)&server_print, sizeof(server_print));
    perror("Connection\n");


    while (1) {
        char data_print[SIZEOF_MSG] = "";

        printf("NAME   LOC    SPEED\n");
        for (int i = 0; i < (trains.nb_trains); i++) {
            printf("%s %4.1f %4.1f\n", (trains.trains)[i] -> id, (trains.trains)[i] -> local, (trains.trains)[i] -> speed);
            strcat(data_print, (trains.trains)[i] -> id);
            strcat(data_print, SEPARATOR);
            char temp[15] = "";
            printf("trains.trains : %f\n", (trains.trains)[i] -> local);
            sprintf(temp, "%f", (trains.trains)[i] -> local);
            printf("temp : %s\n", temp);
            strcat(data_print, temp);
            strcat(data_print, EOM);
            printf("%s\n", data_print);
        }
        send(sock_print, data_print, strlen(data_print),MSG_NOSIGNAL);
        sleep(1);
    }
}

float speed_to_have(int num_train){

    if (num_train == 0)
    {
        return 25.0;   
    }
    else {
    
        return consigne(trains.trains[num_train-1], trains.trains[num_train]);
    }
}

float distance(Train *t1, Train *t2)
{
	bool found1=false, found2=false;
	float a;
	float b;
	
	for (int i=0;i<(trains.nb_trains);i++) // we check if the trains exist
	{
		if (strncmp(t1->id,(trains.trains)[i]->id,MAX_LENGTH_ID)==0)
		{
			found1=true;
		}
		if (strncmp(t2->id,(trains.trains)[i]->id,MAX_LENGTH_ID)==0)
		{
			found2=true;
		}
	}
	
	if (found1 && found2) // if we found them
	{
		a=fabs(((*t1).local)-((*t2).local));//distance without crossing 0	
		if((t1->local)>(t2->local))//distance crossing 0
        {
			b=D_TOUR-(t1->local)+(t2->local);
		}		
		else 
		{
			b=D_TOUR-(t2->local)+(t1->local);
		}		
		if(b>a){ // the distance we want is the smaller
			return a; }
		else {
			return b; }
	}	
	else //if one or two trains have note been found
	{
		perror("One or several trains don't exist.\n");
		return -1;
	}
}

float consigne(Train *t1, Train *t2) {
    int d = 0;
    if(trains.nb_trains >= 2){
        d  = distance(t1, t2);
    }
    else{
        d = 1745;
    }

    int e = DIST_OPT - d;

    if (d < DIST_STOP)
    {
        printf("Emergency stop !");
        return 0;
    }
    else if (d < DIST_SLOW_DOWN)
    {
        printf("Slow mode");
        return 0.9 * (t1 -> speed);
    }
    else
    {
        printf("Regulation mode");
        float K = fabs(P / e * (t1 -> speed));
        if (K > 25)
        {
            return 25;
        }
        else
        {
            return K;
        }
    }
}

int get_num_train(char* id){
    int num_train = -1;
    for(int i =0; i<trains.nb_trains; i++){
        if(strncmp(trains.trains[i] -> id, id, MAX_LENGTH_ID) == 0){
            num_train = i;
            break;
        }
    }
    return num_train;
}

void timer_thread(union sigval arg)
{
    int i = 0;
    printf("Timer %d\n", i++);
}

void errno_abort(char* message)
{
    perror(message);
    exit(EXIT_FAILURE);
}

void create_timer(unsigned i)
{
    timer_t timer_id;
    int status;
    struct itimerspec ts;
    struct sigevent se;

    /*
     * Set the sigevent structure to cause the signal to be
     * delivered by creating a new thread.
     */
    se.sigev_notify = SIGEV_THREAD;
    se.sigev_value.sival_ptr = &timer_id;
    se.sigev_notify_function = timer_thread;
    se.sigev_notify_attributes = NULL;

    ts.it_value.tv_sec = 1;
    ts.it_value.tv_nsec = 0;
    ts.it_interval.tv_sec = 1;
    ts.it_interval.tv_nsec = 0;

    status = timer_create(CLOCK_REALTIME, &se, &timer_id);
    if (status == -1)
        errno_abort("Create timer");

    status = timer_settime(timer_id, 0, &ts, 0);
    if (status == -1)
        errno_abort("Set timer");
}

int main()
{
    pthread_t thread;

    //Set timer to trigger signal_handler
    create_timer(1);

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

    /* Create thread to print the table */
    pthread_create(&thread, NULL, print_trains, NULL);

    /* Accepting incoming connections */
    listen(sock, MAX_REQUEST);
    int c = sizeof(struct sockaddr_in);
    int new_socket;

    while ((new_socket = accept(sock, (struct sockaddr *)&client, (socklen_t*)&c)))
    {
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
