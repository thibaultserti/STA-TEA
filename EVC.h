#ifndef DEF_EVC
#define DEF_EVC


#include "conf.h"

bool is_moving = false;
char* id;
char* localisation;
char* speed;

int SocketCreate(void);
void SocketConnect(int socket_desc, char* adresse_hote);
int SocketReceive(int socket, char* response, short rcvSize);


int get_localisation(void);
int get_speed(void);
void change_speed(void);
 #endif
