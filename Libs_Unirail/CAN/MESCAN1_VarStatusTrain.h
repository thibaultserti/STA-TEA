/**
  @Generated PIC24 / dsPIC33 / PIC32MM MCUs Source File

  @Company:
    Centrale Lille

  @File Name:
    MESCAN1_VarStatusTrain.h

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

 * Created on 4 juillet 2019
 */

#ifndef ECAN1_DECLARATION_VAR_STATUS_TRAIN_H
#define	ECAN1_DECLARATION_VAR_STATUS_TRAIN_H


//#include "MESCAN1_DefinitionVariable.h"

//#include "../Librairie_DspicFJ/ecan1_DefinitionVariable.h"
//#include "MESCAN1_VarTrain.h"

//#include  "../init.h"

typedef enum {
    MOT_VERSION_SOFT = 0,
} MC_MOT_STATUS_START_DATAS;

typedef enum {
    MOT_ERROR = 0,
    MOT_WARNING = 1,
    MOT_IO = 2,
    MOT_STATE_DYNAMIQUE = 3,
    MOT_VBAT = 4,
    MOT_VAR1 = 6,
    MOT_VAR2 = 7,
} MC_MOT_STATUS_RUN_DATAS;

//config bits de la data "MOT_ERROR" de la trame "mc_MOT_statusRun"

typedef enum {
    MOT_CRASH_SOFT = 0,
    MOT_SECU_PI = 1,
    STOP_LOCO_XXX_CRASH_SOFT = 3,
} MC_MOT_STATUS_RUN_ERROR_BIT;

//config bits de la data "MOT_WARNING" de la trame "mc_MOT_statusRun"

typedef enum {
    MOT_INIT_EN_COURS = 0,
    ELECTRIFICATION_RAIL = 1,
    BATTERIE_FAIBLE = 2,
    MOT_BUG_SOFT = 4,
    MOT_CANRX_ERRORPASSIVE = 5,
    MOT_CANTX_ERRORPASSIVE = 6,
    MOT_CAN_BUS_OFF = 7,
} MC_MOT_STATUS_RUN_WARNING_BIT;

//config bits de la data "MOT_IO" de la trame "mc_MOT_statusRun"

typedef enum {
    MOT_JUMPER2 = 1,
    MOT_JUMPER3 = 2,
    MOT_JUMPER4 = 3,
    MOT_SW1 = 4,
    MOT_SW2 = 5
} MC_MOT_STATUS_RUN_IO_BIT;

//config bits de la data "MOT_STATE_DYNAMIQUE" de la trame "mc_MOT_statusRun"

typedef enum {
    MOT_MODE_LOCO_OFF = 1,
    MODE_MOVE_LOCO_MANUEL_OR_REMOTE = 2,
    MOVE_SENS_LOCO_MANUEL_OR_REMOTE = 3,
} MC_MOT_STATUS_RUN_STATE_DYNAMIQUE_BIT;



////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_MOT_statusStart" et datas associees
extern uCAN1_MSG mc_MOT_statusStart;
extern MC_Data8 cdmc_MOT_versionSoft;
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_MOT_statusRun" et datas associees
extern uCAN1_MSG mc_MOT_statusRun;

//Definitions des variables de "MOT_ERROR"
extern MC_Bit bdmc_MOT_crashSoft;
extern MC_Bit bdmc_MOT_securiteErreurPI;
extern MC_Bit bdmc_stopLoco_XXX_CrashSoft;
extern MC_Data8 cdmc_MOT_erreurs;

//Definitions des variables de "MOT_WARNING"
extern MC_Bit bdmc_MOT_initEnCours;
extern MC_Bit bdmc_noPoweredByRails;
extern MC_Bit bdmc_batterieFaible;
extern MC_Bit bdmc_MOT_bugSoft;
extern MC_Bit bdmc_MOT_CAN_RxErrorPassive;
extern MC_Bit bdmc_MOT_CAN_TxErrorPassive;
extern MC_Bit bdmc_MOT_CAN_busOFF;
extern MC_Data8 cdmc_MOT_warnings;

