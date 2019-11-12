#ifndef DEF_RBC
#define DEF_RBC

#include "conf.h"

#define MAX_LENGTH_ID 6
#define MAX_NB_TRAINS 100
#define MAX_REQUEST 5

typedef struct train
{
    char id[MAX_LENGTH_ID+1];
    short signed local;
    short signed eoa;
    short signed speed;

} 
Train;

typedef struct trains
{
    Train* trains[MAX_NB_TRAINS];
    int nb_trains;
}
Trains;

//bool init_connection();
bool add_to_rbc(Train *t);
bool remove_from_rbc(Train *t);
bool update_local_rbc(char* id, short local);
bool update_eoa_rbc(void);
void* connection_handler(void *sock);
void* print_trains(void *arg);
int speed_to_have(void);
void create_timer(unsigned i);

#endif
