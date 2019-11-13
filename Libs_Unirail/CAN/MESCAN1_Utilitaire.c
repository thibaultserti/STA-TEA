/**
  @Generated PIC24 / dsPIC33 / PIC32MM MCUs Source File

  @Company:
    Centrale Lille

  @File Name:
    MESCAN1_Utilitaire.c

  @Summary:
    This is the MESCAN1_Utilitaire.c file generated using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description: A LIRE IMPERATIVEMENT AVANT UTILISATION
 * 
 * Ces fonctions ne peuvent être utilisées que lorsque le message CAN a quitté 
 * la mémoire DMA du DsPIC, càd que le message a déjà été copié dans la RAM
 * "classique du DsPIC.
 * En d'autres termes, on peut manipuler toutes les messages CAN définis dans le
 * fichier "ecan1_DeclarationVarTrain.h"
 * 
 * 
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
#include "MESCAN1_Utilitaire.h"

void MESCAN_SetBitHigh(uCAN1_MSG *CanMsg, MC_Bit DefBit) {
    uint8_t valData;
    if (CanMsg->frame.id == DefBit.IdValue) {
        valData = CanMsg->array[OFFSET_DATA0_TO_7 + DefBit.IndiceData];
        CanMsg->array[OFFSET_DATA0_TO_7 + DefBit.IndiceData] = valData | (1 << DefBit.IndiceBit);
    } else {
        cptErreurDefinitionVar++;
    }
}

void MESCAN_SetBitLow(uCAN1_MSG *CanMsg, MC_Bit DefBit) {
    uint8_t valData;
    if (CanMsg->frame.id == DefBit.IdValue) {
        valData = CanMsg->array[OFFSET_DATA0_TO_7 + DefBit.IndiceData];
        CanMsg->array[OFFSET_DATA0_TO_7 + DefBit.IndiceData] = valData & (~(1 << DefBit.IndiceBit));
    } else {
        cptErreurDefinitionVar++;
    }
}

void MESCAN_SetBit(uCAN1_MSG *CanMsg, MC_Bit DefBit, bool valbit) {
    uint8_t valData;
    if (CanMsg->frame.id == DefBit.IdValue) {
        valData = CanMsg->array[OFFSET_DATA0_TO_7 + DefBit.IndiceData];
        if (valbit)
            CanMsg->array[OFFSET_DATA0_TO_7 + DefBit.IndiceData] |= valData | (1 << DefBit.IndiceBit);
        else
            CanMsg->array[OFFSET_DATA0_TO_7 + DefBit.IndiceData] &= valData & (~(1 << DefBit.IndiceBit));
    } else {
        cptErreurDefinitionVar++;
    }
}

bool MESCAN_GetBit(uCAN1_MSG *CanMsg, MC_Bit DefBit) {
    uint8_t valData;
    if (CanMsg->frame.id == DefBit.IdValue) {
        valData = CanMsg->array[OFFSET_DATA0_TO_7 + DefBit.IndiceData] & (1 << DefBit.IndiceBit);
        if (valData)
            return true;
        else
            return false;
    } else {
        cptErreurDefinitionVar++;
        return false;
    }
}

uint8_t MESCAN_GetData8(uCAN1_MSG *CanMsg, MC_Data8 DefData) {
    uint8_t valData = 0;
    if (CanMsg->frame.id == DefData.IdValue) {
        valData = CanMsg->array[OFFSET_DATA0_TO_7 + DefData.IndiceData];
    } else {
        cptErreurDefinitionVar++;
    }
    return valData;
}

void MESCAN_SetData8(uCAN1_MSG *CanMsg, MC_Data8 DefData, uint8_t Data) {
    if (CanMsg->frame.id == DefData.IdValue) {
        CanMsg->array[OFFSET_DATA0_TO_7 + DefData.IndiceData] = Data;
    } else {
        cptErreurDefinitionVar++;
    }
}

void MESCAN_DecrementeDataToZero(uCAN1_MSG *CanMsg, MC_Data8 DefData) {
    if (CanMsg->frame.id == DefData.IdValue) {
        if (CanMsg->array[OFFSET_DATA0_TO_7 + DefData.IndiceData])
            CanMsg->array[OFFSET_DATA0_TO_7 + DefData.IndiceData]--;;
    } else {
        cptErreurDefinitionVar++;
    }
}


void MESCAN_SetData16(uCAN1_MSG *CanMsg, MC_Data16 DefData16, uint16_t Data16) {
    if (CanMsg->frame.id == DefData16.IdValue) {
        CanMsg->array[OFFSET_DATA0_TO_7 + DefData16.IndiceData] = (uint8_t) Data16;
        CanMsg->array[OFFSET_DATA0_TO_7 +1 + DefData16.IndiceData] = Data16 >> 8;
    } else
        cptErreurDefinitionVar++;
}

uint16_t MESCAN_GetData16(uCAN1_MSG *CanMsg, MC_Data16 DefData16) {
    uint16_t ValData16 = 0;
    if (CanMsg->frame.id == DefData16.IdValue) {
        ValData16 = (CanMsg->array[OFFSET_DATA0_TO_7 +1 + DefData16.IndiceData]) << 8;
        ValData16 = ValData16 + CanMsg->array[OFFSET_DATA0_TO_7 + DefData16.IndiceData];
    } else
        cptErreurDefinitionVar++;
    return ValData16;
}

void MESCAN_SetData32(uCAN1_MSG *CanMsg, MC_Data32 DefData32, uint32_t Data32) {
    if (CanMsg->frame.id == DefData32.IdValue) {
        CanMsg->array[OFFSET_DATA0_TO_7 + DefData32.IndiceData] = (uint8_t) Data32;
        CanMsg->array[OFFSET_DATA0_TO_7 +1 + DefData32.IndiceData] = Data32 >> 8;
        CanMsg->array[OFFSET_DATA0_TO_7 +2 + DefData32.IndiceData] = Data32 >> 16;
        CanMsg->array[OFFSET_DATA0_TO_7 +3 + DefData32.IndiceData] = Data32 >> 24;
    } else
        cptErreurDefinitionVar++;
}

uint32_t MESCAN_GetData32(uCAN1_MSG *CanMsg, MC_Data32 DefData32) {
    uint32_t ValData32 = 0;
    if (CanMsg->frame.id == DefData32.IdValue) {
        ValData32 = CanMsg->array[OFFSET_DATA0_TO_7 +3 + DefData32.IndiceData] << 8;
        ValData32 = (ValData32 + CanMsg->array[OFFSET_DATA0_TO_7 +2 + DefData32.IndiceData]) << 8;
        ValData32 = (ValData32 + CanMsg->array[OFFSET_DATA0_TO_7 +1 + DefData32.IndiceData]) << 8;
        ValData32 = ValData32 + CanMsg->array[OFFSET_DATA0_TO_7 + DefData32.IndiceData];
    } else
        cptErreurDefinitionVar++;
    return ValData32;
}

void MESCAN_SetDataFloat32(uCAN1_MSG *CanMsg, MC_Datafloat32 DefDataFloat32, float ValFloat) {

    union entfloat {
        uint32_t D_long;
        float D_float;
    };

    union entfloat u;
    uint32_t Datalong;

    u.D_float = ValFloat;
    Datalong = u.D_long;
    if (CanMsg->frame.id == DefDataFloat32.IdValue) {

        CanMsg->array[OFFSET_DATA0_TO_7 + DefDataFloat32.IndiceData] = Datalong;
        CanMsg->array[OFFSET_DATA0_TO_7 +1 + DefDataFloat32.IndiceData] = Datalong >> 8;
        CanMsg->array[OFFSET_DATA0_TO_7 +2 + DefDataFloat32.IndiceData] = Datalong >> 16;
        CanMsg->array[OFFSET_DATA0_TO_7 +3 + DefDataFloat32.IndiceData] = Datalong >> 24;
    } else
        cptErreurDefinitionVar++;
}

float MESCAN_GetDataFloat32(uCAN1_MSG *CanMsg, MC_Datafloat32 DefDataFloat32) {

    union entfloat {
        uint32_t D_long;
        float D_float;
    };

    union entfloat u;
    uint32_t Datalong;
    float valFloat = 0;

    if (CanMsg->frame.id == DefDataFloat32.IdValue) {

        Datalong = (CanMsg->array[OFFSET_DATA0_TO_7 +3 + DefDataFloat32.IndiceData]) << 8;
        Datalong = Datalong + CanMsg->array[OFFSET_DATA0_TO_7 +2 + DefDataFloat32.IndiceData];
        Datalong = Datalong << 8;
        Datalong = Datalong + CanMsg->array[OFFSET_DATA0_TO_7 +1 + DefDataFloat32.IndiceData];
        Datalong = Datalong << 8;
        Datalong = Datalong + CanMsg->array[OFFSET_DATA0_TO_7 + DefDataFloat32.IndiceData];
        u.D_long = Datalong;
        valFloat = u.D_float;
    } else
        cptErreurDefinitionVar++;

    return valFloat;
}


void MESCAN_InitAndRAZ_Alldatas(uCAN1_MSG * MesCAN) {
    int i;
    MesCAN->frame.msgtype = CAN1_MSG_DATA;
    MesCAN->frame.idType = CAN1_FRAME_STD;
    for (i = OFFSET_DATA0_TO_7; i < 16; i++)
        MesCAN->array[i] = 0;
}

void MESCAN_DupliqueMessageWithDLC(uCAN1_MSG * SrcMesCAN, uCAN1_MSG * DestMesCAN)
{
    int i;
    DestMesCAN->frame.msgtype = SrcMesCAN->frame.msgtype;   //RTR ou Datas
    DestMesCAN->frame.dlc = SrcMesCAN->frame.dlc;
    for (i=7; i<15; i++)
        DestMesCAN->array[i] = SrcMesCAN->array[i];
}


void MESCAN_DupliqueMessageSaufDLC(uCAN1_MSG * SrcMesCAN, uCAN1_MSG * DestMesCAN)
{
    int i;
    DestMesCAN->frame.msgtype = SrcMesCAN->frame.msgtype;   //RTR ou Datas
    for (i=7; i<15; i++)
        DestMesCAN->array[i] = SrcMesCAN->array[i];
}

bool MESCAN_isDataTrame(uCAN1_MSG * MesCAN)
{
    if ( MesCAN->frame.msgtype == CAN1_MSG_DATA )
        return true;
    else
        return false;
}





/*  Exemple d'utilisation de la FIFO.
 * On déclare une variable type FILE "maFIFO_essai": 
 *      iFILE_MesCAN maFIFO_essai;
 * 
 * Il faut l'initialiser:
 *      InitFIFO_MesCAN(&maFIFO_essai);
 * 
 * Pour enfiler les messages:
 *      enfiler_MesCAN(&maFIFO_essai, msgReceiveFIFO); //Avec par exemple msgReceiveFIFO
 *      comme message CAN reçu.
 * 
 * Avant de défiler, il faut s'assurer que la file n'est pas vide: Exemple
 *         if (!isFileVide_MesCAN(&maFIFO_essai)) {
            DesabledInterrupt();
            defiler_MesCAN(&maFIFO_essai, &msgCAN_essai);
            EnabledInterrupt();
        }
 * On a récupéré un message CAN nommé "msgCAN_essai" de la file
 */
