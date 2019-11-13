/**
  @Generated PIC24 / dsPIC33 / PIC32MM MCUs Source File

  @Company:
    Centrale Lille

  @File Name:
    ecan1_DefinitionVariable.h

  @Summary:
    This is the ecan1_DefinitionVariable.h file generated using PIC24 / dsPIC33 / PIC32MM MCUs

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



#ifndef ECAN1_DEFINITION_VARIABLE_H
#define	ECAN1_DEFINITION_VARIABLE_H

#include <stdint.h>


///lignes identiques à la génération MCC
/* ECAN message type identifiers */
#define CAN1_MSG_DATA           0x01
#define CAN1_MSG_RTR            0x02
#define CAN1_FRAME_EXT          0x03
#define CAN1_FRAME_STD          0x04
#define CAN1_BUF_FULL           0x05
#define CAN1_BUF_EMPTY         	0x06

typedef union {
    struct {
        uint32_t id;
        uint8_t idType;
        uint8_t msgtype;
        uint8_t dlc;
        uint8_t data0;
        uint8_t data1;
        uint8_t data2;
        uint8_t data3;
        uint8_t data4;
        uint8_t data5;
        uint8_t data6;
        uint8_t data7;
    } frame;
    unsigned char array[16];
} uCAN1_MSG;
/// Fin lignes identiques à la génération MCC

typedef struct {
    uint32_t IdValue;
    uint16_t IndiceData;
    uint16_t IndiceBit;
} MC_Bit;

typedef struct {
    uint32_t IdValue;
    uint16_t IndiceData;
} MC_Data8;

typedef struct {
    uint32_t IdValue;
    uint16_t IndiceData;
} MC_Data16;

typedef struct {
    uint32_t IdValue;
    uint16_t IndiceData;
} MC_Datafloat32;

typedef struct {
    uint32_t IdValue;
    uint16_t IndiceData;
} MC_Data32;



#endif	/* ECAN1_DEFINITION_VARIABLE_H */


/**
 End of File
*/
