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
////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_MOT_statusStart" et datas associées
uCAN1_MSG mc_MOT_statusStart = {
    {MC_ID_MOT_STATUS_START,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_MOT_STATUS_START,
        0, 0, 0, 0, 0, 0, 0, 0}
};
MC_Data8 cdmc_MOT_versionSoft = {
    MC_ID_MOT_STATUS_START,
    MOT_VERSION_SOFT,
};

////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_MOT_statusRun" et datas associées
uCAN1_MSG mc_MOT_statusRun = {
    {MC_ID_MOT_STATUS_RUN,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_MOT_STATUS_RUN,
        0, 0, 0, 0, 0, 0, 0, 0}
};
//Definitions des variables de "MOT_ERROR"
MC_Bit bdmc_MOT_crashSoft = {
    MC_ID_MOT_STATUS_RUN,
    MOT_ERROR,
    MOT_CRASH_SOFT,
};
MC_Bit bdmc_MOT_securiteErreurPI = {
    MC_ID_MOT_STATUS_RUN,
    MOT_ERROR,
    MOT_SECU_PI,
};
MC_Bit bdmc_stopLoco_XXX_CrashSoft = {
    MC_ID_MOT_STATUS_RUN,
    MOT_ERROR,
    STOP_LOCO_XXX_CRASH_SOFT,
};
//Union en 1 octet de tous les bits d'erreur
MC_Data8 cdmc_MOT_erreurs = {
    MC_ID_MOT_STATUS_RUN,
    MOT_ERROR,
};
//Union en 1 octet de tous les bits warning
MC_Data8 cdmc_MOT_warnings = {
    MC_ID_MOT_STATUS_RUN,
    MOT_WARNING,
};

//Definitions des variables de "MOT_WARNING"
MC_Bit bdmc_MOT_initEnCours = {
    MC_ID_MOT_STATUS_RUN,
    MOT_WARNING,
    MOT_INIT_EN_COURS,
};
MC_Bit bdmc_noPoweredByRails = {
    MC_ID_MOT_STATUS_RUN,
    MOT_WARNING,
    ELECTRIFICATION_RAIL,
};
MC_Bit bdmc_batterieFaible = {
    MC_ID_MOT_STATUS_RUN,
    MOT_WARNING,
    BATTERIE_FAIBLE,
};
MC_Bit bdmc_MOT_bugSoft = {
    MC_ID_MOT_STATUS_RUN,
    MOT_WARNING,
    MOT_BUG_SOFT,
};
MC_Bit bdmc_MOT_CAN_RxErrorPassive = {
    MC_ID_MOT_STATUS_RUN,
    MOT_WARNING,
    MOT_CANRX_ERRORPASSIVE,
};
MC_Bit bdmc_MOT_CAN_TxErrorPassive = {
    MC_ID_MOT_STATUS_RUN,
    MOT_WARNING,
    MOT_CANTX_ERRORPASSIVE,
};
MC_Bit bdmc_MOT_CAN_busOFF = {
    MC_ID_MOT_STATUS_RUN,
    MOT_WARNING,
    MOT_CAN_BUS_OFF,
};
//Definitions des variables de "MOT_IO"
MC_Bit bdmc_MOT_jumper2 = {
    MC_ID_MOT_STATUS_RUN,
    MOT_IO,
    MOT_JUMPER2,
};
MC_Bit bdmc_MOT_jumper3 = {
    MC_ID_MOT_STATUS_RUN,
    MOT_IO,
    MOT_JUMPER3,
};
MC_Bit bdmc_MOT_jumper4 = {
    MC_ID_MOT_STATUS_RUN,
    MOT_IO,
    MOT_JUMPER4,
};
MC_Bit bdmc_MOT_sw1 = {
    MC_ID_MOT_STATUS_RUN,
    MOT_IO,
    MOT_SW1,
};
MC_Bit bdmc_MOT_sw2 = {
    MC_ID_MOT_STATUS_RUN,
    MOT_IO,
    MOT_SW2,
};
//Definitions des variables de "MOT_STATE_DYNAMIQUE"
MC_Bit bdmc_modeLocoOFF = {
    MC_ID_MOT_STATUS_RUN,
    MOT_STATE_DYNAMIQUE,
    MOT_MODE_LOCO_OFF,
};
MC_Bit bdmc_modeMoveLocoManuelOrRemote = {
    MC_ID_MOT_STATUS_RUN,
    MOT_STATE_DYNAMIQUE,
    MODE_MOVE_LOCO_MANUEL_OR_REMOTE,
};
MC_Bit bdmc_moveSensLocoManuelOrRemote = {
    MC_ID_MOT_STATUS_RUN,
    MOT_STATE_DYNAMIQUE,
    MOVE_SENS_LOCO_MANUEL_OR_REMOTE,
};
//Union en 1 octet de tous les bits dynamiques
MC_Data8 cdmc_MOT_dynamique = {
    MC_ID_MOT_STATUS_RUN,
    MOT_STATE_DYNAMIQUE,
};

