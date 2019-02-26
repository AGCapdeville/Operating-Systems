/**
 * Name: Adam Capdeville
 * Lab/task: Lab 3
 * Date: 02/14/2019 
**/

#include "message.h"



int main(int argc, char** argv)
{
	if (argc != 3)
		oops("Incorrect number of arguments", -1);
		
	int nodeNumber = atoi(argv[1]);
	char nodeName[256] = "";
	sprintf(nodeName, "/" NODE_NAME_PREFIX "%d", atoi(argv[1]));
	//printf("Node Spawned with name: %s\n", nodeName);

	MESSG msg_rcvd;
	msg_rcvd.stable = false;
	
	MESSG msg_send;
	msg_send.stable = false;
	msg_send.nodeId = nodeNumber;
	msg_send.temperature = atof(argv[2]);
	
	float new_node_temp, previous_node_temp, new_integrated_temp = 0.0;

	mqd_t msqid = openMonitorQueue();
	mqd_t nmsqid = openNodeQueue(nodeNumber);

	while( !msg_rcvd.stable ) {
		//printf(" Node: %d Temp: %f \n",msg_rcvd->);    // TODO
		sendMsg(msqid,&msg_send);

		rcvdMsg(nmsqid, &msg_rcvd);
		//printf(" \n Node Temp rcvd: %f\n", msg_rcvd.temperature );

		//	Calc new_integrated_temp
		new_integrated_temp = msg_rcvd.temperature;
		new_node_temp = (previous_node_temp * 3 + 2 * new_integrated_temp) / 5;
		previous_node_temp = new_node_temp;
		
		msg_send.nodeId = msg_rcvd.nodeId;
		msg_send.temperature = msg_rcvd.temperature;
		//	Now send back new_node_temp ...
		msg_send.temperature = new_node_temp;
	}

	printf("\n NODE %d TERMINATING...\n",msg_rcvd.nodeId);
}
