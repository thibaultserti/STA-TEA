/**
  @Generated PIC24 / dsPIC33 / PIC32MM MCUs Source File

  @Company:
    Centrale Lille

  @File Name:
    MESCAN1_Enum_ID_DLC.h

  @Summary:
    This is the MESCAN1_DefinitionVarTrain.h file generated using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - pic24-dspic-pic32mm : 1.75.1
        Device            :  dsPIC33FJ128MC802
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.35
        MPLAB             :  MPLAB X v5.05

 * Created on 5 juillet 2019
 */

#ifndef MESCAN1_DEFINITION_VAR_TRAIN_H
#define	MESCAN1_DEFINITION_VAR_TRAIN_H


/**
  Section: Included Files
 */

//#include "../Librairie_DspicFJ/ecan1_DefinitionVariable.h"
#include "MESCAN1_DefinitionVariable.h"
#include "loco_MAIN_PARAMS.h"

#define CAN_SPEED_BUS       125

#define NB_MAX_CAR_MES_EBT  11  //Si on n'utilise pas les 4 octets EEPROM
//#define NB_MAX_CAR_MES_EBT  15  //Avec les 4 octets EEPROM

typedef enum {
    MC_ID_MOT_STATUS_RUN = 0x20,
    MC_ID_MOT_STATUS_START = 0xA0,
    MC_ID_RP1_STATUS_RUN = 0x21,
    MC_ID_RP1_STATUS_START = 0xA1,
    MC_ID_RP2_STATUS_RUN = 0x22,
    MC_ID_RP2_STATUS_START = 0xA2,
    MC_ID_BAL_STATUS_RUN = 0x23,
    MC_ID_BAL_STATUS_START = 0xA3,
    MC_ID_LCD_STATUS_RUN = 0x24,
    //MC_ID_LCD_STATUS_START = 0xA4, N'a pas de raison d'exister!!!
    MC_ID_GSM_STATUS_RUN = 0x25,
    MC_ID_GSM_STATUS_START = 0xA5,

    MC_ID_MESSAGE_GSM_SENT = 0x60,
    MC_ID_MESSAGE_GSM_RECEIVED = 0x70,

    MC_ID_ARRET_HARDWARE = 0x15,
    MC_ID_EEPROM = 0x1E,
    MC_ID_SCHEDULEUR_MESURES = 0x2F,

    MC_ID_STATE_SOFT_LOCO = 0x10,

    MC_ID_CONSIGNE_VITESSE = 0x17,
    MC_ID_CONSIGNE_VITESSE_LIMITE = 0x16,

    MC_ID_MESSAGE_EBT_RECEIVED = 0x30,

    MC_ID_MESSAGE_PARAM_KI_KP = 0x82,

    MC_ID_RECEIVE_ACK_RF_XBEE = 0x1A,

    MC_ID_GHOST_TRAME_CAN = 0x3E,
    MC_ID_SHADOWS_TRAME_CAN = 0x3F,
            
            MC_ID_WARNING = 0x0D,

} MC_ID;
//PS: MC_ID_XXX_STATUS_RUN doit etre l'Id de début des "statusRun"
#define MC_ID_XXX_STATUS_RUN    MC_ID_MOT_STATUS_RUN
#define MC_ID_XXX_STATUS_START   MC_ID_MOT_STATUS_START

typedef enum {
    MC_DLC_MOT_STATUS_RUN = 0x08,
    MC_DLC_MOT_STATUS_START = 0x01,
    MC_DLC_RP1_STATUS_RUN = 0x08,
    MC_DLC_RP1_STATUS_START = 0x05,
    MC_DLC_RP2_STATUS_RUN = 0x08,
    MC_DLC_RP2_STATUS_START = 0x05,
    MC_DLC_BAL_STATUS_RUN = 0x08,
    MC_DLC_BAL_STATUS_START = 0x01,
    MC_DLC_LCD_STATUS_RUN = 0x08,
    //MC_DLC_LCD_STATUS_START = 0x01, N'a pas de raison d'exister!!!
    MC_DLC_GSM_STATUS_RUN = 0x08,
    MC_DLC_GSM_STATUS_START = 0x01,

    MC_DLC_MESSAGE_GSM_SENT = 0x08,
    MC_DLC_MESSAGE_GSM_RECEIVED = 0x08,

    MC_DLC_ARRET_HARDWARE = 0x01,
    MC_DLC_EEPROM = 0x00, //A redefinir suivant (Offset ecriture ou lecture)
    MC_DLC_SCHEDULEUR_MESURES = 0x07,

    MC_DLC_STATE_SOFT_LOCO = 0x08,

    MC_DLC_CONSIGNE_VITESSE = 0x02,
    MC_DLC_CONSIGNE_VITESSE_LIMITE = 0x01,

    MC_DLC_MESSAGE_EBT_RECEIVED = 0x08,

    MC_DLC_MESSAGE_PARAM_KI_KP = 0x08,

    MC_DLC_RECEIVE_ACK_RF_XBEE = 0x2,

    MC_DLC_GHOST_TRAME_CAN = 0x0, //longueur variable, force par la telecomande
    MC_DLC_SHADOWS_TRAME_CAN = 0x0, //longueur variable, force par la telecomande
            
            MC_DLC_WARNING = 0x03,

} MC_DLC;

typedef enum {
    MC_SHORTNAME_MOT = 0x0,
    MC_SHORTNAME_RP1 = 0x1,
    MC_SHORTNAME_RP2 = 0x2,
    MC_SHORTNAME_BAL = 0x3,
    MC_SHORTNAME_LCD = 0x4,
    MC_SHORTNAME_GSM = 0x5,

} MC_SHORTNAME_PROC;

typedef enum {
    HARDWARE = 0,
    SOFTWARE = 0x10,
    CAUSES_EXTERNES = 0x20,
} TYPE_WARNING;

#endif


