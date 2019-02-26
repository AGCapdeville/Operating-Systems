/**
 * Name: Adam Capdeville
 * Lab/task: Lab 3
 * Date: 02/14/2019 
**/

#include "message.h"

#define MONITOR_TEMP_ARG 1
#define NODE_COUNT_ARG 2
#define	EPSILON 0.005F

// example of evoc: 
// $ ./monitor 200 4 25 50 75 100

void closeQueue(char * queueName)
{
//	printf("Unlinking \"%s\"\n", queueName);
	mq_unlink(queueName);
}

void closeMonitorQueue()
{
	closeQueue(MONITOR_QUEUE);
}

void closeNodeQueues(int nodeCount)
{
	char nodeName[256] = "";
	for(int index = 0; index < nodeCount; index++) {
		sprintf(nodeName, "/" NODE_NAME_PREFIX "%d", index);
		closeQueue(nodeName);	
	}
}

int main( int argc, char** argv){
	if(argc < 3)
		oops("Error, not enough arguments", -1);

	int numberOfNodes = (int)strtol(argv[NODE_COUNT_ARG], NULL, 10);
	closeMonitorQueue();
	closeNodeQueues(numberOfNodes);

	float monitorTemp = strtof(argv[1],NULL);
	
	//MESSG
	MESSG msg_rcvd = {0, 0, 0};
	MESSG msg_send = {0, 0, 0};
	
	TEMPERATURE * nodeData = calloc(numberOfNodes, sizeof(TEMPERATURE));
	mqd_t msqid = openMonitorQueue();

    //	Loop for opening node Queues
	int pid;
    char nodeIdStr[MAX_NODES];
    for (int index = 0; index < numberOfNodes ; index++){
		nodeData[index].msqid = openNodeQueue(index);
		
    	pid = fork();
    	if(pid < 0)
    		oops("Fork Failed!", errno);
		if(pid == 0){ // this is the child:
			nodeData[index].previousTemperature = atof(argv[3 + index]);
			sprintf(nodeIdStr, "%d", index);
	   		execlp("./node", "node", nodeIdStr, argv[3 + index], NULL);		
		}
	}
	
      
   float new_integrated_temp = 0.0f;
   float previous_integrated_temp = monitorTemp;
   
   int stableCount = 0;
   float sum_of_client_temps = 0.0f;
   while ( stableCount != numberOfNodes ){
		
		// Listen for node temps:
		for(int index = 0; index < numberOfNodes; index++) {
			fflush(stdout);
			rcvdMsg(msqid, &msg_rcvd);
			if( checkTemp(msg_rcvd.temperature, nodeData[index].previousTemperature, EPSILON) ) {
				stableCount++;	
			}
			else {
				nodeData[index].previousTemperature = msg_rcvd.temperature;
			}
			sum_of_client_temps = (sum_of_client_temps) + (msg_rcvd.temperature);

		}
		
		new_integrated_temp = (2 * previous_integrated_temp + sum_of_client_temps) / 6;
		sum_of_client_temps = 0.0f;
		
		previous_integrated_temp = new_integrated_temp;
		printf("\n Monitor temp: %f \n", new_integrated_temp);

		msg_send.temperature = new_integrated_temp;
    	for (int index =0; index<numberOfNodes; index++) {
			sendMsg(nodeData[index].msqid, &msg_send);
    	}	
   	}
   		printf("\n STABLE TEMPERATURE DETECTED.\nMONITOR TERMINATING...\n");
   	
	// send stable flag to all nodes
	for (int index =0; index<numberOfNodes; index++) {
		msg_send.stable = true;
		msg_send.nodeId = index;
		sendMsg(nodeData[index].msqid, &msg_send);
	}
	

	closeMonitorQueue();   	
	closeNodeQueues(numberOfNodes);
	free(nodeData);
}
