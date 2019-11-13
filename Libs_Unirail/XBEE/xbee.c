#include "xbee.h"
#include "../CAN/MESCAN1_VarTrain.h"
	
#include <stdio.h>///\todo attention aux printf...

extern uCAN1_MSG mc_BASE4PAYLOAD2CAN;
extern iFILE_MesCAN CAN1_FIFO_forSendMesCAN;

#define OFFSET_ARRAY_DATA0      7  


#if defined (MC802)

void FormatAndSend_RF_PacketToRPIviaCAN(xBeeReceivePacket* donnees) {
    uint8_t uc_LenMes, uc_CustomCKS;
    uint16_t temp_uint16;
    uint8_t temp_uint8;
    uint16_t ui_TempDLC_TrameCAN2SendPayload = 0;
    uint16_t ui_IndiceDataToSendFromTabPayload = 0;
    uint8_t uc_CKS_SubsetDatas_XBeeToRpi = 0;
    int i;

    mc_BASE4PAYLOAD2CAN.frame.id = MC_ID_MESSAGE_GSM_RECEIVED;
    mc_BASE4PAYLOAD2CAN.frame.dlc = 8;

    mc_BASE4PAYLOAD2CAN.frame.data2 = donnees->AdrSource;
    mc_BASE4PAYLOAD2CAN.frame.data3 = donnees->AdrSource >> 8;

    mc_BASE4PAYLOAD2CAN.frame.data4 = donnees->RSSI;
    mc_BASE4PAYLOAD2CAN.frame.data5 = 0;
    mc_BASE4PAYLOAD2CAN.frame.data6 = 0; //Datas 6 et 7 trame CAN
    mc_BASE4PAYLOAD2CAN.frame.data7 = 0;

    //					//Decomposition "brute" en trame CAN
    //					//Pas de traitement des datas
    uc_LenMes = donnees->LenPacket - 5; //Nb de datas restantes � transmettre

    mc_BASE4PAYLOAD2CAN.frame.data0 = uc_LenMes;

    //Calcul du uc_CustomCKS
    temp_uint16 = donnees->AdrSource;
    uc_CustomCKS = donnees->RSSI;
    uc_CustomCKS = uc_CustomCKS + (temp_uint16 >> 8);
    uc_CustomCKS = uc_CustomCKS + temp_uint16;

    for (i = 0; i < uc_LenMes; i++)
        uc_CustomCKS = uc_CustomCKS + donnees->bReceivePacketData[i];

    mc_BASE4PAYLOAD2CAN.frame.data1 = uc_CustomCKS;
    DesabledInterrupt();
    MESCAN_enfiler(&CAN1_FIFO_forSendMesCAN, mc_BASE4PAYLOAD2CAN);
    EnabledInterrupt();

    //Pour envoi des trames suivantes
    mc_BASE4PAYLOAD2CAN.frame.id = mc_BASE4PAYLOAD2CAN.frame.id + 1;

    ui_TempDLC_TrameCAN2SendPayload = 0;
    ui_IndiceDataToSendFromTabPayload = 0;

    while (ui_IndiceDataToSendFromTabPayload < uc_LenMes) {

        temp_uint8 = donnees->bReceivePacketData[ui_IndiceDataToSendFromTabPayload];
        mc_BASE4PAYLOAD2CAN.array[ui_TempDLC_TrameCAN2SendPayload + OFFSET_ARRAY_DATA0] = temp_uint8;

        uc_CKS_SubsetDatas_XBeeToRpi = uc_CKS_SubsetDatas_XBeeToRpi + temp_uint8;
        ui_IndiceDataToSendFromTabPayload++;

        if (ui_TempDLC_TrameCAN2SendPayload == 7) {
            //Envoi trame CAN
            mc_BASE4PAYLOAD2CAN.frame.dlc++;
            DesabledInterrupt();
            MESCAN_enfiler(&CAN1_FIFO_forSendMesCAN, mc_BASE4PAYLOAD2CAN);
            EnabledInterrupt();

            mc_BASE4PAYLOAD2CAN.frame.id = mc_BASE4PAYLOAD2CAN.frame.id + 1;
            ui_TempDLC_TrameCAN2SendPayload = 0;
            mc_BASE4PAYLOAD2CAN.frame.dlc = ui_TempDLC_TrameCAN2SendPayload;
        } else {
            ui_TempDLC_TrameCAN2SendPayload++;
            mc_BASE4PAYLOAD2CAN.frame.dlc = ui_TempDLC_TrameCAN2SendPayload;

        }
    }
    //Envoi la derniere trame CAN
    if (ui_TempDLC_TrameCAN2SendPayload) {
        DesabledInterrupt();
        MESCAN_enfiler(&CAN1_FIFO_forSendMesCAN, mc_BASE4PAYLOAD2CAN);
        EnabledInterrupt();
    }
}
#endif
/**Format de la trame (xbee documentation page 86+):<BR>
    Delimiteur ->0x7E<BR>
    Longueur de la \b trame (longueur du message +5) 2 octets<BR>
    Mode d'operation API sans echappements (0x01)<BR>
    ID de la trame pour suivi d'ACK<BR>
    Adresse de destination, 2 octets<BR>
    Options<BR>
    donnees<BR>
    checksum
    \todo faire une lib pour config, envoi de messages, monitoring, etc.
    \todo verifier si gi_FlagReceptionCompletePayload sert a qqch
    \todo elimine de la fonction: 
    -	short si_FlagReceptionCompleteSpecifsTrameCAN= 0 et son seul usage: 
    si_FlagReceptionCompleteSpecifsTrameCAN = 0
    - short si_FlagReceivePayloadXBeeEnCours = 0 et son usage: 
    si_FlagReceivePayloadXBeeEnCours = 0;
    si_FlagReceivePayloadXBeeEnCours = 1;
	
	
	
 */
