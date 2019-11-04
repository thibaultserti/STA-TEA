#ifndef DEF_EVC
#define DEF_EVC


#include "conf.h"

bool is_moving = false;
char* id;
char* localisation;

int SocketCreate(void);
void SocketConnect(int socket_desc, char* adresse_hote);
int SocketReceive(int socket, char* response, short rcvSize);

 #endif
