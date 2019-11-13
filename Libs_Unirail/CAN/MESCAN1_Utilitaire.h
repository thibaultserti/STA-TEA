/**
  @Generated PIC24 / dsPIC33 / PIC32MM MCUs Source File

  @Company:
    Centrale Lille

  @File Name:
    MESCAN1_Utilitaire.h

  @Summary:
    This is the MESCAN1_Utilitaire.h file generated using PIC24 / dsPIC33 / PIC32MM MCUs

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


#ifndef UTILITAIRECAN_H
#define	UTILITAIRECAN_H

/**
  Section: Included Files
 */
//#include <xc.h>
//#include "ecan1_DsPICFJ.h"
//#include "ecan1_Addon.h"
#include <stdbool.h>
//#include "../Librairie_DspicFJ/ecan1_DefinitionVariable.h"
#include "MESCAN1_DefinitionVariable.h"

//#include "ecan1_DeclarationVarTrain.h"
extern uint16_t cptErreurDefinitionVar;

#define HIGH    1
#define LOW     0

#define OFFSET_DATA0_TO_7   7

#define TailleFIFO 	20
    
typedef	struct fileReceiveMesCAN 
{
	int tete_FileCAN;
	int queue_FileCAN;
	int	NbTransaction_FileCAN;
	uCAN1_MSG fileValue_FileCAN[TailleFIFO];
} iFILE_MesCAN;



/******************************************************************************
 *                                                                             
 *    Function:		
 *    Description: Positionne "High" un bit particulier d'une data d'une trame CAN
 * MC_Bit est definit de la façon suivante
 *      typedef struct {
            uint32_t IdValue;       //  Identifiant de la trame CAN
            uint16_t IndiceData;    //  Numéro de la data dans le message CAN (de 0 à 7)
            uint16_t IndiceBit;     //  Numéro du bit dans la data message CAN (de 0 à 7)
        } MC_Bit; 
 * Cette fonction vérifie la cohérence de MC_Bit (bien été définit dans la bonne trame CAN)
 * Càd qu'il vérifie que l'Id correspond bien à la variable bit déclarée
 * Dans le cas contraire, une variable globale "cptErreurDefinitionVar" sera
 * incrémentée.
 *    Arguments:		message CAN "mc_xxxx"  et la structure data du bit 
 *    Return Value:  None
 *                                                                                                   
 ******************************************************************************/
void MESCAN_SetBitHigh(uCAN1_MSG *CanMsg, MC_Bit DefBit);


/******************************************************************************
 *                                                                             
 *    Function:		
 *    Description:   
 *    Arguments:		None  
 *    Return Value:  None
 *                                                                                                   
 ******************************************************************************/
void MESCAN_SetBitLow(uCAN1_MSG *CanMsg, MC_Bit DefBit);


/******************************************************************************
 *                                                                             
 *    Function:		
 *    Description:   
 *    Arguments:		None  
 *    Return Value:  None
 *                                                                                                   
 ******************************************************************************/
void MESCAN_SetBit(uCAN1_MSG *CanMsg, MC_Bit DefBit, bool valbit);


/******************************************************************************
 *                                                                             
 *    Function:		
 *    Description:   
 *    Arguments:		None  
 *    Return Value:  None
 *                                                                                                   
 ******************************************************************************/
bool MESCAN_GetBit(uCAN1_MSG *CanMsg, MC_Bit DefBit);


/******************************************************************************
 *                                                                             
 *    Function:		
 *    Description:   
 *    Arguments:		None  
 *    Return Value:  None
 *                                                                                                   
 ******************************************************************************/
uint8_t MESCAN_GetData8(uCAN1_MSG *CanMsg, MC_Data8 DefData);


/******************************************************************************
 *                                                                             
 *    Function:		
 *    Description:   
 *    Arguments:		None  
 *    Return Value:  None
 *                                                                                                   
 ******************************************************************************/
void MESCAN_SetData8(uCAN1_MSG *CanMsg, MC_Data8 DefData, uint8_t Data);


/******************************************************************************
 *                                                                             
 *    Function:		
 *    Description:   
 *    Arguments:		None  
 *    Return Value:  None
 *                                                                                                   
 ******************************************************************************/
void MESCAN_DecrementeDataToZero(uCAN1_MSG *CanMsg, MC_Data8 DefData);


/******************************************************************************
 *                                                                             
 *    Function:		
 *    Description:   
 *    Arguments:		None  
 *    Return Value:  None
 *                                                                                                   
 ******************************************************************************/
void MESCAN_SetData16(uCAN1_MSG *CanMsg, MC_Data16 DefData16, uint16_t Data16);

/******************************************************************************
 *                                                                             
 *    Function:		
 *    Description:   
 *    Arguments:		None  
 *    Return Value:  None
 *                                                                                                   
 ******************************************************************************/
uint16_t MESCAN_GetData16(uCAN1_MSG *CanMsg, MC_Data16 DefData16);

/******************************************************************************
 *                                                                             
 *    Function:		
 *    Description:   
 *    Arguments:		None  
 *    Return Value:  None
 *                                                                                                   
 ******************************************************************************/
