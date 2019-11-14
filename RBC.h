#ifndef DEF_RBC
#define DEF_RBC

#include "conf.h"

#define MAX_LENGTH_ID 6
#define MAX_NB_TRAINS 100
#define MAX_REQUEST 5

#define DIST_INTER_TRAIN
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
int distance (Train *t1,Train *t2);
float speed_to_have(int num_train);
int get_num_train(char* id);

void timer_thread(union sigval arg);
void errno_abort(char* message);
void create_timer(unsigned i);


#endif
