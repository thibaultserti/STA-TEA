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

/**
  Section: Included Files
 */
#include "MESCAN1_DefinitionVariable.h"
#include "MESCAN1_MAIN_PARAMS.h"
#include "MESCAN1_VarStatusTrain.h"
#include "MESCAN1_VarTrain.h"

uint16_t cptErreurDefinitionVar = 0;

////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_messageGSM_Sent" et datas associées
uCAN1_MSG mc_messageGSM_Sent = {
    {MC_ID_MESSAGE_GSM_SENT,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_MESSAGE_GSM_SENT,
        0, 0, 0, 0, 0, 0, 0, 0}
};
MC_Data8 cdmc_lenMessageSent = {
    MC_ID_MESSAGE_GSM_SENT,
    LEN_MESSAGE_SENT_TO_ANTENNE,
};
MC_Data8 cdmc_customCKS_MessageSent = {
    MC_ID_MESSAGE_GSM_SENT,
    CUSTOM_CKS_MESSAGE_SENT_TO_ANTENNE,
};
MC_Data16 wdmc_destAdressMessageSent = {
    MC_ID_MESSAGE_GSM_SENT,
    DEST_ADRESS_ANTENNE,
};

////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_messageGSM_Received" et datas associées
uCAN1_MSG mc_messageGSM_Received = {
    {MC_ID_MESSAGE_GSM_RECEIVED,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_MESSAGE_GSM_RECEIVED,
        0, 0, 0, 0, 0, 0, 0, 0}
};
MC_Data8 cdmc_lenMessageReceived = {
    MC_ID_MESSAGE_GSM_RECEIVED,
    LEN_MESSAGE_RECEIVED_FROM_ANTENNE,
};
MC_Data8 cdmc_customCKS_MessageReceived = {
    MC_ID_MESSAGE_GSM_RECEIVED,
    CUSTOM_CKS_MESSAGE_RECEIVED_FROM_ANTENNE,
};
MC_Data16 wdmc_sourceAdressMessageReceived = {
    MC_ID_MESSAGE_GSM_RECEIVED,
    ADRESS_SOURCE_FROM_ANTENNE,
};
MC_Data8 cdmc_RSSI_FromAntenne = {
    MC_ID_MESSAGE_GSM_RECEIVED,
    RSSI_FROM_ANTENNE,
};



////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_scheduleurAndMesures" et datas associées
uCAN1_MSG mc_scheduleurAndMesures = {
    {MC_ID_SCHEDULEUR_MESURES,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_SCHEDULEUR_MESURES,
        MC_ID_SCHEDULEUR_MESURES, 0, 0, 0, 0, 0, 0, 0}
};
MC_Data8 cdmc_ordonnancementId = {
    MC_ID_SCHEDULEUR_MESURES,
    ORDONNANCEMENT_ID,
};
MC_Data8 cdmc_vitesseMesuree = {
    MC_ID_SCHEDULEUR_MESURES,
    VITESSE_MESUREE,
};
MC_Data16 wdmc_QEI_distanceRelativeParcourue = {
    MC_ID_SCHEDULEUR_MESURES,
    DISTANCE_RELATIVE_PARCOURUE,
};
MC_Data16 wdmc_valeurErreurRegul = {
    MC_ID_SCHEDULEUR_MESURES,
    VALEUR_ERREUR_REGUL,
};
MC_Data8 cdmc_vitesseConsigneInterne = {
    MC_ID_SCHEDULEUR_MESURES,
    VITESSE_CONSIGNE_INTERNE,
};


////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_consigneVitesse" et datas associées
uCAN1_MSG mc_consigneVitesse = {
    {MC_ID_CONSIGNE_VITESSE,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_CONSIGNE_VITESSE,
        0, 0, 0, 0, 0, 0, 0, 0}
};
MC_Data8 cdmc_consigneVitesse = {
    MC_ID_CONSIGNE_VITESSE,
    CONSIGNE_VITESSE,
};
MC_Bit bdmc_sensDeplacementLoco = {
    MC_ID_CONSIGNE_VITESSE,
    SENS_DEPLACEMENT_LOCO,
    POSITION_BIT_SENS_DEPLACEMENT_LOCO,
};


////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_consigneVitesseLimite" et datas associées
uCAN1_MSG mc_consigneVitesseLimite = {
    {MC_ID_CONSIGNE_VITESSE_LIMITE,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_CONSIGNE_VITESSE_LIMITE,
        MAX_CONSIGNE_VITESSE_AUTORISEE, 0, 0, 0, 0, 0, 0, 0}
};
MC_Data8 cdmc_consigneVitesseLimite = {
    MC_ID_CONSIGNE_VITESSE_LIMITE,
    CONSIGNE_VITESSE_LIMITE,
};


