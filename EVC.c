#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>

#include "Libs_Unirail/CAN/canLinux.h"
#include "Libs_Unirail/CAN/MESCAN1_VarTrain.h"
#include "Libs_Unirail/CAN/MESCAN1_MAIN_PARAMS.h"
#include "Libs_Unirail/CAN/MESCAN1_DefinitionVariable.h"
#include "EVC.h"


int main(int argc , char *argv[]) {
    id = argv[2];
    localisation = argv[3];
    speed = argv[4];
    Fifo *fifoRequests = initialisation();
    int socket_desc;
    int connection;
    int rval;
    int reqack, entier;
    char data[SIZEOF_MSG];
    char* message;
    pthread_t thread;
    pthread_create(&thread, NULL, can, NULL);

    do {


        printf("Trying to connect to RBC\n");

        //Création de la socket
        socket_desc = SocketCreate();
        //Vérification de la création
        if (socket_desc == -1) {
            perror("Could not create socket\n");
            //on reprend la boucle while
            continue;
        }

        //Connection au server
        SocketConnect(socket_desc, argv[1]);

        printf("Connected\n");

        if (!(send_data(socket_desc, REQUEST, ADD_TRAIN, id, localisation, speed))){
            continue;
        }
        connection = SocketReceive(socket_desc, data, SIZEOF_MSG);
        /* Listening to RBC */
        do {
            sprintf(speed, "%3.1f", get_speed());
            sprintf(localisation, "%3.1f", get_localisation());
            send_data(socket_desc, REQUEST, LOCATION_REPORT, id, localisation, speed);

            data[0] = '\0';
            memset(data, 0, sizeof(data));
            rval = read(socket_desc, data, SIZEOF_MSG);
            if (rval < 0) {
                perror("Reading stream message");
            } else if (rval == 0) {
                perror("Ending connection\n");
                break;
            } else {
                //printf("Received : %s\n", data);

                parse_EOM(fifoRequests, data);

                message = defiler(fifoRequests);

                while (message!= NULL) {
                    parse_data(message, &reqack, &entier, &id, &localisation, &speed);
                    switch (entier) {
                        case ADD_TRAIN :
                            switch (reqack) {
                                case RESPONSE :
                                    printf("Train added\n");
                                    break;
                                case ERROR :
                                    perror("Too many trains !\n");
                                    exit(0);
                            }
                            break;

                        case LOCATION_REPORT :
                            switch (reqack) {
                                case RESPONSE :
                                    //printf("Position has been transmitted\n");
                                    break;
                                case ERROR :
                                    break;
                            }
                            break;
                            //This use case is not a part of the project
                            /*case DELETE_TRAIN :
                                switch (reqack){
                                    case REQUEST :
                                        break;
                                    case RESPONSE :
                                        break;
                                    case ERROR :
                                        break;

                                }
                                break;*/

                        case MOVEMENT :
                            switch (reqack) {
                                case REQUEST :
                                    send_data(socket_desc, RESPONSE, MOVEMENT, id, localisation, speed);
                                    change_speed();
                                    break;
                                case ERROR :
                                    break;
                            }
                            break;
                    }
                    message = defiler(fifoRequests);
                }
            }
        
        }while (true);

        //Vérification de la connexion
        if (connection == 0) {
            perror("Ending connection\n");
            continue;
        }

    } while (true);
    pthread_join(thread, NULL);
    return 1;
}


int SocketCreate(void)
{
    int new_socket;
    //Create socket
    new_socket = socket(AF_INET, SOCK_STREAM, 0);
    return new_socket;
}

void SocketConnect(int socket_desc, char* adresse_hote)
{
    int return_value = -1;
    struct sockaddr_in server;
    server.sin_addr.s_addr = inet_addr(adresse_hote);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT_NUMBER);
    //Vérification de la connection
    while (true)
    {
        return_value = connect(socket_desc, (struct sockaddr *)&server, sizeof(server));
        perror("Connection\n");
        if(return_value<0)
        {
            printf("Could not connect to RBC\n");
        }
        if(return_value == 0)
        {
            break;

        }
        sleep(3);
    }
}

int SocketReceive(int socket, char* response, short rcvSize)
{
    int rcv = -1;
    while(rcv<0)
    {
        rcv = read(socket, response, rcvSize-1);
        if(rcv < 0) /*Vérification nécessaire mais pas élégante. L'idéal serait de pouvoir exécuter une instruction
            qu'après la première instance du while */
        {
            perror("Reading stream message");
            slow_down();
            return 0;
        }
        if (rcv == 0)
        {
            perror("Ending connection in receive\n");
            return 0;
        }
    }
    return 1;
}

