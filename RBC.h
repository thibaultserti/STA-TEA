#ifndef DEF_RBC
#define DEF_RBC

#include "conf.h"

#define MAX_LENGTH_ID 6
#define MAX_NB_TRAINS 100
#define MAX_REQUEST 5
#define PORT_NUMBER_PRINT 9000

#define DIST_OPT 300
#define DIST_STOP 150
#define DIST_SLOW_DOWN 200
#define P 150 // gain

typedef struct train
{
    char id[MAX_LENGTH_ID+1];
    float local;
    float speed;

} 
Train;

typedef struct trains
{
    Train* trains[MAX_NB_TRAINS];
    int nb_trains;
}
Trains;

void* connection_handler(void *sock);

bool add_to_rbc(Train *t);
bool remove_from_rbc(Train *t);
bool update_local_rbc(char* id, short local);
void* print_trains(void *arg);
float distance (Train *t1,Train *t2);
float speed_to_have(int num_train);
int get_num_train(char* id);
float consigne(Train *t1, Train *t2);

void timer_thread(union sigval arg);
void errno_abort(char* message);
void create_timer(unsigned i);


#endif
