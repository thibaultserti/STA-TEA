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
    int i = 0;
}

int main()
{
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