////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_EEPROM" et datas associées
uCAN1_MSG mc_EEPROM = {
    {MC_ID_EEPROM,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_EEPROM,
        0, 0, 0, 0, 0, 0, 0, 0}
};
MC_Data8 cdmc_commandeEEPROM = {
    MC_ID_EEPROM,
    COMMANDE_EEPROM,
};
MC_Data16 wdmc_offsetEEPROM = {
    MC_ID_EEPROM,
    OFFSET_EEPROM,
};
MC_Data8 cdmc_data1EEPROM = {
    MC_ID_EEPROM,
    DATA1EEPROM,
};
MC_Data8 cdmc_data2EEPROM = {
    MC_ID_EEPROM,
    DATA2EEPROM,
};
MC_Data8 cdmc_data3EEPROM = {
    MC_ID_EEPROM,
    DATA3EEPROM,
};
MC_Data8 cdmc_data4EEPROM = {
    MC_ID_EEPROM,
    DATA4EEPROM,
};
MC_Data8 cdmc_data5EEPROM = {
    MC_ID_EEPROM,
    DATA5EEPROM,
};
MC_Data8 cdmc_data6EEPROM = {
    MC_ID_EEPROM,
    DATA6EEPROM,
};
MC_Data8 cdmc_data7EEPROM = {
    MC_ID_EEPROM,
    DATA7EEPROM,
};


////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_arretHardware" et datas associées
uCAN1_MSG mc_arretHardware = {
    {MC_ID_ARRET_HARDWARE,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_ARRET_HARDWARE,
        0, 0, 0, 0, 0, 0, 0, 0}
};
MC_Data8 cdmc_causeLocoOFF = {
    MC_ID_ARRET_HARDWARE,
    CAUSE_LOCO_OFF,
};



////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_paramKiKp"

uCAN1_MSG mc_paramKiKp = {
    {MC_ID_MESSAGE_PARAM_KI_KP,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_MESSAGE_PARAM_KI_KP,
        0, 0, 0, 0, 0, 0, 0, 0}
};

MC_Datafloat32 fdmc_Ki = {
    MC_ID_MESSAGE_PARAM_KI_KP,
    COEFF_KI,
};

MC_Datafloat32 fdmc_Kp = {
    MC_ID_MESSAGE_PARAM_KI_KP,
    COEFF_KP,
};




////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_messageBaliseReceived"
//
//  LES DATAS ASSOCI2ES RESTENT A DECLARER !!!!!!!!!!!
//  Pour le prog "MOT", seul la presence de la trame suffit a RAZ le QEI
uCAN1_MSG mc_message_ebt_received = {
    {MC_ID_MESSAGE_EBT_RECEIVED,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_MESSAGE_EBT_RECEIVED,
        0, 0, 0, 0, 0, 0, 0, 0}
};

MC_Data8 cdmc_lenMessageBalise = {
    MC_ID_MESSAGE_EBT_RECEIVED,
    LEN_MESSAGE_EBT,
};

MC_Data8 cdmc_customCKS_MessageBalise = {
    MC_ID_MESSAGE_EBT_RECEIVED,
    CUSTOM_CKS_MESSAGE_EBT,
};

MC_Data8 cdmc_sourceNumeroBalise = {
    MC_ID_MESSAGE_EBT_RECEIVED,
    SOURCE_NUMERO_BALISE,
};

MC_Data8 cdmc_etatProchainFeu = {
    MC_ID_MESSAGE_EBT_RECEIVED,
    ETAT_PROCHAIN_FEU,
};

MC_Data8 cdmc_numeroCantonSuivant = {
    MC_ID_MESSAGE_EBT_RECEIVED,
    NUMERO_CANTON_SUIVANT,
};

MC_Data8 cdmc_compteRenduTransactionAvecInfra = {
    MC_ID_MESSAGE_EBT_RECEIVED,
    COMPTE_RENDU_TRANSACTION,
};


////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_receiveACK_RF_Xbee" et datas associées
////////////////////////////////////////////////////////////////////////////////

uCAN1_MSG mc_receiveACK_RF_Xbee = {
    {MC_ID_RECEIVE_ACK_RF_XBEE,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_RECEIVE_ACK_RF_XBEE,
        0, 0, 0, 0, 0, 0, 0, 0}
};

MC_Data8 cdmc_frame_Id_ACK_Packet = {
    MC_ID_RECEIVE_ACK_RF_XBEE,
    FRAME_ID_ACK_PACKET,
};

MC_Data8 cdmc_statusTx_ACK_Packet = {
    MC_ID_RECEIVE_ACK_RF_XBEE,
    STATUS_TX_ACK_PACKET,
};


///////////////////////////////////////////////////////////////////////////////
//Décomposition des datas de la trame "mc_warning"
///////////////////////////////////////////////////////////////////////////////
//config de toutes les datas de la trame "mc_warning"

uCAN1_MSG mc_warning = {
    {MC_ID_WARNING,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_WARNING,
        0, 0, 0, 0, 0, 0, 0, 0}
};

MC_Data8 cdmc_sourceWarning = {
     MC_ID_WARNING, 
     SOURCES_WARNINGS,
};

MC_Data8 cdmc_typeWarning = {
     MC_ID_WARNING, 
     TYPES_WARNINGS,
};

MC_Data8 cdmc_codeWarning = {
     MC_ID_WARNING, 
     CODES_WARNINGS,
};

 