short PortXbee_receptionOctet(xBeeReceivePacket* donnees, int serial) {
    unsigned char CharRecu;
    static short si_Etat_ISR_UART = WAIT_START_DELIMITER_FRAME_XB;
    static short si_NbCharData;
    static short si_IndiceTabReceivePacket; //compteur d'indice du tableau de donnees
    static unsigned char suc_cks_calcule; //Accumulateur pour calculer le checksum

#if defined (MC802)
    CharRecu = U2RXREG;

    if (IFS1bits.T4IF) //Erreut TimeOUT donc Reset Diagramme etat
    {
        T4CONbits.TON = 0; //	Stop TimeOUT
        IFS1bits.T4IF = 0;
        TMR4 = 0;
        si_Etat_ISR_UART = WAIT_START_DELIMITER_FRAME_XB;
    }
#else
    CharRecu = serialGetchar(serial);
#endif


    //Pour Debug
    //MESCAN_SetData8(&mc_GSM_statusRun, cdmc_GSM_var1Debug, si_Etat_ISR_UART);


    switch (si_Etat_ISR_UART) {
        case WAIT_START_DELIMITER_FRAME_XB:
            suc_cks_calcule = 0;
            si_NbCharData = 0;
            if (CharRecu == START_DELIMITER_FRAME_XB) {
#if defined (MC802)
                TMR4 = 0;
                IFS1bits.T4IF = 0;
                Nop();
    //            T4CONbits.TON = 1; //	Start TimeOU
#endif
                si_Etat_ISR_UART = RX_MSB_LEN_MESSAGE;
            }
            return 0;

        case RX_MSB_LEN_MESSAGE:
            donnees->LenPacket = (unsigned int) (CharRecu << 8);
            si_Etat_ISR_UART = RX_LSB_LEN_MESSAGE;
            return 0;

        case RX_LSB_LEN_MESSAGE:
            donnees->LenPacket = donnees->LenPacket + CharRecu;
            si_Etat_ISR_UART = RX_FRAME_TYPE;
            return 0;

        case RX_FRAME_TYPE:
            donnees->OptionFrameType = CharRecu;
            suc_cks_calcule += CharRecu;
            if (CharRecu == FRAME_TYPE_RX16_BITS_ADR) {
                si_Etat_ISR_UART = RX_MSB_SOURCE_ADR;
                return 0;
            } else if (CharRecu == TX_STATUS_FRAME_ACK_RF) {
                si_Etat_ISR_UART = RX_ACKXBEE_ID_ACK;
                return 0;
            } else if (CharRecu == AT_COMMAND_RESPONSE) {
                si_Etat_ISR_UART = RX_ATCOMMAND_ID_ATCOMMAND;
                return 0;
            } else {
                si_Etat_ISR_UART = WAIT_START_DELIMITER_FRAME_XB;
                return -2;
            }

        case RX_MSB_SOURCE_ADR:
            donnees->AdrSource = (unsigned int) (CharRecu << 8);
            suc_cks_calcule += CharRecu;
            si_Etat_ISR_UART = RX_LSB_SOURCE_ADR;
            return 0;

        case RX_LSB_SOURCE_ADR:
            donnees->AdrSource += CharRecu;
            suc_cks_calcule += CharRecu;
            si_Etat_ISR_UART = RX_RSSI;
            return 0;

        case RX_RSSI:
            donnees->RSSI = CharRecu;
            suc_cks_calcule += CharRecu;
            si_Etat_ISR_UART = RX_OPTIONS;
            return 0;

        case RX_OPTIONS:
            donnees->Options = CharRecu;
            suc_cks_calcule += CharRecu;
            si_IndiceTabReceivePacket = 0;
            si_Etat_ISR_UART = RX_DATA_TYPE_TRAME_RF;
            return 0;

        case RX_DATA_TYPE_TRAME_RF:
            //Dans le tableau de datas, La premiere data d'indice ZERO indique
            //Le type de trame datas RF que l'on a recu (TROIS types possibles)

            //  0x3E: Reception d'un codage de trame CAN qu'il faudra envoyer sur le bus
            //  0x3F: Reception d'un codage de trame CAN qu'il faudra interpreter
            //  Autres: Correspond a un numero de SUBSET GSM-R

            donnees->bReceivePacketData[si_IndiceTabReceivePacket] = CharRecu;
            si_IndiceTabReceivePacket++;
            suc_cks_calcule += CharRecu;
            si_Etat_ISR_UART = RX_DATAS_MESSAGE;

            return 0;


        case RX_DATAS_MESSAGE:
            //Reception des datas xbee (SUBMIT GSM_R ou FRAMEs CAN)
            donnees->bReceivePacketData[si_IndiceTabReceivePacket] = CharRecu;
            si_IndiceTabReceivePacket++;
            suc_cks_calcule += CharRecu;
            if (si_IndiceTabReceivePacket == (donnees->LenPacket - 5))
                si_Etat_ISR_UART = RX_CKS;
            return 0;

        case RX_CKS:
            // Reception du checksum et verification
            donnees->CKS = CharRecu;
            suc_cks_calcule = 0xFF - suc_cks_calcule;

            if (suc_cks_calcule == CharRecu) {
                donnees->StatusCom = RAS;
                //			gi_FlagReceptionCompletePayload = 1;


                si_Etat_ISR_UART = WAIT_START_DELIMITER_FRAME_XB;
                return 1;
            } else {
                donnees->StatusCom = ERREUR;
                si_Etat_ISR_UART = WAIT_START_DELIMITER_FRAME_XB;
                return -1;
                //			gi_FlagAllumerLedRougeXbee = 1;
            }
            break;
            //Traitement pour reception Frame Acknoledge RF Xbee
        case RX_ACKXBEE_ID_ACK:
            donnees->FrameId_IdentifiUARTdataFrameBeingReported = CharRecu;
            suc_cks_calcule += CharRecu;
            si_Etat_ISR_UART = RX_ACKXBEE_STATE;
            return 0;

        case RX_ACKXBEE_STATE:
            donnees->ReponseACK_EtatLowSiGoodACK = CharRecu;
            suc_cks_calcule += CharRecu;
            si_Etat_ISR_UART = RX_ACKXBEE_CKS;
            return 0;

        case RX_ACKXBEE_CKS:
            donnees->CKS = CharRecu;
            suc_cks_calcule = 0xFF - suc_cks_calcule;
            si_Etat_ISR_UART = WAIT_START_DELIMITER_FRAME_XB;
            
            if (suc_cks_calcule == CharRecu) {
                donnees->StatusCom = RAS;
                //			gi_FlagReceptionCompletePayload = 1;

                //			if ( Jumper1 )
                //				giFlagAllumerLedVerteXbee = 1;

                return 1;

            } else {


                donnees->StatusCom = ERREUR;
                //			gi_FlagAllumerLedRougeXbee = 1;
                return -1;
                //			gi_FlagReceptionCompletePayload = 1;
            }
            break;

        case RX_ATCOMMAND_ID_ATCOMMAND:
            donnees->FrameId_IdentifiUARTdataFrameBeingReported = CharRecu;
            suc_cks_calcule += CharRecu;
            si_Etat_ISR_UART = RX_ATCOMMAND_1;
            return 0;

        case RX_ATCOMMAND_1:
            suc_cks_calcule += CharRecu;
            si_Etat_ISR_UART = RX_ATCOMMAND_2;
            return 0;

        case RX_ATCOMMAND_2:
            suc_cks_calcule += CharRecu;
            si_Etat_ISR_UART = RX_ATCOMMAND_STATUS;
            return 0;

        case RX_ATCOMMAND_STATUS:
            donnees->ReponseACK_EtatLowSiGoodACK = CharRecu;
            donnees->CKS = CharRecu;
            if (donnees->LenPacket > 5)
                si_Etat_ISR_UART = RX_ATCOMMAND_DATAS;
            else
                si_Etat_ISR_UART = RX_CKS;

            return 0;

        case RX_ATCOMMAND_DATAS:
            //Reception des datas xbee
            donnees->bReceivePacketData[si_IndiceTabReceivePacket] = CharRecu;
            si_IndiceTabReceivePacket++;
            suc_cks_calcule += CharRecu;
            if (si_IndiceTabReceivePacket == (donnees->LenPacket - 4))
                si_Etat_ISR_UART = RX_CKS;
            return 0;


        default:
            donnees->StatusCom = 2;
            return -2;
    }
}

