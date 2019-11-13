/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */
#ifndef LOCO_MAIN_PARAMS_H
#define	LOCO_MAIN_PARAMS_H

#define MAX_CONSIGNE_VITESSE_AUTORISEE  0x32


//Prediviseur de tension par 10 pour lecture tension de batterie
//Ex codage: 0x0C10 --> 0x0C:12V et 0x10: 0.16V soit 12.16V
#define V_BATTERIE_FAIBLE               0x0C10  // soit 12.16V
#define V_BATTERIE_TROP_FAIBLE          0x0B32 // soit 11,5V pour essai alim12V
//#define V_BATTERIE_TROP_FAIBLE          0x0B5A  // soit 11.9V

#define VMAX_RAILS  0x1700  //Codage tension volts en Hexa reste en hexa
//Ex si VMAX_RAILS = 0x1700 -->  = 23V  
//NB: La valeur réelle appliquée aux rails est :
//  Cette tension auquelle il faut ajouter 2x 0.8V (seuil du pont redresseur)
//  Soit Vrails réel = 23V + 1.6V = 24.6V

#define COEFF_MULTIPLICATEUR_WHEN_POWER_ON_RAIL     2
#define MAXTIMEOUT4LOCO_OFF (long)3541 * (long)240
//3541 x 16.944ms = 60s ou 1 minute quand incrément de 1 
//C'est à dire quand alimenté par les rails
//On multiplie par le nombre de minutes désirées
//Sinon c'est 60s divisé par "COEFF_MULTIPLICATEUR_WHEN_POWER_ON_RAIL"

#define CONSIGNE_VITESSE_MODE_MANU      0x10

#define MAX_CPT_REBOURS_LOCO_OFF        1770    ///1770*17ms~=30 secondes

#define PAS_ROUE_CODEUSE 0.016944 // en cm
//Parametres moteur CC
#define tau 0.33
#define k 1.41
#define dt 0.017
#define n 2.0
#define alphamin 30 

//Correcteur PI du moteur
#define KI_USINE    (n/k)*(1/tau)*dt
#define KP_USINE    (n/k)





#endif	/* LOCO_MAIN_PARAMS_H */