//Autres variables
MC_Data16 wdmc_tensionBatterie = {
    MC_ID_MOT_STATUS_RUN,
    MOT_VBAT,
};
MC_Data8 cdmc_MOT_var1Debug = {
    MC_ID_MOT_STATUS_RUN,
    MOT_VAR1,
};
MC_Data8 cdmc_MOT_var2Debug = {
    MC_ID_MOT_STATUS_RUN,
    MOT_VAR2,
};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//Décomposition des datas de la trame mc_RP1_statusStart et mc_RP1_statusRun
///////////////////////////////////////////////////////////////////////////////
//config de toutes les datas de la trame "mc_RP1_statusStart"

uCAN1_MSG mc_RP1_statusStart = {
    {MC_ID_RP1_STATUS_START,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_RP1_STATUS_START,
        0, 0, 0, 0, 0, 0, 0, 0}
};

MC_Data8 cdmc_RP1_versionSoft = {
    MC_ID_RP1_STATUS_START,
    RP1_VERSION_SOFT,
};

MC_Data32 ldmc_adresseIP_RP1 = {
    MC_ID_RP1_STATUS_START,
    RP1_ADRESSE_IP,
};


////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_RP1_statusRun" et datas associees
////////////////////////////////////////////////////////////////////////////////
uCAN1_MSG mc_RP1_statusRun = {
    {MC_ID_RP1_STATUS_RUN,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_RP1_STATUS_RUN,
        0, 0, 0, 0, 0, 0, 0, 0}
};
MC_Bit bdmc_RP1_crashSoft = {
    MC_ID_RP1_STATUS_RUN,
    RP1_ERROR,
    RP1_CRASH_SOFT,
};
//Union en 1 octet de tous les bits erreurs
MC_Data8 cdmc_RP1_erreurs = {
    MC_ID_RP1_STATUS_RUN,
    RP1_ERROR,
};

//Definitions des variables de "RP1_WARNING"
MC_Bit bdmc_RP1_initEnCours = {
    MC_ID_RP1_STATUS_RUN,
    RP1_WARNING,
    RP1_INIT_EN_COURS,
};

MC_Bit bdmc_RP1_bugSoft = {
    MC_ID_RP1_STATUS_RUN,
    RP1_WARNING,
    RP1_BUG_SOFT,
};
MC_Bit bdmc_RP1_CAN_RxErrorPassive = {
    MC_ID_RP1_STATUS_RUN,
    RP1_WARNING,
    RP1_CANRX_ERRORPASSIVE,
};
MC_Bit bdmc_RP1_CAN_TxErrorPassive = {
    MC_ID_RP1_STATUS_RUN,
    RP1_WARNING,
    RP1_CANTX_ERRORPASSIVE,
};
MC_Bit bdmc_RP1_CAN_busOFF = {
    MC_ID_RP1_STATUS_RUN,
    RP1_WARNING,
    RP1_CAN_BUS_OFF,
};
//Union en 1 octet de tous les bits warning
MC_Data8 cdmc_RP1_warnings = {
    MC_ID_RP1_STATUS_RUN,
    RP1_WARNING,
};


