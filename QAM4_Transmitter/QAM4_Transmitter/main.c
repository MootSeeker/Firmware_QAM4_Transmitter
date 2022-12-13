/*
 * QAM4_Transmitter.c
 *
 * Created: 06.12.2022 18:57:08
 * Author : Kevin Perillo
 */ 

#include "main.h"


/* Task handles for heap overflow monitoring. */

typedef struct
{
	TaskHandle_t handle;
	BaseType_t stack_high_water_mark;
}st_task_state;

st_task_state task_state[ TASK_STATES_MAX ];

/* Static semaphore to synchronize Task initialization */
static SemaphoreHandle_t init_synchronisation = NULL;

void init_task( void *pvParameters );

extern void vApplicationIdleHook( void );

void vApplicationIdleHook( void )
{	
	
}

/**
 * Main Loop
 *
 * The main loop creates the initialization task and the scheduler. Everything
 * else is started up in the initialization task.
 */
int main(void)
{
	BaseType_t task_status;

	vInitClock();
	
	vSemaphoreCreateBinary( init_synchronisation );
	configASSERT( init_synchronisation );

	/* Start and initialize the initialization Task. */
	task_status = xTaskCreate( init_task,
								"INIT",
								TASK_STACK_INIT,
								NULL,
								TASK_PRIORITY_INIT,
								&task_state[ 0 ].handle);
	configASSERT(task_status == pdPASS);

	/* Start the scheduler */
	vTaskStartScheduler();
		
	return 0;
}

/**
 * Initialization task
 *
 * This task controls the complete initialization of the system. The different
 * system tasks are started one by one, using a semaphore for synchronisation.
 *
 * @param pvParameters      Not used by this task.
 */
void init_task( void *pvParameters )
{
	/* Parameters not used in this task. */
	( void ) pvParameters;
	BaseType_t task_status;
	
	/* Were starting to create tasks, clear the synchronisation semaphore. */
	xSemaphoreTake( init_synchronisation, 0 );
	
	/* Measurement Task */
	task_status = xTaskCreate( measurement_task,
								"MEAS",
								TASK_STACK_MEAS,
								&init_synchronisation,
								TASK_PRIORITY_MEAS,
								&task_state[ 1 ].handle);
								
	configASSERT( task_status == pdPASS );
	xSemaphoreTake( init_synchronisation, portMAX_DELAY );
	
	initDAC();
	initDACTimer();
	initGenDMA();
	
	// For Testing just create data on the begining
	createSendData();
		
	task_status = xTaskCreate( vQuamGen,
								"GEN", 
								configMINIMAL_STACK_SIZE + 500,
								&init_synchronisation,
								TASK_PRIORITY_MEAS,
								&task_state[ 2 ].handle );
								
	configASSERT( task_status == pdPASS );
	xSemaphoreTake( init_synchronisation, portMAX_DELAY );
	
	vInitDisplay();
	vDisplayClear();
	vDisplayWriteStringAtPos(0,0,"QAM4 Transmitter");
	vDisplayWriteStringAtPos(1,0,"EDUBoard Version");
	vDisplayWriteStringAtPos(2,0,"V1.01 Beta");
	
	/* Initialization completed, suspend the task */
	vTaskSuspend( NULL ); 
}