//Definitions des variables de "MOT_IO"
extern MC_Bit bdmc_MOT_jumper2;
extern MC_Bit bdmc_MOT_jumper3;
extern MC_Bit bdmc_MOT_jumper4;
extern MC_Bit bdmc_MOT_sw1;
extern MC_Bit bdmc_MOT_sw2;

//Definitions des variables de "MOT_STATE_DYNAMIQUE"
extern MC_Bit bdmc_modeLocoOFF;
extern MC_Bit bdmc_modeMoveLocoManuelOrRemote;
extern MC_Bit bdmc_moveSensLocoManuelOrRemote;

//Union en 1 octet de tous les bits dynamiques
extern MC_Data8 cdmc_MOT_dynamique;
//Autres variables
extern MC_Data16 wdmc_tensionBatterie;
extern MC_Data8 cdmc_MOT_var1Debug;
extern MC_Data8 cdmc_MOT_var2Debug;

typedef enum {
    RP1_VERSION_SOFT = 0,
    RP1_ADRESSE_IP = 1,
} MC_RP1_STATUS_START_DATAS;

//config de toutes les datas de la trame "mc_RP1_statusRun"

typedef enum {
    RP1_ERROR = 0,
    RP1_WARNING = 1,
    RP1_IO = 2,
    RP1_STATE_DYNAMIQUE = 3,
	RP1_CONFIG_ONBOARD = 4,
    RP1_VAR1 = 6,
    RP1_VAR2 = 7,
} MC_RP1_STATUS_RUN_DATAS;

//config bits de la data "RP1_ERROR" de la trame "mc_RP1_statusRun"

typedef enum {
    RP1_CRASH_SOFT = 0,
} MC_RP1_STATUS_RUN_ERROR_BIT;

//config bits de la data "RP1_WARNING" de la trame "mc_RP1_statusRun"

typedef enum {
    RP1_INIT_EN_COURS = 0,
    RP1_BUG_SOFT = 4,
    RP1_CANRX_ERRORPASSIVE = 5,
    RP1_CANTX_ERRORPASSIVE = 6,
    RP1_CAN_BUS_OFF = 7,
} MC_RP1_STATUS_RUN_WARNING_BIT;

//config bits de la data "RP1_IO" de la trame "mc_RP1_statusRun"

typedef enum {
    RP1_CAMERA = 0,
    RP1_JUMPER_CFG1 = 1,
    RP1_JUMPER_CFG2 = 2,
} MC_RP1_STATUS_RUN_IO_BIT;

//config bits de la data "RP1_STATE_DYNAMIQUE" de la trame "mc_RP1_statusRun"

typedef enum {
    RP1_ETAT_CONNECTION_TCP_IP = 1,
    RP1_ETAT_CONNECTION__WIFI = 2,
    RP1_ETAT_CONNECTION_CAMERA = 3,
} MC_RP1_STATUS_RUN_STATE_DYNAMIQUE_BIT;




////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_RP1_statusStart" et datas associees
extern uCAN1_MSG mc_RP1_statusStart;
extern MC_Data8 cdmc_RP1_versionSoft;
extern MC_Data32 ldmc_adresseIP_RP1;
////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_RP1_statusRun" et datas associees
////////////////////////////////////////////////////////////////////////////////
extern uCAN1_MSG mc_RP1_statusRun;

extern MC_Bit bdmc_RP1_crashSoft;
//Union en 1 octet de tous les bits erreurs
extern MC_Data8 cdmc_RP1_erreurs;

//Definitions des variables de "RP1_WARNING"
extern MC_Bit bdmc_RP1_initEnCours;
extern MC_Bit bdmc_RP1_bugSoft;
extern MC_Bit bdmc_RP1_CAN_RxErrorPassive;
extern MC_Bit bdmc_RP1_CAN_TxErrorPassive;
extern MC_Bit bdmc_RP1_CAN_busOFF;

//Union en 1 octet de tous les bits warning
extern MC_Data8 cdmc_RP1_warnings;

//Definitions des variables de "RP1_IO"
extern MC_Bit bdmc_presenceCamera;
extern MC_Bit bdmc_RP1_jumperCfg1;
extern MC_Bit bdmc_RP1_jumperCfg2;

