#ifndef XBEE_H
#define XBEE_H
//#define MC802

#if defined (MC802)
	#include <xc.h>
	#include "../../UART.h"
#endif
#define	START_DELIMITER_FRAME_XB									0x7E
//FrameTypes de reception (omision des types adresses 64 bit)
#define	FRAME_TYPE_RX16_BITS_ADR									0x81
#define	AT_COMMAND_RESPONSE											0x88
#define	TX_STATUS_FRAME_ACK_RF										0x89
#define	FRAME_TYPE_MODEM_STATUS										0x8A
#define	REMOTE_COMMAND_RESPONSE										0x97

//FrameTypes d'envoi (omision des types adresses 64 bit)
#define	TX_REQUEST_16BITS_ADR										0x01
#define	AT_COMMAND_FRAME											0x08
#define	AT_COMMAND_QUEUE_FRAME										0x09
#define	REMOTE_AT_COMMAND_REQUEST_FRAME								0x17
//Options d'envoi (avec ACK ou pas, )
#define	OPTION_TX_REQUEST_FRAME_DISABLE_ACK							0x01
#define	OPTION_TX_REQUEST_FRAME_BROADCAST_PAN						0x04

#define	MAX_DATAS_RF_PACKET											100

/**Choix de 256:
    On lit un octet pour determiner une longueur de tableau
    Ensuite tout est calculer a partir de cette longueur
		
    Si la valeur lue est erronnee et plus grande que celle prevue max
    On aura un debordement de tableau et le CRASH logiciel
    De cette facon, aucun debordement possible
    \bug la longueur de trame maximale est de 100 octets!!
 */
#define	LEN_TAB_TX_PACKET_XB					256	//Doit etre pair!!!!!

//Ici ce tableau n est pas reconstitue avec des datas lues
// donc pas de debordement possible
#define	LEN_TAB_RX_PACKET_XB				120	//Doit etre pair!!!!!

#define	RAS				0
#define	ERREUR          1

//Trame CAN Schadows ou Ghost
//Une trame CAN shadows sera decode et envoyé sur le Bus
//Une trame CAN ghost sera decode et interpretee d'une facon pre-definie
//ou pour pouvoir executer des commandes speciales
//Exemple la trame CAN "mc_consigneVitesse":
//      Mode Shadows --> Recopie sur le bus CAN
//      Mode Ghost --> Mise à jour des flags et datas de la trame "mc_GSM_statusRun"

/**
    <table>
    <caption id="RX_packet_format">Packet format</caption>
    <tr><th>Desc 	<th>Delimeter 	<th>LenPacket 	<th>OptionFrameType  	<th>AdrSource	<th>RSSI 	<th>Options <th>ReceivePacketData 	<th>CKS 	<th><th>FrameId_IdentifiUARTdataFrameBeingReported <th>ReponseACK_EtatLowSiGoodACK
    <tr><td>Taille 	<td>1 			<td>2 			<td>1 					<td>2 			<td>1 		<td>1 		<td>n<100 octets 		<td>1 		<td><td>1											<td>1
    <tr><td>Comments <td>Non inclus dans le struct <td>MSB+LSB  <td> Voir doc sur type de trames <td>MSB+LSB <td>puissance de signal en dBm <td>Bit 1:Addr. broadcast Bit 2:PAN broadcast<td>Message (int16 ou char)<td>checksum<td><td>??<td>??
    </table>
 */
/**\bug int dans RPi est 4 ou 8 octets!! => Changement vers short (unsigned) int, 
en particulier pour wReceivePacketData (entre 240 et 360 octets gaspilles)*/

/**
\todo FrameId_IdentifiUARTdataFrameBeingReported?
\todo il faut ajouter le type de message (CAN shadows, GSM-R  ou ATCommandXBEE) */
typedef struct {
    unsigned short  LenPacket;
    unsigned char   OptionFrameType;
    unsigned short  AdrSource;
    unsigned char   RSSI;
    unsigned char   Options;
    unsigned char   StatusCom;
    unsigned char   FrameId_IdentifiUARTdataFrameBeingReported;
    unsigned char   ReponseACK_EtatLowSiGoodACK;
    unsigned char   CKS;

    //Dans le tableau de datas suivants, La premiere data d'indice ZERO indique
    //Le type de trame datas RF que l'on a recu (TROIS types possibles)

    //  0x3E: Reception d'un codage de trame CAN qu'il faudra envoyer
    //  le bus
    //  0x3F: Reception d'un codage de trame CAN qu'il faudra interpreter
    //  Autres: Correspond a un numero de SUBSET GSM-R

    union {
        unsigned char   bReceivePacketData[MAX_DATAS_RF_PACKET];
        unsigned short  wReceivePacketData[MAX_DATAS_RF_PACKET >> 1];
    };
} xBeeReceivePacket;

/**
    <table>
    <caption id="TX_packet_format">Packet format</caption>
    <tr><th>Desc 	<th>Delimeter 	<th>LenPacket 	<th>FrameID  	<th>AdrDest	<th>Options <th>SendPacketData 	<th>CKS
    <tr><td>Taille 	<td>1 			<td>2 			<td>1 			<td>2 		<td>1 		<td>n<100 octets 	<td>1
    <tr><td>Comments <td>Non inclus dans le struct <td>MSB+LSB  <td> Voir doc sur type de trames <td>MSB+LSB <td>0x01: No ACK 0x04:PAN ID broadcast<td>Message (int16 ou char)<td>Non inclus dans le struct
    </table>
 */
