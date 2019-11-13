#ifndef GSM_R_PACKET_H
	#define	GSM_R_PACKET_H
	
	#include <stdint.h>
	/** Legende:
		A_         Acceleration<BR>
		D_         distance<BR>
		G_         Gradient<BR>
		L_         length<BR>
		M_         Miscellaneous<BR>
		N_         Number<BR>
		NC_        class number<BR>
		NID_       identity number<BR>
		Q_         Qualifier<BR>
		T_         time/date<BR>
		V_         Speed<BR>
		X_         Text<BR>
	*/
	///GSMR_nid_lrbg:
	/**Taille:4<BR>
		nid_lrbg: Identity of last relevant balise group = Country/region identity (NID_C, 10bits) + balise identity number of last relevant balise group (NID_BG, 14bits) 
		\todo: en tout c'est 24bits, peut etre compresse en cas de besoin a 3 octets
	*/
	typedef struct 
	{
		uint16_t nid_c;
		uint16_t nid_bg;
	} GSMR_nid_lrbg;
	
	///GSMR_engine_identifier: Variable intermediaire, non existant dans la doc originale.
	/**Taille:1-3<BR>
		engine_identifier: Elle existe car elle peut exister en plusieurs exemplaires, selon la valeur de n_iter immediatement superieure 
		\todo: la taille du packet envoye sera plus petite que celle-ci at a calculer avan chaque envoi, attention a cela!
		\todo nid_ctraction existe si m_voltage!=0
	*/
	typedef struct 
	{
		uint8_t m_voltage;
		uint16_t nid_ctraction;
	} GSMR_engine_identifier;
	
	///GSMR_PositionReportPacket: reports the train position and speed as well as some additional information (e.g. mode, level, etc.)
	/**Taille:21-24<BR>
		ID packet:0<BR>
		\todo l_traininit est optionnel selon la valeur de q_length
		\todo nid_ntc existe si m_level=NTC (1)
	*/
	typedef struct 
	{
		const uint8_t nid_packet;	///< = 0
		const uint16_t l_packet;	///< = 24
		uint8_t q_scale;
		GSMR_nid_lrbg nid_lrbg;
		uint16_t d_lrbg;
		uint8_t q_dirlrbg;
		uint8_t q_dlrbg;
		uint16_t l_doubtover;
		uint16_t l_doubtunder;
		uint8_t q_length;
		uint16_t l_traininit;
		uint8_t v_train;
		uint8_t q_dirtrain;
		uint8_t m_mode;
		uint8_t m_level;
		uint8_t nid_ntc;
	} GSMR_PositionReportPacket;
	
	///GSMR_PositionReportPacketTwoBaliseGroups: extension of the “standard position report “ packet 0.
	/**Taille:25-28<BR>
		ID packet:1<BR>
		It is used in case of single balise groups if the orientation of the LRBG is unknown but the on-board equipment is able to report a second balise group (the one detected before) to give a direction reference for the directional information in the position report.
		\todo l_traininit est optionnel selon la valeur de q_length
		\todo nid_ntc existe si m_level=NTC (1)
	*/
	typedef struct 
	{
		const uint8_t nid_packet;	///< = 1
		uint16_t l_packet;
		uint8_t q_scale;
		GSMR_nid_lrbg nid_lrbg;
		GSMR_nid_lrbg nid_prvlrbg;
		uint16_t d_lrbg;
		uint8_t q_dirlrbg;
		uint8_t q_dlrbg;
		uint16_t l_doubtover;
		uint16_t l_doubtunder;
		uint8_t q_length;
		uint16_t l_traininit;
		uint8_t v_train;
		uint8_t q_dirtrain;
		uint8_t m_mode;
		uint8_t m_level;
		uint8_t nid_ntc;
	} GSMR_PositionReportPacketTwoBaliseGroups;
	
	///GSMR_Level2_3TransitionInformationPacket: Identity of the level 2/3 transition balise group.
	/**Taille:7<BR>
		ID packet:9<BR>
		It is used in case of single balise groups if the orientation of the LRBG is unknown but the on-board equipment is able to report a second balise group (the one detected before) to give a direction reference for the directional information in the position report.
		\todo l_traininit est optionnel selon la valeur de q_length
		\todo nid_ntc existe si m_level=NTC (1)
	*/
	typedef struct 
	{
		const uint8_t nid_packet;	///< = 9
		const uint16_t l_packet;	///< = 7
		GSMR_nid_lrbg nid_lrbg;
	} GSMR_Level2_3TransitionInformationPacket;
	
	///GSMR_ValidatedTrainDataPacket: Validated train data.
	/**Taille:16-144<BR>
		ID packet:11<BR>
	*/
	typedef struct 
	{
		const uint8_t nid_packet;	///< = 11
		uint16_t l_packet;
		uint8_t nc_cdtrain;
		uint16_t nc_train;
		uint16_t l_train;
		uint8_t v_maxtrain;
		uint8_t m_loadinggauge;
		uint8_t m_axleloadcat;
		uint8_t m_airtight;
		uint16_t n_axle;
		uint8_t n_iter_engine;
		GSMR_engine_identifier engine_identifier[32];
		uint8_t n_iter_ntc;
		uint8_t nid_ntc[32];
	} GSMR_ValidatedTrainDataPacket;
	
	///GSMR_SectionDescription: Variable intermediaire. 
	/**Taille:3-7<BR>
		\todo t_sectiontimer et d_sectiontimerstoploc existent si q_sectiontimer=1
	*/
	typedef struct 
	{
		uint16_t l_section;
		uint8_t q_sectiontimer;
		uint16_t t_sectiontimer;
		uint16_t d_sectiontimerstoploc;
	} GSMR_SectionDescription;
	
	///GSMR_Level2_3MovementAuthorityPacket: Transmission of a movement authority for levels 2/3. 
	/**Taille:15-257<BR>
		ID packet:15<BR>
		\todo t_endtimer et d_endtimerstoploc existent si q_endtimer=1
		\todo d_dp et v_releasedp existent si q_dangerpoint=1
		\todo d_startol, t_ol et v_releaseol existent si q_overlap=1
	*/
	typedef struct 
	{
		const uint8_t nid_packet;	///< = 15
		uint8_t q_dir;
		uint16_t l_packet;
		uint8_t q_scale;
		uint8_t v_ema;
		uint16_t t_ema;
		uint8_t n_iter_section;
		GSMR_SectionDescription sectiondescription[32];
		GSMR_SectionDescription endsectiondescription;
		uint8_t q_endtimer;
		uint16_t t_endtimer;
		uint16_t d_endtimerstoploc;
		uint8_t q_dangerpoint;
		uint16_t d_dp;
		uint8_t v_releasedp;
		uint8_t q_overlap;
		uint16_t d_startol;
		uint16_t t_ol;
		uint16_t d_ol;
		uint8_t v_releaseol;
	} GSMR_Level2_3MovementAuthorityPacket;
	
#endif	