float get_localisation(void){
    float localisation = train1.distance;
    return localisation;
}
float get_speed(void){
    float speed = train1.vit_mesuree ;
    return speed;
}

void change_speed(void) {

}

void slow_down(void) {

}

void* can(void* arg){
    // ------------------------------CAN---------------------------------
    gettimeofday(&instant_init,NULL);	
	gettimeofday(&instant_prec,NULL);	
	uCAN1_MSG recCanMsg;
	int fd;
	struct ifreq ifr;
	int canPort;
	char *NomPort = "can0";
	struct can_filter rfilter[2]; 
	rfilter[0].can_id   = 0x02F;
	rfilter[0].can_mask = CAN_SFF_MASK;
	rfilter[1].can_id   = 0x033;
	rfilter[1].can_mask = CAN_SFF_MASK;

	int consigne_rbc=20;

	train1.distance =0;
	train1.vit_consigne =0;
	train1.imp_mesuree =0;
	train1.nb_impulsions =0;
	train1.vit_mesuree=0;
	
 
    printf("je suis dans main \n");

    fd = socket(AF_INET, SOCK_DGRAM, 0);

    /* I want to get an IPv4 IP address */
    ifr.ifr_addr.sa_family = AF_INET;

    /* I want IP address attached to "wlan1" */
    strncpy(ifr.ifr_name, "wlan1", IFNAMSIZ-1);
    ioctl(fd, SIOCGIFADDR, &ifr);
    close(fd);

    /* display result */
    printf("mon IP WLAN1 : %s\n", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));

    /* Start CAN bus connexion */
    canPort = canLinux_Init(NomPort);
	canLinux_InitFilter(canPort, rfilter, sizeof(rfilter));
	/* Unlock speed limits */
    WriteVitesseLimite(MAX_CONSIGNE_VITESSE_AUTORISEE);
    usleep(150000); //150ms
    
    while(1)
    {
		if(ECAN1_receive(canPort, &recCanMsg))
		{
			//printf("Lecture trame CAN.\n");
			TraitementDonnee2(&recCanMsg, &train1);
			WriteVitesseConsigne(consigne_rbc, 1);
			
		}
    usleep(15000); //Sampling period ~= 17ms
	}
	WriteVitesseConsigne(0, 1);

    close(canPort);
	printf("EXIT\n");

    // ------------------------------------------------------------------
}

//////////////////////////////////////////
/// Ecriture de la Trame vitesse limite
///////////////////////////////////////////
int WriteVitesseLimite(float vitesseLimite)
{

	char *ifname = "can0";
	int portNumber = canLinux_Init(ifname);
	uCAN1_MSG consigneUrgence;
	
	if(vitesseLimite > MAX_CONSIGNE_VITESSE_AUTORISEE) //vitesse superieur a 50 cm/s
	vitesseLimite = MAX_CONSIGNE_VITESSE_AUTORISEE;                   
	
	consigneUrgence.frame.id  = MC_ID_CONSIGNE_VITESSE_LIMITE;
	consigneUrgence.frame.dlc = MC_DLC_CONSIGNE_VITESSE_LIMITE;
	MESCAN_SetData8(&consigneUrgence, cdmc_consigneVitesseLimite, vitesseLimite);
	
	ECAN1_transmit(portNumber, CANLINUX_PRIORITY_HIGH, &consigneUrgence);
	close(portNumber);
	return 1;
}

//////////////////////////////////////////
/// Ecriture de la Trame Consigne
///////////////////////////////////////////
int WriteVitesseConsigne(unsigned int vitesse, unsigned char sens)
{
	
	char *ifname = "can0";
	int portNumber = canLinux_Init(ifname);
	uCAN1_MSG consigneVitesse;

	if(vitesse>MAX_CONSIGNE_VITESSE_AUTORISEE) //vitesse supÃ©rieur Ã  50 cm/s
		vitesse = MAX_CONSIGNE_VITESSE_AUTORISEE;
	
	consigneVitesse.frame.id  = MC_ID_CONSIGNE_VITESSE;
	consigneVitesse.frame.dlc = MC_DLC_CONSIGNE_VITESSE;
	MESCAN_SetData8(&consigneVitesse, cdmc_consigneVitesse, vitesse);
	MESCAN_SetBit(&consigneVitesse, bdmc_sensDeplacementLoco, sens);
	
	ECAN1_transmit(portNumber, CANLINUX_PRIORITY_HIGH, &consigneVitesse);
	close(portNumber);
	return 1;
}