void MESCAN_InitFIFO(iFILE_MesCAN *F) {
    F->tete_FileCAN = 0;
    F->queue_FileCAN = 0;
    F->NbTransaction_FileCAN = 0;
}

int MESCAN_isFileVide(iFILE_MesCAN *F) {
        return (F->tete_FileCAN == F->queue_FileCAN);
}

bool MESCAN_enfiler(iFILE_MesCAN *F, uCAN1_MSG myReceiveMesCAN) {
    if (F->NbTransaction_FileCAN <= (TailleFIFO - 1)) {
        F->fileValue_FileCAN[F->queue_FileCAN] = myReceiveMesCAN;
        if (F->queue_FileCAN == TailleFIFO - 1)
            F->queue_FileCAN = 0;
        else
            F->queue_FileCAN++;

        F->NbTransaction_FileCAN++;
        return true;
    } else
        return false;
}

bool MESCAN_defiler(iFILE_MesCAN *F, uCAN1_MSG *MesCAN) {
    uCAN1_MSG myDefileMesCAN;
    int i;
    if (F->NbTransaction_FileCAN != 0) {
        myDefileMesCAN = F->fileValue_FileCAN[F->tete_FileCAN];

        MesCAN->frame.id = myDefileMesCAN.frame.id;
        MesCAN->frame.dlc = myDefileMesCAN.frame.dlc;
        MesCAN->frame.idType = myDefileMesCAN.frame.idType;
        MesCAN->frame.msgtype = myDefileMesCAN.frame.msgtype;
        for (i = 0; i < 8; i++) {
            MesCAN->array [i + 7] = myDefileMesCAN.array [i + 7];
        }

        if (F->tete_FileCAN == TailleFIFO - 1)
            F->tete_FileCAN = 0;
        else
            F->tete_FileCAN++;

        F->NbTransaction_FileCAN--;
        return true;
    } else
        return false;

}


/**
 End of File
*/