//Definitions des variables de "RP1_IO"
MC_Bit bdmc_presenceCamera = {
    MC_ID_RP1_STATUS_RUN,
    RP1_IO,
    RP1_CAMERA,
};

MC_Bit bdmc_RP1_jumperCfg1 = {
    MC_ID_RP1_STATUS_RUN,
    RP1_IO,
    RP1_JUMPER_CFG1,
};

MC_Bit bdmc_RP1_jumperCfg2 = {
    MC_ID_RP1_STATUS_RUN,
    RP1_IO,
    RP1_JUMPER_CFG2,
};

//Definitions des variables de "RP1_STATE_DYNAMIQUE"
MC_Bit bdmc_RP1_etatConnexion_TCP_IP = {
    MC_ID_RP1_STATUS_RUN,
    RP1_STATE_DYNAMIQUE,
    RP1_ETAT_CONNECTION_TCP_IP,
};

MC_Bit bdmc_RP1_etatConnexionWIFI = {
    MC_ID_RP1_STATUS_RUN,
    RP1_STATE_DYNAMIQUE,
    RP1_ETAT_CONNECTION__WIFI,
};

MC_Bit bdmc_etatConnexionCamera = {
    MC_ID_RP1_STATUS_RUN,
    RP1_STATE_DYNAMIQUE,
    RP1_ETAT_CONNECTION_CAMERA,
};
//Union en 1 octet de tous les bits dynamiques
MC_Data8 cdmc_RP1_dynamique = {
    MC_ID_RP1_STATUS_RUN,
    RP1_STATE_DYNAMIQUE,
};

//Autres variables
MC_Data8 cdmc_RP1_configONBOARD = {
    MC_ID_RP1_STATUS_RUN,
    RP1_CONFIG_ONBOARD,
};
MC_Data8 cdmc_RP1_var1Debug = {
    MC_ID_RP1_STATUS_RUN,
    RP1_VAR1,
};
MC_Data8 cdmc_RP1_var2Debug = {
    MC_ID_RP1_STATUS_RUN,
    RP1_VAR2,
};



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//Décomposition des datas de la trame mc_RP2_statusStart et mc_RP2_statusRun
///////////////////////////////////////////////////////////////////////////////
//config de toutes les datas de la trame "mc_RP1_statusStart"


////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_RP2_statusStart" et datas associees
uCAN1_MSG mc_RP2_statusStart = {
    {MC_ID_RP2_STATUS_START,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_RP2_STATUS_START,
        0, 0, 0, 0, 0, 0, 0, 0}
};

MC_Data8 cdmc_RP2_versionSoft = {
    MC_ID_RP2_STATUS_START,
    RP2_VERSION_SOFT,
};

MC_Data32 ldmc_adresseIP_RP2 = {
    MC_ID_RP2_STATUS_START,
    RP2_ADRESSE_IP,
};

////////////////////////////////////////////////////////////////////////////////
// Declaration de la trame "mc_RP2_statusRun" et datas associees
////////////////////////////////////////////////////////////////////////////////
uCAN1_MSG mc_RP2_statusRun = {
    {MC_ID_RP2_STATUS_RUN,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_RP2_STATUS_RUN,
        0, 0, 0, 0, 0, 0, 0, 0}
};

MC_Bit bdmc_RP2_crashSoft = {
    MC_ID_RP2_STATUS_RUN,
    RP2_ERROR,
    RP2_CRASH_SOFT,
};

//Union en 1 octet de tous les bits erreurs
MC_Data8 cdmc_RP2_erreurs = {
    MC_ID_RP2_STATUS_RUN,
    RP2_ERROR,
};

//Definitions des variables de "RP2_WARNING"
MC_Bit bdmc_RP2_initEnCours = {
    MC_ID_RP2_STATUS_RUN,
    RP2_WARNING,
    RP2_INIT_EN_COURS,
};

