#ifndef DEF_RBC
#define DEF_RBC

#define MAX_LENG_ID 6
#define MAX_NB_TRAINS 100

typedef int bool;
#define true 1
#define false 0

typedef struct train
{
    char* id[MAX_LENG_ID];
    short signed local;
    short signed eoa;

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
bool check_eoa(void); /* send SIG_STOP if the train 2 is right behind the train 1; send SIG_CONTINUE otherwise */
bool update_eoa_rbc(void);



 #endif