//Definitions des variables de "RP1_STATE_DYNAMIQUE"
extern MC_Bit bdmc_RP1_etatConnexion_TCP_IP;
extern MC_Bit bdmc_RP1_etatConnexionWIFI;
extern MC_Bit bdmc_etatConnexionCamera;
//Union en 1 octet de tous les bits dynamiques
extern MC_Data8 cdmc_RP1_dynamique;

//Definition de la variable de "RP1_CONFIG_ONBOARD"

extern MC_Data8 cdmc_RP1_configONBOARD;

//Autres variables
extern MC_Data8 cdmc_RP1_var1Debug;
extern MC_Data8 cdmc_RP1_var2Debug;

typedef enum {
    RP2_VERSION_SOFT = 0,
    RP2_ADRESSE_IP = 1,
} MC_RP2_STATUS_START_DATAS;

//config de toutes les datas de la trame "mc_RP2_statusRun"

typedef enum {
    RP2_ERROR = 0,
    RP2_WARNING = 1,
    RP2_IO = 2,
    RP2_STATE_DYNAMIQUE = 3,
    RP2_VAR1 = 6,
    RP2_VAR2 = 7,
} MC_RP2_STATUS_RUN_DATAS;

//config bits de la data "RP2_ERROR" de la trame "mc_RP2_statusRun"

typedef enum {
    RP2_CRASH_SOFT = 0,
} MC_RP2_STATUS_RUN_ERROR_BIT;

//config bits de la data "RP2_WARNING" de la trame "mc_RP2_statusRun"

typedef enum {
    RP2_INIT_EN_COURS = 0,
    RP2_BUG_SOFT = 4,
    RP2_CANRX_ERRORPASSIVE = 5,
    RP2_CANTX_ERRORPASSIVE = 6,
    RP2_CAN_BUS_OFF = 7,
} MC_RP2_STATUS_RUN_WARNING_BIT;

//config bits de la data "RP2_IO" de la trame "mc_RP2_statusRun"

//typedef enum {
//    RP2_JUMPER2 = 1,
//    RP2_SW2 = 5
//} MC_RP2_STATUS_RUN_IO_BIT;

//config bits de la data "RP2_STATE_DYNAMIQUE" de la trame "mc_RP2_statusRun"

typedef enum {
    RP2_ETAT_CONNECTION_TCP_IP = 1,
    RP2_ETAT_CONNECTION__WIFI = 2,
} MC_RP2_STATUS_RUN_STATE_DYNAMIQUE_BIT;




////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_RP2_statusStart" et datas associees
extern uCAN1_MSG mc_RP2_statusStart;
extern MC_Data8 cdmc_RP2_versionSoft;
extern MC_Data32 ldmc_adresseIP_RP2;
////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_RP2_statusRun" et datas associees
////////////////////////////////////////////////////////////////////////////////
extern uCAN1_MSG mc_RP2_statusRun;

extern MC_Bit bdmc_RP2_crashSoft;
//Union en 1 octet de tous les bits erreurs
extern MC_Data8 cdmc_RP2_erreurs;

//Definitions des variables de "RP2_WARNING"
extern MC_Bit bdmc_RP2_initEnCours;

extern MC_Bit bdmc_RP2_bugSoft;
extern MC_Bit bdmc_RP2_CAN_RxErrorPassive;
extern MC_Bit bdmc_RP2_CAN_TxErrorPassive;
extern MC_Bit bdmc_RP2_CAN_busOFF;

//Union en 1 octet de tous les bits warning
extern MC_Data8 cdmc_RP2_warnings;

//Definitions des variables de "RP2_IO"
//MC_Bit bdmc_RP2_xxxx = {
//    MC_ID_RP2_STATUS_RUN,
//    RP1_IO,
//    RP1_XXXXX,
//};

//Definitions des variables de "RP2_STATE_DYNAMIQUE"
extern MC_Bit bdmc_RP2_etatConnexion_TCP_IP;
extern MC_Bit bdmc_RP2_etatConnexionWIFI;
//Union en 1 octet de tous les bits dynamiques
extern MC_Data8 cdmc_RP2_dynamique;

//Autres variables
extern MC_Data8 cdmc_RP2_var1Debug;
extern MC_Data8 cdmc_RP2_var2Debug;

