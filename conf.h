

#ifndef STA_TEA_CONF_H
#define STA_TEA_CONF_H

typedef int bool;
#define true 1
#define false 0

#define PORT_NUMBER 4242
#define SIZEOF_MSG 1024

//code reqack
#define REQUEST 10
#define RESPONSE 20
#define ERROR 50

//code message : entier
#define ADD_TRAIN 1
#define DELETE_TRAIN 2
#define LOCATION_REPORT 3
#define MOVEMENT 4

//building the message
#define SEPARATOR ":"
#define EOM "$"
#define MAX_SIZE 6

bool send_data(int socket, int reqack, int entier, char *id, char* local, char* speed);
char *str_sub (const char *s, unsigned int start, unsigned int end);

char *str_sub (const char *s, unsigned int start, unsigned int end) {
    char *new_s = NULL;
    if (s != NULL && start < end)
    {
        new_s = malloc(sizeof(*new_s) * (end - start + 2));
        if (new_s != NULL)
        {
            int i;
            for (i = start; i <= end; i++)
            {
                new_s[i - start] = s[i];
            }
            new_s[i - start] = '\0';
        }
        else
        {
            fprintf(stderr, "Memoire insuffisante\n");
            exit(EXIT_FAILURE);
        }
    }
    else{
        printf("Erreur d'arguments\n");
        exit(EXIT_FAILURE);
    }
    return new_s;
}

bool send_data(int socket, int reqack, int entier, char *id, char* local, char* speed){
    char data[SIZEOF_MSG] = "";
    sprintf(data, "%d", reqack);
    char temp[2] = "";
    sprintf(temp, "%d", entier);
    strcat(data, temp);
    strcat(data, SEPARATOR);
    strcat(data, id);
    strcat(data, SEPARATOR);
    strcat(data, local);
    strcat(data, SEPARATOR);
    strcat(data, speed);
    strcat(data, SEPARATOR);
    strcat(data, EOM);

    if (send(socket, data, strlen(data), 0) < 0) {
        perror("Writing stream message");
        return false;
    }
    else {
        printf("Sending the following message : %s\n", data);
        return true;
    }
}

void parse_EOM(char data[], char* table[]) {
    char* token;
    int i = 0;

    /* get the first test */
    token = strtok(data, EOM);

    /* walk through other tests */
    while( token != NULL ) {
        i++;
        strcpy(table[i], token);
        token = strtok(NULL, EOM);
    }
}

void parse_data(char data[], int* reqack, int* entier, char** id, char** local, char** speed) {
    char *reqack_ = NULL, *entier_ = NULL;

    reqack_ = str_sub(data, 0, 1);
    entier_ = str_sub(data, 2, 3);
    *reqack = atoi(reqack_);
    *entier = atoi(entier_);
    strtok(data, SEPARATOR);
    *id = strtok(NULL, SEPARATOR);
    *local = strtok(NULL, SEPARATOR);
    *speed = strtok(NULL, SEPARATOR);
}

#endif