typedef struct {
    unsigned short LenPacket;
    unsigned char FrameID;
    unsigned short AdrDest;
    unsigned char Options;

    union {
        unsigned char bSendPacketData[MAX_DATAS_RF_PACKET];
        unsigned short wSendPacketData[MAX_DATAS_RF_PACKET >> 1];
    };
} xBeeSendPacket;


///ETAT_RECEPETION_UART: Controle le stade du decodage
/**0->WAIT_START_DELIMITER_FRAME_XB<BR>
    101->RX_MSB_LEN_MESSAGE<BR>
    102->RX_LSB_LEN_MESSAGE<BR>
    103->RX_FRAME_TYPE<BR>
    <HR>Etats reception message XBEE (code 0x81 doc XBEE)<BR>
    104->RX_MSB_SOURCE_ADR<BR>
    105->RX_LSB_SOURCE_ADR<BR>
    106->RX_RSSI<BR>
    107->RX_OPTIONS<BR>
    108->RX_DATA1_MESSAGE<BR>
    109->RX_DATAS_MESSAGE_GSM<BR>
    110->RX_CKS<BR>
    <HR>Etats reception CAN SHADOWS<BR>
    400->RX_DATAS_MESCAN_SHADOWS<BR>
    <HR>Etats reception ACK XBEE (code 0x89 doc XBEE)<BR>
    200->RX_ACKXBEE_ID_ACK<BR>
    201->RX_ACKXBEE_STATE<BR>
    202->RX_ACKXBEE_CKS<BR>
    <HR>Etats reception ATCommand XBEE (code 0x88 doc XBEE)<BR>
    300->RX_ATCOMMAND_ID_ATCOMMAND<BR>
    301->RX_ATCOMMAND_1<BR>
    302->RX_ATCOMMAND_2<BR>
    303->RX_ATCOMMAND_STATUS<BR>
    304->RX_ATCOMMAND_DATAS<BR>
 */

/**\todo generaliser pour modem status frame (0x8A) et Remote command response (0x97)?
 */
enum ETAT_RECEPETION_UART {
    WAIT_START_DELIMITER_FRAME_XB = 0,
    RX_MSB_LEN_MESSAGE = 1,
    RX_LSB_LEN_MESSAGE = 2,
    RX_FRAME_TYPE = 3,
    RX_MSB_SOURCE_ADR = 4,
    RX_LSB_SOURCE_ADR = 5,
    RX_RSSI = 6,
    RX_OPTIONS = 7,
    ///\todo si data =0x3E c'est une trame CAN et remplissage du tableau "trame CAN". Sinon, tableau GSM-R
    RX_DATA_TYPE_TRAME_RF = 0x10,
    RX_DATAS_MESSAGE = 0x11,
    RX_CKS = 0x12,

    RX_ACKXBEE_ID_ACK = 0x20,
    RX_ACKXBEE_STATE = 0x21,
    RX_ACKXBEE_CKS = 0x22,
    
    RX_ATCOMMAND_ID_ATCOMMAND = 0x30,
    RX_ATCOMMAND_1 = 0x31,
    RX_ATCOMMAND_2 = 0x32,
    RX_ATCOMMAND_STATUS = 0x33,
    RX_ATCOMMAND_DATAS = 0x34,
};
///TYPE_TRAME: Selectionne le type de trame (octet 4)

/**
    0x01->SEND_DATA_16BIT_ADDRESS<BR>
    0x08->SEND_AT_COMMAND_REQUEST<BR>
    0x09->SEND_AT_COMMAND_QUEUE<BR>
    0x17->SEND_REMOTE_AT_COMMAND_REQUEST<BR>
    0x81->RECEIVE_DATA_16BIT_ADDRESS<BR>
    0x83->RECEIVE_DATA_16BIT_ADDRESS_IO<BR>
    0x88->RECEIVE_COMMAND_RESPONSE<BR>
    0x89->TRANSMISSION_STATUS_FRAME<BR>
    0x8A->MODEM_STATUS_FRAME<BR>
    0x97->RECEIVE_REMOTE_COMMAND_RESPONSE<BR>
 */
enum TYPE_TRAME {
    SEND_DATA_16BIT_ADDRESS = 0x01,
    SEND_AT_COMMAND_REQUEST = 0x08,
    SEND_AT_COMMAND_QUEUE = 0x09,
    SEND_REMOTE_AT_COMMAND_REQUEST = 0x17,
    RECEIVE_DATA_16BIT_ADDRESS = 0x81,
    RECEIVE_DATA_16BIT_ADDRESS_IO = 0x83,
    RECEIVE_COMMAND_RESPONSE = 0x88,
    TRANSMISSION_STATUS_FRAME = 0x89,
    MODEM_STATUS_FRAME = 0x8A,
    RECEIVE_REMOTE_COMMAND_RESPONSE = 0x97,
};


/**envoi des donnees via xbee. <BR>
    ID_message utilise pour faire le suivi des ACK <BR>
    Options peut etre interprete comme 1 octet pour des transmissions de donnees standard, ou la commande AT en 2 octets.
    \todo vitesse de transmission?
 */

short PortXbee_envoyer(char dest_addr[2], char *donnees, int nb, int serial, short type_trame, unsigned char ID_message, short options);

short PortXbee_receptionOctet(xBeeReceivePacket* donnees, int serial);

void FormatAndSend_RF_PacketToRPIviaCAN(xBeeReceivePacket* donnees);


#endif