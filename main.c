/*
 * CPE-555 Real-Time and Embedded Systems
 * Stevens Institute of Technology
 * Fall 2016
 *
 * Homework 3
 *
 * Name: Dler Hasan
 */

/* Standard includes */
#include <stdio.h>

/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"


/* define the queue parameters*/
	#define QUEUE_LENGTH 15

/* global variables */
	QueueHandle_t numberQueue = 0;
	int globalCount = 0;


// Task sender number 2
void TxTask1(void *p){
	// TxTask1 Continuously Transmit
	while(1){
		printf("TxTask1: Send %d to receiver task\n", globalCount);
		if(! xQueueSendToBack(numberQueue, &globalCount, 500)){
			printf("TxTask1: Failed to send item to queue within 500ms\n");
		}
		// Increment global variable by 1.
		globalCount++;
		// Wait 500 milliseconds
		vTaskDelay(500);
	}
}

void TxTask2(void *p){
	// TxTask2 Continuously Transmit
	while(1){
		printf("TxTask2: Send %d to receiver task\n", globalCount);
		if(! xQueueSendToBack(numberQueue, &globalCount, 500)){
			printf("TxTask2: Failed to send item to queue within 500ms\n");
		}
		// Increment global variable by 1.
		globalCount++;
		// Wait 500 milliseconds
		vTaskDelay(500);
	}
}

// Task Receiver
void RxTask(void *p){
	int rx_receive = 0;
	while(1){
		if(xQueueReceive(numberQueue, &rx_receive, 2000)){
			printf("Received %d\n", rx_receive);
		}else {
			puts("Failed to receive\n");
		}
	}
}

int main( void )
{
	// Create queue
	numberQueue = xQueueCreate(QUEUE_LENGTH, sizeof(int));

	// Prompt info if Queue fails
	if(numberQueue == 0){
		printf("Failed to create the queue");
	}

	// Create Tasks: TxTask1, TxTask2 RxTask
	xTaskCreate(TxTask1, (signed char*)"t1", 1024, 0, 1, 0);
	xTaskCreate(TxTask2, (signed char*)"t2", 1024, 0, 1, 0);
	xTaskCreate(RxTask, (signed char*)"Rx", 1024, 0, 1, 0);
	vTaskStartScheduler();

	return 0;
}

/* (Add any additional function definitions here) */