MC_Bit bdmc_RP2_bugSoft = {
    MC_ID_RP2_STATUS_RUN,
    RP2_WARNING,
    RP2_BUG_SOFT,
};
MC_Bit bdmc_RP2_CAN_RxErrorPassive = {
    MC_ID_RP2_STATUS_RUN,
    RP2_WARNING,
    RP2_CANRX_ERRORPASSIVE,
};
MC_Bit bdmc_RP2_CAN_TxErrorPassive = {
    MC_ID_RP2_STATUS_RUN,
    RP2_WARNING,
    RP2_CANTX_ERRORPASSIVE,
};
MC_Bit bdmc_RP2_CAN_busOFF = {
    MC_ID_RP2_STATUS_RUN,
    RP2_WARNING,
    RP2_CAN_BUS_OFF,
};

//Union en 1 octet de tous les bits warning
MC_Data8 cdmc_RP2_warnings = {
    MC_ID_RP2_STATUS_RUN,
    RP2_WARNING,
};

//Definitions des variables de "RP2_IO"

//MC_Bit bdmc_RP2_xxxx = {
//    MC_ID_RP2_STATUS_RUN,
//    RP1_IO,
//    RP1_XXXXX,
//};

//Definitions des variables de "RP2_STATE_DYNAMIQUE"
MC_Bit bdmc_RP2_etatConnexion_TCP_IP = {
    MC_ID_RP2_STATUS_RUN,
    RP2_STATE_DYNAMIQUE,
    RP2_ETAT_CONNECTION_TCP_IP,
};

MC_Bit bdmc_RP2_etatConnexionWIFI = {
    MC_ID_RP2_STATUS_RUN,
    RP2_STATE_DYNAMIQUE,
    RP2_ETAT_CONNECTION__WIFI,
};

//Union en 1 octet de tous les bits dynamiques
MC_Data8 cdmc_RP2_dynamique = {
    MC_ID_RP2_STATUS_RUN,
    RP2_STATE_DYNAMIQUE,
};

//Autres variables
MC_Data8 cdmc_RP2_var1Debug = {
    MC_ID_RP2_STATUS_RUN,
    RP2_VAR1,
};

MC_Data8 cdmc_RP2_var2Debug = {
    MC_ID_RP2_STATUS_RUN,
    RP2_VAR2,
};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//Décomposition des datas de la trame mc_BAL_statusStart et mc_BAL_statusRun
///////////////////////////////////////////////////////////////////////////////
//config de toutes les datas de la trame "mc_BAL_statusRun"


////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_BAL_statusStart" et datas associées
uCAN1_MSG mc_BAL_statusStart = {
    {MC_ID_BAL_STATUS_START,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_GSM_STATUS_START,
        0, 0, 0, 0, 0, 0, 0, 0}
};
MC_Data8 cdmc_BAL_versionSoft = {
    MC_ID_BAL_STATUS_START,
    BAL_VERSION_SOFT,
};


////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_BAL_statusRun" et datas associées
uCAN1_MSG mc_BAL_statusRun = {
    {MC_ID_BAL_STATUS_RUN,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_BAL_STATUS_RUN,
        0, 0, 0, 0, 0, 0, 0, 0}
};
//Definitions des variables de "GSM_ERROR"
MC_Bit bdmc_BAL_crashSoft = {
    MC_ID_BAL_STATUS_RUN,
    BAL_ERROR,
    BAL_CRASH_SOFT,
};
//Union en 1 octet de tous les bits d'erreur
MC_Data8 cdmc_BAL_erreurs = {
    MC_ID_BAL_STATUS_RUN,
    BAL_ERROR,
};
//Definitions des variables de "GSM_WARNING"
MC_Bit bdmc_BAL_initEnCours = {
    MC_ID_BAL_STATUS_RUN,
    BAL_WARNING,
    BAL_INIT_EN_COURS,
};
MC_Bit bdmc_BAL_BadComWithInfra = {
    MC_ID_BAL_STATUS_RUN,
    BAL_WARNING,
    BAL_ECHEC_COM_BALI_AVEC_INFRA,
};
MC_Bit bdmc_BAL_bugSoft = {
    MC_ID_BAL_STATUS_RUN,
    BAL_WARNING,
    BAL_BUG_SOFT,
};
MC_Bit bdmc_BAL_CAN_RxErrorPassive = {
    MC_ID_BAL_STATUS_RUN,
    BAL_WARNING,
    BAL_CANRX_ERRORPASSIVE,
};
MC_Bit bdmc_BAL_CAN_TxErrorPassive = {
    MC_ID_BAL_STATUS_RUN,
    BAL_WARNING,
    BAL_CANTX_ERRORPASSIVE,
};
MC_Bit bdmc_BAL_CAN_busOFF = {
    MC_ID_BAL_STATUS_RUN,
    BAL_WARNING,
    BAL_CAN_BUS_OFF,
};
//Union en 1 octet de tous les bits warning
MC_Data8 cdmc_BAL_warnings = {
    MC_ID_BAL_STATUS_RUN,
    BAL_WARNING,
};

