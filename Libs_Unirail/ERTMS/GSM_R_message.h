#ifndef GSM_R_MESSAGE_H
	#define	GSM_R_MESSAGE_H
	
	#include "GSM_R_packet.h"
	
	///GSMR_CommunicationInitiationMessage: Demarrage des echanges
	/**Taille:8<BR>
		ID message:155<BR>
		Sens du message: Train to Track
	*/
	typedef struct 
	{
		const uint8_t nid_message;	///< = 155
		const uint16_t l_message;	///< = 8
		uint32_t t_train;
		uint8_t nid_engine;
	} GSMR_CommunicationInitiationMessage;
	
	///GSMR_RBCSystemVersionMessage:
	/**Taille:11<BR>
		ID message:32<BR>
		Sens du message: Track to Train
	*/
	typedef struct 
	{
		const uint8_t nid_message;	///< = 32
		const uint16_t l_message;	///< = 11
		uint32_t t_train;
		uint8_t m_ack;
		uint16_t nid_lrbg;
		uint8_t m_version;
	} GSMR_RBCSystemVersionMessage;
	
	///GSMR_SessionEstablishedMessage:
	/**Taille:8<BR>
		ID message:159<BR>
		Sens du message: Train to Track
	*/
	typedef struct 
	{
		const uint8_t nid_message;	///< = 159
		const uint16_t l_message;	///< = 8
		uint32_t t_train;
		uint8_t nid_engine;
	} GSMR_SessionEstablishedMessage;
	
	///GSMR_ValidatedTrainDataMessage:
	/**Taille:45-180<BR>
		ID message:129<BR>
		Sens du message: Train to Track
	*/
	typedef struct 
	{
		const uint8_t nid_message;	///< = 129
		uint16_t l_message;
		uint32_t t_train;
		uint8_t nid_engine;
		union 
		{
			GSMR_PositionReportPacket packetNb0;
			GSMR_PositionReportPacketTwoBaliseGroups packetNb1;
		};
		GSMR_ValidatedTrainDataPacket packetNb11;
	} GSMR_ValidatedTrainDataMessage;
	
	///GSMR_ACKTrainDataMessage:
	/**Taille:16<BR>
		ID message:8<BR>
		Sens du message: Track to Train
	*/
	typedef struct 
	{
		const uint8_t nid_message;	///< = 8
		const uint16_t l_message;	///< = 16
		uint32_t t_train;
		uint8_t m_ack;
		GSMR_nid_lrbg nid_lrbg;
		uint32_t t_trainMessageOrigin;
	} GSMR_ACKTrainDataMessage;
	
	///GSMR_MARequestMessage:
	/**Taille:33-37+nb9<BR>
		ID message:132<BR>
		Sens du message: Train to Track<BR>
		There are 5 reasons why a train may request a movement authority(q_marqstreason)<BR>
		1)	Start selected by driver<BR>
		2)	Time before reaching the perturbation location reached<BR>
		3)	Time before a section timer/LOA speed timer expires reached<BR>
		4)	Track description deleted<BR>
		5)	TAF up to level 2/3 transition location<BR>
		\todo Packet 9 is optional at the end of the message
	*/
	typedef struct 
	{
		const uint8_t nid_message;	///< = 132
		uint16_t l_message;
		uint32_t t_train;
		uint8_t nid_engine;
		uint8_t q_marqstreason;
		union 
		{
			GSMR_PositionReportPacket packetNb0;
			GSMR_PositionReportPacketTwoBaliseGroups packetNb1;
		};
	} GSMR_MARequestMessage;
	
	///GSMR_MovementAuthorityMessage:
	/**Taille:27-269+optionals<BR>
		ID message:3<BR>
		Sens du message: Track to Train<BR>
		\todo optional packets handling?
	*/
	typedef struct 
	{
		const uint8_t nid_message;	///< = 3
		uint16_t l_message;
		uint32_t t_train;
		uint8_t m_ack;
		GSMR_nid_lrbg nid_lrbg;
		GSMR_Level2_3MovementAuthorityPacket packetnb15;
	} GSMR_MovementAuthorityMessage;
	
	///GSMR_SRAuthorisationMessage:
	/**Taille:15+optionals<BR>
		ID message:2<BR>
		Sens du message: Track to Train<BR>
		\todo optional packets handling?
	*/
	typedef struct 
	{
		const uint8_t nid_message;	///< = 2
		uint16_t l_message;
		uint32_t t_train;
		uint8_t m_ack;
		GSMR_nid_lrbg nid_lrbg;
		uint8_t q_scale;
		uint16_t d_sr;
	} GSMR_SRAuthorisationMessage;
	
	///GSMR_Acknowledgment:
	/**Taille:12<BR>
		ID message:146<BR>
		Sens du message: Train to Track<BR>
	*/
	typedef struct 
	{
		const uint8_t nid_message;	///< = 146
		const uint16_t l_message;	///< = 12
		uint32_t t_train;
		uint8_t nid_engine;
		uint32_t t_trainMessageOrigin;
	} GSMR_Acknowledgment;
	
	///GSMR_EndOfMission:
	/**Taille:29-36<BR>
		ID message:150<BR>
		Sens du message: Train to Track<BR>
	*/
	typedef struct 
	{
		const uint8_t nid_message;	///< = 150
		uint16_t l_message;
		uint32_t t_train;
		uint8_t nid_engine;
		union 
		{
			GSMR_PositionReportPacket packetNb0;
			GSMR_PositionReportPacketTwoBaliseGroups packetNb1;
		};
	} GSMR_EndOfMission;
	
	///GSMR_AckTerminationCommunicationSession:
	/**Taille:12<BR>
		ID message:39<BR>
		Sens du message: Track to Train<BR>
		Acknowledgement of termination of a communication session
	*/
	typedef struct 
	{
		const uint8_t nid_message;	///< = 39
		uint16_t l_message;	///< = 12
		uint32_t t_train;
		const uint8_t m_ack;	/// = 0
		GSMR_nid_lrbg nid_lrbg;
	} GSMR_AckTerminationCommunicationSession;
	
#endif
