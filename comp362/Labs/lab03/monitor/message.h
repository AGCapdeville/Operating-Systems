/**
 * Name: Adam Capdeville
 * Lab/task: Lab 3
 * Date: 02/14/2019 
**/


#ifndef _MESSG_H
#define _MESSG_H

#include <sys/types.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "stdbool.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define oops(ermsg,erno) {perror(ermsg); exit(erno); }

#define MONITOR_QUEUE "/MONITOR" // message queue name must start with '/'
#define NODE_NAME_PREFIX "NODE_" 

#define MAX_MSG_SIZE 64
#define MAX_NODES 256
#define MSG_TYPE 1


typedef struct messg {
	bool stable;
	int nodeId;
	float temperature;
} MESSG;


typedef struct temperature {
    mqd_t msqid;
    float previousTemperature;
} TEMPERATURE;

struct mq_attr makeAttribs()
{
	struct mq_attr attribs = {
		.mq_flags = 0,
		.mq_maxmsg = 10,
		.mq_msgsize = MAX_MSG_SIZE,
		.mq_curmsgs = 0
	};
	return attribs;
}

mqd_t openQueue(char * queueName) 
{
	//printf("Opening %s\n", queueName);
	struct mq_attr attr = makeAttribs();
	mqd_t msqid = mq_open(queueName, O_RDWR | O_CREAT, S_IWUSR | S_IRUSR, &attr );
	if ( msqid < 0)
    	oops("FUNC: openQ :Error opening a queue", errno);
	//printf("Opening \"%s\" MQID: %d\n", queueName, msqid);
	return msqid;
}

mqd_t openMonitorQueue()
{
	return openQueue(MONITOR_QUEUE);
}

mqd_t openNodeQueue(int nodeNumber)
{
	char nodeQueue[MAX_MSG_SIZE];
	sprintf(nodeQueue, "/" NODE_NAME_PREFIX "%d", nodeNumber);
	return openQueue(nodeQueue);
}

void sendMsg( mqd_t msqid, MESSG* mssg ){

	//msqid = openNodeQueue(mssg->nodeId);
	if (mq_send(msqid,((char*)mssg), sizeof(MESSG), (unsigned int)MSG_TYPE) < 0)
	{
		//printf("sendMsg ID: %d \n", mssg->nodeId);
    	oops("sendMsg: Error sending", errno);
	}
	//printf("SEND: mqid:%d nodeID:%d, tmp:%f\n", msqid, mssg->nodeId, mssg->temperature );
}


void rcvdMsg( mqd_t msqid, MESSG* mssg )
{
	if (mq_receive(msqid, (char*)(mssg), sizeof(MESSG)*30, NULL) < 0){
		//printf("rcvdMsg ID: %d \n", mssg->nodeId);
		oops("Wait for Monitor: Error receiving data.", errno);
	}
	//printf("RECV: node: %d   temp:%f\n", mssg->nodeId, mssg->temperature);
}


bool checkTemp(float rcvdTemp, float prvTemp, float epsilon){
	return abs(rcvdTemp-prvTemp) < epsilon;
}




#endif