//////////////////////////////////////////
/// Envoi de la trame status de RPI1
///////////////////////////////////////////
int  WriteTrameStatusRUNRP1(unsigned char status, unsigned char varDebug1, unsigned char varDebug2)
{
	char *ifname = "can0";
	int portNumber = canLinux_Init(ifname);
	uCAN1_MSG trameStatusRP1;
	trameStatusRP1.frame.id  = MC_ID_RP1_STATUS_RUN;
	trameStatusRP1.frame.dlc = MC_DLC_RP1_STATUS_RUN;
	MESCAN_SetData8(&trameStatusRP1, cdmc_RP1_erreurs, 0);
	MESCAN_SetData8(&trameStatusRP1, cdmc_RP1_warnings, 0);
	MESCAN_SetBit(&trameStatusRP1, bdmc_RP1_etatConnexionWIFI, 1);
	MESCAN_SetData8(&trameStatusRP1, cdmc_RP1_configONBOARD, status);
	MESCAN_SetData8(&trameStatusRP1, cdmc_RP1_var1Debug, varDebug1);
	MESCAN_SetData8(&trameStatusRP1, cdmc_RP1_var2Debug, varDebug2);
	
	ECAN1_transmit(portNumber, CANLINUX_PRIORITY_HIGH, &trameStatusRP1);
	close(portNumber);
	return 1;	
}

//////////////////////////////////////////
/// Identification de la trame CAN
///////////////////////////////////////////


void TraitementDonnee2 (uCAN1_MSG *recCanMsg, TrainInfo *infos)
{
	gettimeofday(&instant,NULL);	
		if (recCanMsg->frame.id == ID_balises_3){
			printf("TRAME CAN : %u\n", recCanMsg->frame.id);
		}

    	switch (recCanMsg->frame.id)
	    {
			/** Recuperer Info BALISE  **/
			case ID_balises_3 :

				//MAJ_Info_BALISE (XXX);
				//numero_balise = (int)MESCAN_GetData8(recCanMsg, cdmc_sourceNumeroBalise);//Le NUMERO DE LA BALISE
				numero_balise = recCanMsg->frame.data5;//Le NUMERO DE LA BALISE
				printf("\nBalise n°%d", numero_balise);
				infos-> nb_impulsions = 0;

				/*if (numero_balise==1 && !PremiereBalise){
					nb_tour+=1;
				}*/
				for (int i=0;i<numero_balise;i++)
				{
					printf("MODIFICATIONS CD VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV");
					infos->distance += sectionsLength[i];	
				}
				
				break ;

			case MC_ID_MESSAGE_GSM_RECEIVED:
				//MAJ_GSMR(XXX);
				break;

			case MC_ID_SCHEDULEUR_MESURES  : /** Envoi la vitesse instantannÃ©e (consigne vitesse) ,	le nombre dâ€™impulsions, la vitesse mesurÃ©e, lâ€™erreur du PID **/
				if(MESCAN_GetData8(recCanMsg, cdmc_ordonnancementId)==MC_ID_RP1_STATUS_RUN)
					WriteTrameStatusRUNRP1(status, varDebug1, varDebug2);
				infos-> imp_mesuree= (int)MESCAN_GetData8(recCanMsg, cdmc_vitesseMesuree);/** le nbre d'implusion envoyÃ© ici
				// est le nombre d'impulsion entre 2 mesures **/
				infos-> nb_impulsions+= infos-> imp_mesuree;
				infos-> distance += PAS_ROUE_CODEUSE * (infos->nb_impulsions);
				infos-> vit_consigne = (float)MESCAN_GetData8(recCanMsg, cdmc_vitesseConsigneInterne);
				//printf("Actualisation: Postition: %lf, Vit: %d \n", infos-> distance, infos-> imp_mesuree);
				break;

			default :
				printf("frame est de can id %X \n",recCanMsg->frame.id);
				break;
		}
	
	if(DISTANCE_PARCOURS-infos->distance)
	{
		infos->vit_mesuree=(d_tour-distance_prec+(infos->distance))/(instant.tv_sec-instant_prec.tv_sec);	

	}
	else
	{
		infos->vit_mesuree=((infos->distance)-distance_prec)/((instant.tv_sec)-(instant_prec.tv_sec));	
	}
	
	distance_prec=infos->distance;
	instant_prec = instant;
	// AFFICHAGE
	printf("\nT = %lu s\n", instant.tv_sec - instant_init.tv_sec);
	//printf("Vitesse : %lf cm/s\n",  infos->vit_mesuree);
	//printf("Position : %lf cm \n",  infos->distance);
}