typedef enum {
    BAL_VERSION_SOFT = 0,
} MC_BAL_STATUS_START_DATAS;

typedef enum {
    BAL_ERROR = 0,
    BAL_WARNING = 1,
    BAL_IO = 2,
    BAL_STATE_DYNAMIQUE = 3,
    BAL_STATUS_COM_BALISE = 4,
    BAL_NUMBER_LAST_BALISE = 5,
    BAL_VAR1 = 6,
    BAL_VAR2 = 7,
} MC_BAL_STATUS_RUN_DATAS;

//config bits de la data "BAL_ERROR" de la trame "mc_BAL_statusRun"

typedef enum {
    BAL_CRASH_SOFT = 0,
} MC_BAL_STATUS_RUN_ERROR_BIT;

//config bits de la data "BAL_WARNING" de la trame "mc_BAL_statusRun"

typedef enum {
    BAL_INIT_EN_COURS = 0,
    BAL_ECHEC_COM_BALI_AVEC_INFRA = 1,
    BAL_BUG_SOFT = 4,
    BAL_CANRX_ERRORPASSIVE = 5,
    BAL_CANTX_ERRORPASSIVE = 6,
    BAL_CAN_BUS_OFF = 7,
} MC_BAL_STATUS_RUN_WARNING_BIT;

//config bits de la data "BAL_IO" de la trame "mc_BAL_statusRun"

typedef enum {
    BAL_POIDS_1_RC = 0,
    BAL_POIDS_2_RC = 1,
    BAL_POIDS_4_RC = 2,
    BAL_POIDS_8_RC = 3,
    BAL_JUMPER1_RC = 4,
    BAL_SW_RC1 = 5,
} MC_BAL_STATUS_RUN_IO_BIT;




///////////////////////////////////////////////////////////////////////////////
//Décomposition des datas de la trame mc_BAL_statusStart et mc_BAL_statusRun
///////////////////////////////////////////////////////////////////////////////
//config de toutes les datas de la trame "mc_BAL_statusRun"

////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_BAL_statusStart" et datas associées
extern uCAN1_MSG mc_BAL_statusStart;
extern MC_Data8 cdmc_BAL_versionSoft;
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_BAL_statusRun" et datas associées
extern uCAN1_MSG mc_BAL_statusRun;
//Definitions des variables de "BAL_ERROR"
extern MC_Bit bdmc_BAL_crashSoft;
//Union en 1 octet de tous les bits d'erreur
extern MC_Data8 cdmc_BAL_erreurs;
//Definitions des variables de "BAL_WARNING"
extern MC_Bit bdmc_BAL_initEnCours;
extern MC_Bit bdmc_BAL_BadComWithInfra;
extern MC_Bit bdmc_BAL_bugSoft;
extern MC_Bit bdmc_BAL_CAN_RxErrorPassive;
extern MC_Bit bdmc_BAL_CAN_TxErrorPassive;
extern MC_Bit bdmc_BAL_CAN_busOFF;
//Union en 1 octet de tous les bits warning
extern MC_Data8 cdmc_BAL_warnings;

//Definitions des variables de "BAL_IO"
extern MC_Bit bdmc_BAL_poids1RoueCodeuse;
extern MC_Bit bdmc_BAL_poids2RoueCodeuse;
extern MC_Bit bdmc_BAL_poids4RoueCodeuse;
extern MC_Bit bdmc_BAL_poids8RoueCodeuse;
extern MC_Bit bdmc_BAL_jumper1_RC;
extern MC_Bit bdmc_BAL_swRC1;
//Union en 1 octet de tous les bits IO
extern MC_Data8 cdmc_BAL_IO;

//Union en 1 octet de tous les bits dynamiques
extern MC_Data8 cdmc_BAL_dynamique;

//Variable pour status commnication entre balise et infra
extern MC_Data8 cdmc_BAL_statusComBalise;

//Variable qui indique le dernier numero de balise detectee par le train
extern MC_Data8 cdmc_BAL_lastNumberOfDetectedBali;

//Autres variables
extern MC_Data8 cdmc_BAL_var1Debug;
extern MC_Data8 cdmc_BAL_var2Debug;