//Definitions des variables de "BAL_IO"
MC_Bit bdmc_BAL_poids1RoueCodeuse = {
    MC_ID_BAL_STATUS_RUN,
    BAL_IO,
    BAL_POIDS_1_RC,
};
MC_Bit bdmc_BAL_poids2RoueCodeuse = {
    MC_ID_BAL_STATUS_RUN,
    BAL_IO,
    BAL_POIDS_2_RC,
};
MC_Bit bdmc_BAL_poids4RoueCodeuse = {
    MC_ID_BAL_STATUS_RUN,
    BAL_IO,
    BAL_POIDS_4_RC,
};
MC_Bit bdmc_BAL_poids8RoueCodeuse = {
    MC_ID_BAL_STATUS_RUN,
    BAL_IO,
    BAL_POIDS_8_RC,
};
MC_Bit bdmc_BAL_jumper1_RC = {
    MC_ID_BAL_STATUS_RUN,
    BAL_IO,
    BAL_JUMPER1_RC,
};
MC_Bit bdmc_BAL_swRC1 = {
    MC_ID_BAL_STATUS_RUN,
    BAL_IO,
    BAL_SW_RC1,
};
//Union en 1 octet de tous les bits IO
MC_Data8 cdmc_BAL_IO = {
    MC_ID_BAL_STATUS_RUN,
    BAL_IO,
};

//Union en 1 octet de tous les bits dynamiques
MC_Data8 cdmc_BAL_dynamique = {
    MC_ID_BAL_STATUS_RUN,
    BAL_STATE_DYNAMIQUE,
};

//Variable pour status commnication entre balise et infra
MC_Data8 cdmc_BAL_statusComBalise = {
    MC_ID_BAL_STATUS_RUN,
    BAL_STATUS_COM_BALISE,
};

//Variable qui indique le dernier numero de balise detectee par le train
MC_Data8 cdmc_BAL_lastNumberOfDetectedBali = {
    MC_ID_BAL_STATUS_RUN,
    BAL_NUMBER_LAST_BALISE,
};

//Autres variables
MC_Data8 cdmc_BAL_var1Debug = {
    MC_ID_BAL_STATUS_RUN,
    BAL_VAR1,
};
MC_Data8 cdmc_BAL_var2Debug = {
    MC_ID_BAL_STATUS_RUN,
    BAL_VAR2,
};



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_LCD_statusRun"
uCAN1_MSG mc_LCD_statusRun = {
    {MC_ID_LCD_STATUS_RUN,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_LCD_STATUS_RUN,
        0, 0, 0, 0, 0, 0, 0, 0}
};
//Definitions des variables de "LCD_ERROR"
MC_Bit bdmc_LCD_crashSoft = {
    MC_ID_LCD_STATUS_RUN,
    LCD_ERROR,
    LCD_CRASH_SOFT,
};
//Union en 1 octet de tous les bits d'erreur
MC_Data8 cdmc_LCD_erreurs = {
    MC_ID_LCD_STATUS_RUN,
    LCD_ERROR,
};
//Definitions des variables de "LCD_WARNING"
MC_Bit bdmc_LCD_initEnCours = {
    MC_ID_LCD_STATUS_RUN,
    LCD_WARNING,
    LCD_INIT_EN_COURS,
};
MC_Bit bdmc_LCD_bugSoft = {
    MC_ID_LCD_STATUS_RUN,
    LCD_WARNING,
    LCD_BUG_SOFT,
};

