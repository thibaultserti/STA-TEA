/**
  @Generated PIC24 / dsPIC33 / PIC32MM MCUs Source File

  @Company:
    Centrale Lille

  @File Name:
    MESCAN1_DeclarationVarTrain.h

  @Summary:
    This is the MESCAN1_DeclarationVarTrain.h file generated using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - pic24-dspic-pic32mm : 1.75.1
        Device            :  dsPIC33FJ128MC802
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.35
        MPLAB             :  MPLAB X v5.05

 * Created on 21 novembre 2018
 */
#ifndef ECAN1_DECLARATION_VAR_TRAIN_H
#define	ECAN1_DECLARATION_VAR_TRAIN_H

//#include "../Librairie_DspicFJ/ecan1_DefinitionVariable.h"

#include "MESCAN1_DefinitionVariable.h"
#include "MESCAN1_MAIN_PARAMS.h"
#include "MESCAN1_VarStatusTrain.h"
#include "MESCAN1_Utilitaire.h"


extern uint16_t cptErreurDefinitionVar;

///////////////////////////////////////////////////////////////////////////////
//Décomposition des datas de la trame "mc_messageGSM_Sent"
///////////////////////////////////////////////////////////////////////////////
//config de toutes les datas de la trame "mc_messageGSM_Sent"

typedef enum {
    LEN_MESSAGE_SENT_TO_ANTENNE = 0,
    CUSTOM_CKS_MESSAGE_SENT_TO_ANTENNE = 1,
    DEST_ADRESS_ANTENNE = 2,
} MC_MESSAGE_GSM_SENT_TO_ANTENNE;


////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_messageGSM_Sent" et datas associées
extern uCAN1_MSG mc_messageGSM_Sent;
extern MC_Data8 cdmc_lenMessageSent;
extern MC_Data8 cdmc_customCKS_MessageSent;
extern MC_Data16 wdmc_destAdressMessageSent;




///////////////////////////////////////////////////////////////////////////////
//Décomposition des datas de la trame "mc_messageGSM_Received"
///////////////////////////////////////////////////////////////////////////////
//config de toutes les datas de la trame "mc_messageGSM_Received"

typedef enum {
    LEN_MESSAGE_RECEIVED_FROM_ANTENNE = 0,
    CUSTOM_CKS_MESSAGE_RECEIVED_FROM_ANTENNE = 1,
    ADRESS_SOURCE_FROM_ANTENNE = 2,
    RSSI_FROM_ANTENNE = 4,
} MC_MESSAGE_GSM_RECEIVED_FROM_ANTENNE;


////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_messageGSM_Received" et datas associées
extern uCAN1_MSG mc_messageGSM_Received;
extern MC_Data8 cdmc_lenMessageReceived;
extern MC_Data8 cdmc_customCKS_MessageReceived;
extern MC_Data16 wdmc_sourceAdressMessageReceived;
extern MC_Data8 cdmc_RSSI_FromAntenne;




///////////////////////////////////////////////////////////////////////////////
//Décomposition des datas de la trame mc_MOT_scheduleurMesures
///////////////////////////////////////////////////////////////////////////////
//config de toutes les datas de la trame "mc_MOT_scheduleurMesures"

typedef enum {
    ORDONNANCEMENT_ID = 0,
    VITESSE_MESUREE = 1,
    DISTANCE_RELATIVE_PARCOURUE = 2,
    VALEUR_ERREUR_REGUL = 4,
    VITESSE_CONSIGNE_INTERNE = 6,
} MC_SCHEDULEURMESURES_DATAS;



////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_scheduleurAndMesures" et datas associées
extern uCAN1_MSG mc_scheduleurAndMesures;
extern MC_Data8 cdmc_ordonnancementId;
extern MC_Data8 cdmc_vitesseMesuree;
extern MC_Data16 wdmc_QEI_distanceRelativeParcourue;
extern MC_Data16 wdmc_valeurErreurRegul;
extern MC_Data8 cdmc_vitesseConsigneInterne;




///////////////////////////////////////////////////////////////////////////////
//Décomposition des datas de la trame mc_consigneVitesse
///////////////////////////////////////////////////////////////////////////////
//config de toutes les datas de la trame "mc_consigneVitesse"

typedef enum {
    CONSIGNE_VITESSE = 0,
    SENS_DEPLACEMENT_LOCO = 1,
} MC_CONSIGNE_VITESSE_DATAS;

#define POSITION_BIT_SENS_DEPLACEMENT_LOCO  0

////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_consigneVitesse" et datas associées
extern uCAN1_MSG mc_consigneVitesse;
extern MC_Data8 cdmc_consigneVitesse;
extern MC_Bit bdmc_sensDeplacementLoco;



///////////////////////////////////////////////////////////////////////////////
//Décomposition des datas de la trame mc_consigneVitesseLimite
///////////////////////////////////////////////////////////////////////////////
//config de toutes les datas de la trame "mc_consigneVitesseLimite"

