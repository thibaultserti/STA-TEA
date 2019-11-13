#ifndef CANLINUX_H
	#define CANLINUX_H
	
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdbool.h>
	#include <unistd.h>
	#include <string.h>
	#include <time.h>
	
	#include <net/if.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <sys/ioctl.h>
	#include <pthread.h>
	#include <linux/can.h>
	#include <linux/can/raw.h>
	
	#include <netinet/in.h>
	#include <netdb.h>
	
	#include <arpa/inet.h>
	
	#include "MESCAN1_VarTrain.h"
	//#define VERBOSE
	///Niveau de priorite de la trame CAN, 0(bas) -> 3(elevee)
	typedef enum 
	{
		CANLINUX_PRIORITY_HIGH =   0b11,
		CANLINUX_PRIORITY_MEDIUM = 0b10,
		CANLINUX_PRIORITY_LOW =    0b01,
		CANLINUX_PRIORITY_NONE =   0b00
	} CANLINUX_TX_PRIOIRTY;
	
	
	///Initialisation du CAN (#define VERBOSE contrôle la sortie de messages par console)<BR> retourne l'index du bus a utiliser par la suite.
	int canLinux_Init (char *portName);
	
	///Initialisation d'un filtre de trames par ID
	/**struct can_filter {
		canid_t can_id;
		canid_t can_mask;
	};
	longueur max: 512 (limite de la lib)*/
	void canLinux_InitFilter (int portCan, struct can_filter* rfilter, int longueur);
	
	/// transmets dans le bus CAN indique le contenu de sendCanMsg.

	/** Retourne true s'il a envoye la taille d'une trame CAN, sinon false <BR>Traite une seule trame CAN a la fois */
	bool ECAN1_transmit(int portCan, CANLINUX_TX_PRIOIRTY priority, uCAN1_MSG *sendCanMsg);
	
	/// Interroge le bus CAN indique et remplit le champ recCanMsg.

	/** Retourne true s'il a recupere des donnees, sinon false <BR>Traite une seule trame CAN a la fois */
	bool ECAN1_receive(int portCan, uCAN1_MSG *recCanMsg);
	
	/// Reconstruit un message plus grand a partir de trames CAN.

	/** Retourne:<BR> \li 0 si la reconstruction n'est pas finie
		\li 1 quand c'est fini
		\li -1 Si la trame CAN a deja ete recue (a traiter selon contexte)
		\li -2 Si la taille specifiee ou l'identifiant de la trame CAN ne correspondent pas<BR>Traite une seule trame CAN a la fois, elles peuvent arriver dans le desordre */
	short ECAN1_reconstructMessage(uCAN1_MSG *recCanMsg, char* destinationArray, short startIDFrame, short messageLength);
	
	///Decoupage d'un message en trames CAN et generation de checksum et de longueur de message
	
	/** Retourne true quand le decoupage du message est fini<BR>
		a chaque appel a la fonction, actualise la valeur de sendCanMsg pour l'envoyer par la suite
		\bug le buffer du MCP2515 se remplit, a partir de 80 octets de message (dataArray) des trames sont jetees. Ajouter un delay d'au moins 70µs entre le decoupage et l'envoi pour garantir l'envoi de 100 octets*/
	bool ECAN1_sliceMessage(uCAN1_MSG *sendCanMsg, char* headerArray, char* dataArray, short startIDFrame, short messageLength);
	
	
#endif