MC_Bit bdmcLCD_CAN_RxErrorPassive = {
    MC_ID_LCD_STATUS_RUN,
    LCD_WARNING,
    LCD_CANRX_ERRORPASSIVE,
};
MC_Bit bdmc_LCD_CAN_TxErrorPassive = {
    MC_ID_LCD_STATUS_RUN,
    LCD_WARNING,
    LCD_CANTX_ERRORPASSIVE,
};
MC_Bit bdmc_LCD_CAN_busOFF = {
    MC_ID_LCD_STATUS_RUN,
    LCD_WARNING,
    LCD_CAN_BUS_OFF,
};
//Union en 1 octet de tous les bits d'erreur
MC_Data8 cdmc_LCD_warnings = {
    MC_ID_LCD_STATUS_RUN,
    LCD_WARNING,
};
//Definitions des variables de "LCD_IO"
MC_Bit bdmc_LCD_sw1 = {
    MC_ID_LCD_STATUS_RUN,
    LCD_IO,
    LCD_SW1,
};
MC_Bit bdmc_LCD_sw2 = {
    MC_ID_LCD_STATUS_RUN,
    LCD_IO,
    LCD_SW2,
};
//Definitions des variables de "LCD_STATE_DYNAMIQUE"
MC_Bit bdmc_LCD_modeAccueil = {
    MC_ID_LCD_STATUS_RUN,
    LCD_STATE_DYNAMIQUE,
    LCD_MODE_ACCUEIL,
};
MC_Bit bdmc_LCD_modeRun = {
    MC_ID_LCD_STATUS_RUN,
    LCD_STATE_DYNAMIQUE,
    LCD_MODE_RUN,
};
//Union en 1 octet de tous les bits dynamiques
MC_Data8 cdmc_LCD_dynamique = {
    MC_ID_LCD_STATUS_RUN,
    LCD_STATE_DYNAMIQUE,
};

//Definitions des variables de "LCD_ACK_STATUS_START"
MC_Bit bdmc_ACK_MOT_statusStart = {
    MC_ID_LCD_STATUS_RUN,
    LCD_ACK_XXX_STATUS_START,
    ACK_MOT_STATUS_START,
};
MC_Bit bdmc_ACK_RP1_statusStart = {
    MC_ID_LCD_STATUS_RUN,
    LCD_ACK_XXX_STATUS_START,
    ACK_RP1_STATUS_START,
};
MC_Bit bdmc_ACK_RP2_statusStart = {
    MC_ID_LCD_STATUS_RUN,
    LCD_ACK_XXX_STATUS_START,
    ACK_RP2_STATUS_START,
};
MC_Bit bdmc_ACK_BAL_statusStart = {
    MC_ID_LCD_STATUS_RUN,
    LCD_ACK_XXX_STATUS_START,
    ACK_BAL_STATUS_START,
};
MC_Bit bdmc_ACK_GSM_statusStart = {
    MC_ID_LCD_STATUS_RUN,
    LCD_ACK_XXX_STATUS_START,
    ACK_GSM_STATUS_START,
};

//Autres variables
MC_Data8 cdmc_LCD_var1Debug = {
    MC_ID_LCD_STATUS_RUN,
    LCD_VAR1,
};
MC_Data8 cdmc_LCD_var2Debug = {
    MC_ID_LCD_STATUS_RUN,
    LCD_VAR2,
};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_GSM_statusStart" et datas associées
uCAN1_MSG mc_GSM_statusStart = {
    {MC_ID_GSM_STATUS_START,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_GSM_STATUS_START,
        0, 0, 0, 0, 0, 0, 0, 0}
};
MC_Data8 cdmc_GSM_versionSoft = {
    MC_ID_GSM_STATUS_START,
    GSM_VERSION_SOFT,
};