typedef enum {
    LCD_ERROR = 0,
    LCD_WARNING = 1,
    LCD_IO = 2,
    LCD_STATE_DYNAMIQUE = 3,
    LCD_ACK_XXX_STATUS_START = 4,
    LCD_VAR1 = 6,
    LCD_VAR2 = 7,
} MC_LCD_STATUS_RUN_DATAS;

//config bits de la data "LCD_ERROR" de la trame "mc_LCD_statusRun"

typedef enum {
    LCD_CRASH_SOFT = 0,
} MC_LCD_STATUS_RUN_ERROR_BIT;

//config bits de la data "LCD_WARNING" de la trame "mc_LCD_statusRun"

typedef enum {
    LCD_INIT_EN_COURS = 0,
    LCD_BUG_SOFT = 4,
    LCD_CANRX_ERRORPASSIVE = 5,
    LCD_CANTX_ERRORPASSIVE = 6,
    LCD_CAN_BUS_OFF = 7,
} MC_LCD_STATUS_RUN_WARNING_BIT;

//config bits de la data "LCD_IO" de la trame "mc_LCD_statusRun"

typedef enum {
    LCD_SW1 = 0,
    LCD_SW2 = 1,
} MC_LCD_STATUS_RUN_IO_BIT;

//config bits de la data "LCD_STATE_DYNAMIQUE" de la trame "mc_LCD_statusRun"

typedef enum {
    LCD_MODE_ACCUEIL = 2,
    LCD_MODE_RUN = 3,
} MC_LCD_STATUS_RUN_STATE_DYNAMIQUE_BIT;

typedef enum {
    ACK_MOT_STATUS_START = 0,
    ACK_RP1_STATUS_START = 1,
    ACK_RP2_STATUS_START = 2,
    ACK_BAL_STATUS_START = 3,
    ACK_GSM_STATUS_START = 4,
} MC_LCD_ACK_STATUS_START_BIT;



///////////////////////////////////////////////////////////////////////////////
//Décomposition des datas de la trame mc_LCD_statusRun
///////////////////////////////////////////////////////////////////////////////
//config de toutes les datas de la trame "mc_LCD_statusRun"

////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_LCD_statusRun"
extern uCAN1_MSG mc_LCD_statusRun;
//Definitions des variables de "LCD_ERROR"
extern MC_Bit bdmc_LCD_crashSoft;
//Union en 1 octet de tous les bits d'erreur
extern MC_Data8 cdmc_LCD_erreurs;
//Definitions des variables de "LCD_WARNING"
extern MC_Bit bdmc_LCD_initEnCours;
extern MC_Bit bdmc_LCD_bugSoft;

extern MC_Bit bdmcLCD_CAN_RxErrorPassive;
extern MC_Bit bdmc_LCD_CAN_TxErrorPassive;
extern MC_Bit bdmc_LCD_CAN_busOFF;
//Union en 1 octet de tous les bits d'erreur
extern MC_Data8 cdmc_LCD_warnings;
//Definitions des variables de "LCD_IO"
extern MC_Bit bdmc_LCD_sw1;
extern MC_Bit bdmc_LCD_sw2;
//Definitions des variables de "LCD_STATE_DYNAMIQUE"
extern MC_Bit bdmc_LCD_modeAccueil;
extern MC_Bit bdmc_LCD_modeRun;
//Union en 1 octet de tous les bits dynamiques
extern MC_Data8 cdmc_LCD_dynamique;

//Definitions des variables de "LCD_ACK_STATUS_START"
extern MC_Bit bdmc_ACK_MOT_statusStart;
extern MC_Bit bdmc_ACK_RP1_statusStart;
extern MC_Bit bdmc_ACK_RP2_statusStart;
extern MC_Bit bdmc_ACK_BAL_statusStart;
extern MC_Bit bdmc_ACK_GSM_statusStart;
//Autres variables
extern MC_Data8 cdmc_LCD_var1Debug;
extern MC_Data8 cdmc_LCD_var2Debug;



///////////////////////////////////////////////////////////////////////////////
//Décomposition des datas de la trame mc_GSM_statusStart et mc_GSM_statusRun
///////////////////////////////////////////////////////////////////////////////
//config de toutes les datas de la trame "mc_GSM_statusRun"