void MESCAN_SetData32(uCAN1_MSG *CanMsg, MC_Data32 DefData32, uint32_t Data32);

/******************************************************************************
 *                                                                             
 *    Function:		
 *    Description:   
 *    Arguments:		None  
 *    Return Value:  None
 *                                                                                                   
 ******************************************************************************/
uint32_t MESCAN_GetData32(uCAN1_MSG *CanMsg, MC_Data32 DefData32);

/******************************************************************************
 *                                                                             
 *    Function:		
 *    Description:   
 *    Arguments:		None  
 *    Return Value:  None
 *                                                                                                   
 ******************************************************************************/
void MESCAN_SetDataFloat32(uCAN1_MSG *CanMsg, MC_Datafloat32 DefDataFloat32, float ValFloat);

/******************************************************************************
 *                                                                             
 *    Function:		
 *    Description:   
 *    Arguments:		None  
 *    Return Value:  None
 *                                                                                                   
 ******************************************************************************/
float MESCAN_GetDataFloat32(uCAN1_MSG *CanMsg, MC_Datafloat32 DefDataFloat32);

/******************************************************************************
 *                                                                             
 *    Function:		
 *    Description:   
 *    Arguments:		None  
 *    Return Value:  None
 *                                                                                                   
 ******************************************************************************/
void MESCAN_InitAndRAZ_Alldatas(uCAN1_MSG * MesCAN);


/******************************************************************************
 *                                                                             
 *    Function:		
 *    Description:   
 *    Arguments:		None  
 *    Return Value:  None
 *                                                                                                   
 ******************************************************************************/
void MESCAN_DupliqueMessageWithDLC(uCAN1_MSG * SrcMesCAN, uCAN1_MSG * DestMesCAN);


/******************************************************************************
 *                                                                             
 *    Function:		
 *    Description:   
 *    Arguments:		None  
 *    Return Value:  None
 *                                                                                                   
 ******************************************************************************/
void MESCAN_DupliqueMessageSaufDLC(uCAN1_MSG * SrcMesCAN, uCAN1_MSG * DestMesCAN);



/******************************************************************************
 *                                                                             
 *    Function:		
 *    Description:   
 *    Arguments:		None  
 *    Return Value:  None
 *                                                                                                   
 ******************************************************************************/
bool MESCAN_isDataTrame(uCAN1_MSG * MesCAN);



/*  Exemple d'utilisation de la FIFO.
 * On déclare une variable type FILE "maFIFO_essai": 
 *      iFILE_MesCAN maFIFO_essai;
 * 
 * Il faut l'initialiser:
 *      MESCAN_InitFIFO(&maFIFO_essai);
 * 
 * Pour enfiler les messages:
 *      MESCAN_enfiler(&maFIFO_essai, msgReceiveFIFO); //Avec par exemple msgReceiveFIFO
 *      comme message CAN reçu.
 * 
 * Avant de défiler, il faut s'assurer que la file n'est pas vide: Exemple
 *         if (! MESCAN_isFileVide(&maFIFO_essai)) {
            DesabledInterrupt();
            MESCAN_defiler(&maFIFO_essai, &msgCAN_essai);
            EnabledInterrupt();
        }
 * On a récupéré un message CAN nommé "msgCAN_essai" de la file
 */

/******************************************************************************
 *                                                                             
 *    Function:	void MESCAN_InitFIFO (iFILE_MesCAN *F);	
 *    Description:   Initialisation FILE
 *    Arguments:	 Nom de la file à initialiser.  
 *    Return Value:  None
 *                                                                                                   
 ******************************************************************************/
void MESCAN_InitFIFO (iFILE_MesCAN *F);


/******************************************************************************
 *                                                                             
 *    Function:	int MESCAN_isFileVide(iFILE_MesCAN *F);	
 *    Description:   
 *    Arguments:		None  
 *    Return Value:  None
 *                                                                                                   
 ******************************************************************************/
int MESCAN_isFileVide(iFILE_MesCAN *F);


/******************************************************************************
 *                                                                             
 *    Function:bool MESCAN_enfiler(iFILE_MesCAN *F, uCAN1_MSG myReceiveMesCAN);		
 *    Description:   
 *    Arguments:		Nom de la file
 *                      Nom du message CAN à enfiler  
 *    Return Value:     true, Operation OK
 *                      false quand on a atteint la taille maximum de la file, donc
 *                      le message CAN n'est pas enfilé.
 *                                                                                                   
 ******************************************************************************/
bool MESCAN_enfiler(iFILE_MesCAN *F, uCAN1_MSG myReceiveMesCAN);


/******************************************************************************
 *                                                                             
 *    Function:bool MESCAN_defiler(iFILE_MesCAN *F, uCAN1_MSG *myDefileMesCAN);		
 *    Description:   
 *    Arguments:		Nom de la file
 *                      Nom du message CAN à défiler  
 *    Return Value:     true, Operation OK
 *                      false quand il n'y a plus rien à défiler
 *                                                                                                   
 ******************************************************************************/
bool MESCAN_defiler(iFILE_MesCAN *F, uCAN1_MSG *myDefileMesCAN);






#endif	/* UTILITAIRECAN_H */


/**
 End of File
 */

