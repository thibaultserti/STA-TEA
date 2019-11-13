#ifndef DEF_EVC
#define DEF_EVC


#include "conf.h"

#define ID_balises_3 0x33

#define DISTANCE_PARCOURS 50

/*
MC_Data8 cdmc_sourceNumeroBalise = {
	MC_ID_MESSAGE_EBT_RECEIVED, 
	SOURCE_NUMERO_BALISE,
};
*/

typedef struct TrainInfo
{
	float distance;  // en cm
	float vit_consigne;
	float vit_mesuree;
	int imp_mesuree;
	int nb_impulsions;
	int noBalise; //Rajout
}TrainInfo;

///longueurs des cantons 1 a 9 (grande boucle), en cm.
float d_tour = 167+ 190+ 226+ 162+ 161+ 213+ 184+ 163+ 279;
const int sectionsPos[] = {0,167, 357, 583, 745, 906, 1119, 1303, 1466}; 

int numero_balise;
float distance_prec;
float d0 = 0; 

struct timeval instant_init;
struct timeval instant_prec;
struct timeval instant;
unsigned char status, varDebug1, varDebug2;

float dtu;
float dts;
float delta_t;

struct TrainInfo train1;

bool is_moving = false;
char* id;
char* localisation;
char* speed;

int SocketCreate(void);
void SocketConnect(int socket_desc, char* adresse_hote);
int SocketReceive(int socket, char* response, short rcvSize);

float get_localisation(void);
float get_speed(void);
void change_speed(float speed_req);
void slow_down(void);

void* can(void* arg);
int WriteVitesseLimite(float vitesseLimite);
int WriteVitesseConsigne(unsigned int vitesse, unsigned char sens);
int  WriteTrameStatusRUNRP1(unsigned char status, unsigned char varDebug1, unsigned char varDebug2);
void TraitementDonnee2 (uCAN1_MSG *recCanMsg, TrainInfo *infos);


 #endif