typedef enum {
    CONSIGNE_VITESSE_LIMITE = 0,
} MC_CONSIGNE_VITESSE_LIMITE_DATAS;

////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_consigneVitesseLimite" et datas associées
extern uCAN1_MSG mc_consigneVitesseLimite;
extern MC_Data8 cdmc_consigneVitesseLimite;



///////////////////////////////////////////////////////////////////////////////
//Décomposition des datas de la trame "mc_EEPROM"
///////////////////////////////////////////////////////////////////////////////
//config de toutes les datas de la trame "mc_EEPROM"

typedef enum {
    COMMANDE_EEPROM = 0,
    OFFSET_EEPROM = 1,
    DATA1EEPROM = 1,
    DATA2EEPROM = 2,
    DATA3EEPROM = 3,
    DATA4EEPROM = 4,
    DATA5EEPROM = 5,
    DATA6EEPROM = 6,
    DATA7EEPROM = 7,
} MC_MESSAGE_EEPROM;


////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_EEPROM" et datas associées
extern uCAN1_MSG mc_EEPROM;
extern MC_Data8 cdmc_commandeEEPROM;
extern MC_Data16 wdmc_offsetEEPROM;
extern MC_Data8 cdmc_data1EEPROM;
extern MC_Data8 cdmc_data2EEPROM;
extern MC_Data8 cdmc_data3EEPROM;
extern MC_Data8 cdmc_data4EEPROM;
extern MC_Data8 cdmc_data5EEPROM;
extern MC_Data8 cdmc_data6EEPROM;
extern MC_Data8 cdmc_data7EEPROM;



///////////////////////////////////////////////////////////////////////////////
//Décomposition des datas de la trame mc_arretHardware
///////////////////////////////////////////////////////////////////////////////
//config de toutes les datas de la trame "mc_arretHardware"

typedef enum {
    CAUSE_LOCO_OFF = 0,
} MC_ARRET_HARDWARE;

////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_arretHardware" et datas associées
extern uCAN1_MSG mc_arretHardware;
extern MC_Data8 cdmc_causeLocoOFF;


///////////////////////////////////////////////////////////////////////////////
//Décomposition des datas de la trame mc_paramKiKp
///////////////////////////////////////////////////////////////////////////////
//config de toutes les datas de la trame "mc_paramKiKp"

typedef enum {
    COEFF_KI = 0,
    COEFF_KP = 4,
} MC_PARAM_KI_KP_DATAS;

////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_paramKiKp"
extern uCAN1_MSG mc_paramKiKp;
extern MC_Datafloat32 fdmc_Ki;
extern MC_Datafloat32 fdmc_Kp;



///////////////////////////////////////////////////////////////////////////////
//Décomposition des datas de la trame mc_messageBaliseReceived
///////////////////////////////////////////////////////////////////////////////
//config de toutes les datas de la trame "mc_messageBaliseReceived"

typedef enum {
    LEN_MESSAGE_EBT = 0,
    CUSTOM_CKS_MESSAGE_EBT = 1,
    SOURCE_NUMERO_BALISE = 2,
    ETAT_PROCHAIN_FEU = 3,
    NUMERO_CANTON_SUIVANT = 4,
    COMPTE_RENDU_TRANSACTION = 7,
} MC_PARAM_MESSAGE_EBT;
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_messageBaliseReceived"
//
//  LES DATAS ASSOCI2ES RESTENT A DECLARER !!!!!!!!!!!
//  Pour le prog "MOT", seul la presence de la trame suffit a RAZ le QEI
extern uCAN1_MSG mc_message_ebt_received;





////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_receiveACK_RF_Xbee" et datas associées
////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//Décomposition des datas de la trame mc_receiveACK_RF_Xbee
///////////////////////////////////////////////////////////////////////////////
//config de toutes les datas de la trame "mc_receiveACK_RF_Xbee"

typedef enum {
    FRAME_ID_ACK_PACKET = 0,
    STATUS_TX_ACK_PACKET = 1
} RECEIVE_ACK_RF_XBEE;


extern uCAN1_MSG mc_receiveACK_RF_Xbee;

extern MC_Data8 cdmc_frame_Id_ACK_Packet;
extern MC_Data8 cdmc_statusTx_ACK_Packet;
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

typedef enum {
    SOURCES_WARNINGS = 0,
    TYPES_WARNINGS = 1,
    CODES_WARNINGS = 2,
} MC_PARAM_WARNING;
///////////////////////////////////////////////////////////////////////////////
//Décomposition des datas de la trame "mc_warning"
///////////////////////////////////////////////////////////////////////////////
//config de toutes les datas de la trame "mc_warning"

extern uCAN1_MSG mc_warning;

extern MC_Data8 cdmc_sourceWarning;
extern MC_Data8 cdmc_typeWarning;
extern MC_Data8 cdmc_codeWarning;


#endif   /*  ECAN1_DECLARATION_VAR_TRAIN_H  */


//#endif	/* ECAN1_DECLARATION_VAR_TRAIN_H */