/**Format de la trame (xbee documentation page 86+):<BR>
    Delimiteur ->0x7E<BR>
    Longueur de la \b trame (longueur du message +5) 2 octets<BR>
    Mode d'operation API sans echappements (0x01)<BR>
    ID de la trame pour suivi d'ACK<BR>
    Adresse de destination, 2 octets<BR>
    Options<BR>
    donnees<BR>
    checksum
    \todo faire une lib pour config, envoi de messages, monitoring, etc.
 */
short PortXbee_envoyer(char dest_addr[2], char *donnees, int nb, int serial, short type_trame, unsigned char ID_message, short options) {
    short retour = -1;
    unsigned char checksum = 0;
    int i, pos, nbTotal;
    unsigned char trame[128];

    //    memset(trame, 0, 128);

    // page 63
    trame[0] = 0x7E;
    trame[1] = ((nb + 5) >> 8) & 0xFF;
    trame[2] = ((nb + 5)) & 0xFF;
    trame[3] = type_trame & 0xFF;
    trame[4] = ID_message & 0xFF;
    trame[5] = dest_addr[0];
    trame[6] = dest_addr[1];
    if (type_trame == TX_REQUEST_16BITS_ADR) {
        trame[7] = options & 0xFF;
        nbTotal = 8 + nb;
    } else {
        nbTotal = 7 + nb;
        trame[1] = ((nb + 4) >> 8) & 0xFF;
        trame[2] = ((nb + 4)) & 0xFF;
    }


    if (type_trame == TX_REQUEST_16BITS_ADR) {
        for (i = 0; i < nb; i++) {
            trame[8 + i] = donnees[i];
        }
    } else {
        for (i = 0; i < nb; i++) {
            trame[7 + i] = donnees[i];
        }
    }
    // page 59
    checksum = 0;
    for (pos = 3; pos < nbTotal; pos++) {
        checksum += trame[pos];
    }
    trame[nbTotal++] = 0xFF - checksum;

    // cf. man 2 write
    //serialPuts(fd, trame);

    //debug : affichage
    //fprintf(stderr, "-> envoyer (%d/%d) : ", n, retour);
    //fprintf(stderr, "trame : ");

    for (i = 0; i < nbTotal; i++) {

        //    printf("%X ",trame[i] );
        //fprintf(stderr, "0x%02X ", *(trame+i));
        ///\todo A verifier le bon fonctionnement
        //       printf("%X ", *(trame+i));
#if defined (MC802)
        uart2_write(*(trame + i));
#else
        serialPutchar(serial, *(trame + i));
#endif
    }
    //fprintf(stderr, "\n");
    //fprintf(stderr, "%s\n", trame);
    //    printf("Trame envoyÃ©e\n");

    return retour;
} 