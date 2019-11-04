

#ifndef STA_TEA_CONF_H
#define STA_TEA_CONF_H

typedef int bool;
#define true 1
#define false 0

#define PORT_NUMBER 4242
#define SIZEOF_MSG 1024

//code reqack
#define REQUEST 0
#define RESPONSE 1

//code message : entier
#define ADD_TRAIN 1
#define DELETE_TRAIN 2
#define LOCATION_REPORT 3
#define MOVEMENT 4

#endif