////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// Déclaration de la trame "mc_GSM_statusRun" et datas associées
uCAN1_MSG mc_GSM_statusRun = {
    {MC_ID_GSM_STATUS_RUN,
        CAN1_FRAME_STD, CAN1_MSG_DATA, MC_DLC_GSM_STATUS_RUN,
        0, 0, 0, 0, 0, 0, 0, 0}
};
//Definitions des variables de "GSM_ERROR"
MC_Bit bdmc_GSM_crashSoft = {
    MC_ID_GSM_STATUS_RUN,
    GSM_ERROR,
    GSM_CRASH_SOFT,
};
//Union en 1 octet de tous les bits d'erreur
MC_Data8 cdmc_GSM_erreurs = {
    MC_ID_GSM_STATUS_RUN,
    GSM_ERROR,
};
//Definitions des variables de "GSM_WARNING"
MC_Bit bdmc_GSM_initEnCours = {
    MC_ID_GSM_STATUS_RUN,
    GSM_WARNING,
    GSM_INIT_EN_COURS,
};
MC_Bit bdmc_GSM_failureACK_Antenne = {
    MC_ID_GSM_STATUS_RUN,
    GSM_WARNING,
    GSM_FAILURE_ACK_ANTENNE,
};
MC_Bit bdmc_GSM_bugSoft = {
    MC_ID_GSM_STATUS_RUN,
    GSM_WARNING,
    GSM_BUG_SOFT,
};
MC_Bit bdmc_GSM_CAN_RxErrorPassive = {
    MC_ID_GSM_STATUS_RUN,
    GSM_WARNING,
    GSM_CANRX_ERRORPASSIVE,
};
MC_Bit bdmc_GSM_CAN_TxErrorPassive = {
    MC_ID_GSM_STATUS_RUN,
    GSM_WARNING,
    GSM_CANTX_ERRORPASSIVE,
};
MC_Bit bdmc_GSM_CAN_busOFF = {
    MC_ID_GSM_STATUS_RUN,
    GSM_WARNING,
    GSM_CAN_BUS_OFF,
};
//Union en 1 octet de tous les bits warning
MC_Data8 cdmc_GSM_warnings = {
    MC_ID_GSM_STATUS_RUN,
    GSM_WARNING,
};
//Definitions des variables de "GSM_IO"
MC_Bit bdmc_GSM_switch1 = {
    MC_ID_GSM_STATUS_RUN,
    GSM_IO,
    GSM_SW1,
};
MC_Bit bdmc_GSM_switch2 = {
    MC_ID_GSM_STATUS_RUN,
    GSM_IO,
    GSM_SW2,
};
MC_Bit bdmc_GSM_switchOUT_J3 = {
    MC_ID_GSM_STATUS_RUN,
    GSM_IO,
    GSM_OUT_J3,
};
MC_Bit bdmc_GSM_Etat_Led_Rouge = {
    MC_ID_GSM_STATUS_RUN,
    GSM_IO,
    GSM_ETAT_LED_ROUGE,
};
//Definitions des variables de "GSM_STATE_DYNAMIQUE"
MC_Bit bdmc_GSM_modeRemoteControl = {
    MC_ID_GSM_STATUS_RUN,
    GSM_STATE_DYNAMIQUE,
    GSM_MODE_REMOTE_CONTROL,
};
MC_Bit bdmc_GSM_moveSensREmoteControl = {
    MC_ID_GSM_STATUS_RUN,
    GSM_STATE_DYNAMIQUE,
    GSM_MOVE_SENS_REMOTE_CONTROL,
};

//Union en 1 octet de tous les bits dynamiques
MC_Data8 cdmc_GSM_dynamique = {
    MC_ID_GSM_STATUS_RUN,
    GSM_STATE_DYNAMIQUE,
};

//Autres variables
MC_Data8 cdmc_consigneVitesseRemoteControl = {
    MC_ID_GSM_STATUS_RUN,
    GSM_VITESSE_REMOTE_CONTROL,
};
MC_Data8 cdmc_GSM_Nb_FailRxPacketXbee = {
    MC_ID_GSM_STATUS_RUN,
    GSM_NB_FAIL_RX_PACKET_XBEE,
};
MC_Data8 cdmc_GSM_var1Debug = {
    MC_ID_GSM_STATUS_RUN,
    GSM_VAR1,
};
MC_Data8 cdmc_GSM_var2Debug = {
    MC_ID_GSM_STATUS_RUN,
    GSM_VAR2,
};





