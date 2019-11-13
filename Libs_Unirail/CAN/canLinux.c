#include "canLinux.h"

int canLinux_Init (char *portName)
{
	int s;
	struct sockaddr_can addr;
	struct ifreq ifr;
	char *ifname = portName;
	if((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0)
	{
		perror("Error while opening socket");
	}
	strcpy(ifr.ifr_name, ifname);
	ioctl(s, SIOCGIFINDEX, &ifr);
	addr.can_family  = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;
	#ifdef VERBOSE
		printf("%s at index %d\n", ifname, ifr.ifr_ifindex);
	#endif
	if(bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("Error in socket bind");
	}
	return s;
}


bool ECAN1_transmit(int portCan, CANLINUX_TX_PRIOIRTY priority, uCAN1_MSG *sendCanMsg) 
{
	int nbytes;
	bool messageSent = false;
	struct can_frame frameT;
	
	if (CAN1_MSG_RTR == sendCanMsg->frame.msgtype)
	frameT.can_id = sendCanMsg->frame.id | CAN_RTR_FLAG ;
	else
	frameT.can_id = sendCanMsg->frame.id;
	
	frameT.can_dlc = sendCanMsg->frame.dlc;
	frameT.data[0] = sendCanMsg->frame.data0;
	frameT.data[1] = sendCanMsg->frame.data1;
	frameT.data[2] = sendCanMsg->frame.data2;
	frameT.data[3] = sendCanMsg->frame.data3;
	frameT.data[4] = sendCanMsg->frame.data4;
	frameT.data[5] = sendCanMsg->frame.data5;
	frameT.data[6] = sendCanMsg->frame.data6;
	frameT.data[7] = sendCanMsg->frame.data7;
	nbytes = write(portCan, &frameT, sizeof(struct can_frame));
	if (nbytes == sizeof(struct can_frame))
		messageSent = true;
	return messageSent;
}

bool ECAN1_receive(int portCan, uCAN1_MSG *recCanMsg) 
{
	
	bool messageReceived = false;
	struct can_frame frameR;
	
	int nbytes = read(portCan,&frameR,sizeof(struct can_frame));
	if (nbytes >= sizeof(struct can_frame))
	{
		if (frameR.can_id & CAN_RTR_FLAG)
			recCanMsg->frame.msgtype = CAN1_MSG_RTR;
		else
		recCanMsg->frame.msgtype = CAN1_MSG_DATA;
		#ifdef VERBOSE
			printf("msgtype %i\n", recCanMsg->frame.msgtype);
		#endif
		
		recCanMsg->frame.id = frameR.can_id & 0x7FF; /// Standard
		recCanMsg->frame.dlc =  frameR.can_dlc;
		recCanMsg->frame.data0 = frameR.data[0];
		recCanMsg->frame.data1 = frameR.data[1];
		recCanMsg->frame.data2 = frameR.data[2];
		recCanMsg->frame.data3 = frameR.data[3];
		recCanMsg->frame.data4 = frameR.data[4];
		recCanMsg->frame.data5 = frameR.data[5];
		recCanMsg->frame.data6 = frameR.data[6];
		recCanMsg->frame.data7 = frameR.data[7];
		messageReceived=true;
	}
	return (messageReceived);
}


short ECAN1_reconstructMessage(uCAN1_MSG *recCanMsg, char* destinationArray, short startIDFrame, short messageLength) 
{
	short messageCompleted = 0;
	static short flagReceptions = 0, checksum=0, receivedChecksum = 0;
	unsigned short  maskAllReceived = 0, nbOfMessages=messageLength>>3; 
	int i, start, finish;
	if (messageLength%8)
	nbOfMessages++;
	for (i=0; i<nbOfMessages; i++)
	maskAllReceived|=(1<<i);
	if ((recCanMsg->frame.id > (startIDFrame+15)) || (recCanMsg->frame.id < startIDFrame) )		//message d'ailleurs
	{
		printf("Error: frame ID nb %X out of boundaries", recCanMsg->frame.id);
		return(-2);
	}
	if (recCanMsg->frame.id == startIDFrame )		//premiere trame CAN
	{
		checksum = 0;
		receivedChecksum = recCanMsg->frame.data1;
		for (i=0; i<recCanMsg->frame.dlc; i++)
		{
			checksum+= recCanMsg->array[i+9];
		}
		return(0);
	}
	start = (recCanMsg->frame.id - startIDFrame - 1)<<3;
	finish = start + recCanMsg->frame.dlc;
	if ( finish > messageLength)		//message trop long
	{
		printf("Error: message longer than expected");
		return(-2);
	}
	
	if (flagReceptions >>(recCanMsg->frame.id - startIDFrame - 1) & (1 == 1))		//message deja re�u
	{
		printf("Error: message nb %X already received", recCanMsg->frame.id);
		return(-1);
	}
	for (i=0; i<recCanMsg->frame.dlc; i++)
	{
		destinationArray[i+ start] = recCanMsg->array[i+7];
		checksum+= recCanMsg->array[i+7];
	}
	flagReceptions = flagReceptions | (1<<(recCanMsg->frame.id - startIDFrame - 1));
	if ((flagReceptions & maskAllReceived) == maskAllReceived) //Tout recu
	{
		if (checksum == receivedChecksum)
		{
			messageCompleted = 1;
			flagReceptions =0;
			receivedChecksum = 0;
		}
		else
		{
			printf("Error: checksum incorrect");
			return(-1);
		}
	}
	
	return (messageCompleted);
}

bool ECAN1_sliceMessage(uCAN1_MSG *sendCanMsg, char* headerArray, char* dataArray, short startIDFrame, short messageLength) 
{
	bool messageCompleted = false;
	static short compteEnvois = 0;
	unsigned short checksum, nbOfMessages=messageLength>>3; 
	int i, start, finish;
	if (messageLength%8)
		nbOfMessages++;
	
	sendCanMsg->frame.id = startIDFrame + compteEnvois;
	sendCanMsg->frame.msgtype = CAN1_MSG_DATA;
	sendCanMsg->frame.dlc = 8;  //modifie apres si besoin
	
	if (compteEnvois ==0)                       //construction de l'entete
	{
		checksum=0;                              //attention aux overflows
		for (i=0; i<6; i++)
		{
			checksum += headerArray[i];
			sendCanMsg->array[i+9] = headerArray[i];
		}
		for (i=0; i<messageLength; i++)
		checksum += dataArray[i];
		sendCanMsg->frame.data0 = messageLength;
		sendCanMsg->frame.data1 = checksum&0xFF;
		compteEnvois++;
		
	}
	else                                        //trames avec le message
	{
		start = (compteEnvois-1) <<3;
		compteEnvois++;
		finish = start + 8;
		if ( finish > messageLength || compteEnvois == (nbOfMessages+1))
		{
			finish = messageLength;
			sendCanMsg->frame.dlc = finish - start;
			messageCompleted = true;
			compteEnvois = 0;
		}
		for (i=start; i<finish; i++)
		{
			sendCanMsg->array[i+7-start] = dataArray[i];
		}
	}
	return (messageCompleted);
}


void canLinux_InitFilter (int portCan, struct can_filter* rfilter, int longueur)
{
	setsockopt(portCan, SOL_CAN_RAW, CAN_RAW_FILTER, rfilter, longueur); 
}