typedef enum {
    GSM_VERSION_SOFT = 0,
} MC_GSM_STATUS_START_DATAS;

typedef enum {
    GSM_ERROR = 0,
    GSM_WARNING = 1,
    GSM_IO = 2,
    GSM_STATE_DYNAMIQUE = 3,
    GSM_VITESSE_REMOTE_CONTROL = 4,
    GSM_NB_FAIL_RX_PACKET_XBEE = 5,
    GSM_VAR1 = 6,
    GSM_VAR2 = 7,
} MC_GSM_STATUS_RUN_DATAS;

//config bits de la data "GSM_ERROR" de la trame "mc_MOT_statusRun"

typedef enum {
    GSM_CRASH_SOFT = 0,
} MC_GSM_STATUS_RUN_ERROR_BIT;

//config bits de la data "GSM_WARNING" de la trame "mc_MOT_statusRun"

typedef enum {
    GSM_INIT_EN_COURS = 0,
    GSM_FAILURE_ACK_ANTENNE = 1,
    GSM_BUG_SOFT = 4,
    GSM_CANRX_ERRORPASSIVE = 5,
    GSM_CANTX_ERRORPASSIVE = 6,
    GSM_CAN_BUS_OFF = 7,
} MC_GSM_STATUS_RUN_WARNING_BIT;

//config bits de la data "GSM_IO" de la trame "mc_MOT_statusRun"

typedef enum {
    GSM_SW1 = 0,
    GSM_SW2 = 1,
    GSM_OUT_J3 = 2,
    GSM_ETAT_LED_ROUGE = 3,
} MC_GSM_STATUS_RUN_IO_BIT;

//config bits de la data "MOT_STATE_DYNAMIQUE" de la trame "mc_MOT_statusRun"

typedef enum {
    GSM_MODE_REMOTE_CONTROL = 2,
    GSM_MOVE_SENS_REMOTE_CONTROL = 3,
} MC_GSM_STATUS_RUN_STATE_DYNAMIQUE_BIT;


////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_GSM_statusStart" et datas associées
extern uCAN1_MSG mc_GSM_statusStart;
extern MC_Data8 cdmc_GSM_versionSoft;

////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_GSM_statusRun" et datas associées
extern uCAN1_MSG mc_GSM_statusRun;
//Definitions des variables de "GSM_ERROR"
extern MC_Bit bdmc_GSM_crashSoft;
//Union en 1 octet de tous les bits d'erreur
extern MC_Data8 cdmc_GSM_erreurs;
//Definitions des variables de "GSM_WARNING"
extern MC_Bit bdmc_GSM_initEnCours;
extern MC_Bit bdmc_GSM_failureACK_Antenne;
extern MC_Bit bdmc_GSM_bugSoft;
extern MC_Bit bdmc_GSM_CAN_RxErrorPassive;
extern MC_Bit bdmc_GSM_CAN_TxErrorPassive;
extern MC_Bit bdmc_GSM_CAN_busOFF;
//Union en 1 octet de tous les bits warning
extern MC_Data8 cdmc_GSM_warnings;
//Definitions des variables de "GSM_IO"
extern MC_Bit bdmc_GSM_switch1;
extern MC_Bit bdmc_GSM_switch2;
extern MC_Bit bdmc_GSM_switchOUT_J3;
extern MC_Bit bdmc_GSM_Etat_Led_Rouge;
//Definitions des variables de "GSM_STATE_DYNAMIQUE"
extern MC_Bit bdmc_GSM_modeRemoteControl;
extern MC_Bit bdmc_GSM_moveSensREmoteControl;

//Union en 1 octet de tous les bits dynamiques
extern MC_Data8 cdmc_GSM_dynamique;

//Autres variables
extern MC_Data8 cdmc_consigneVitesseRemoteControl;
extern MC_Data8 cdmc_GSM_Nb_FailRxPacketXbee;
extern MC_Data8 cdmc_GSM_var1Debug;
extern MC_Data8 cdmc_GSM_var2Debug;



#endif	/*	ECAN1_DECLARATION_VAR_STATUS TRAIN_H	*/


