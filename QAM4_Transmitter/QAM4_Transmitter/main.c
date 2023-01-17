/**
 * @file   main.c
 *
 * @brief  	Brief description of the content of test.c
 * @author 	kevin, Juventus Techniker Schule
 * @date   	Jan 10, 2023 - first implementation
 * @version 1.0.0
 * 
 * MIT License
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Copyright (c) 2023 Juventus Techniker Schule
 */
 
 // ********************************************************************************
 /**
 * @brief  Includes
 *
 * Section for module-specific include files
 * If all include files are inserted in main.h, only the file main.h must be included here
 */
#include "main.h"

 // ******************************************************************************** 
 /**
 * @brief  Constant variables
 *
 * Section for module-specific constant variables (static) that are only valid within the module
 */
 
 // ********************************************************************************
 /**
 * @brief  Global variables
 *
 * Section for global variables
 */
 
/* Task handles for heap overflow monitoring. */

typedef struct
{
	TaskHandle_t handle;
	BaseType_t stack_high_water_mark;
}st_task_state;

st_task_state task_state[ TASK_STATES_MAX ];

 // ********************************************************************************
 /**
 * @brief  Static variables
 *
 * Section for module-specific variables (static) that are only valid within the module
 */
 
 // ******************************************************************************** 
 /**
 * @brief  Static function prototypes
 *
 * Section for module-specific function prototypes (static) for functions that are only valid within the
 * module
 */
 
/* Static semaphore to synchronize Task initialization */
static SemaphoreHandle_t init_synchronisation = NULL;

void init_task( void *pvParameters );

extern void vApplicationIdleHook( void );

void vApplicationIdleHook( void )
{	
	
}

 // ********************************************************************************
 /**
 * @brief  Static functions definitions
 *
 * Definition area for the module-specific functions (static) previously defined within "Static function
 * prototypes"
 */

 // ********************************************************************************
 /**
 * @brief  Global functions definitions
 *
 * Definition area for the global functions previously defined within "Global function prototypes"
 */
 
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
	//createSendData();
		
	task_status = xTaskCreate( vQuamGen,
								"GEN", 
								TASK_STACK_GEN,
								&init_synchronisation,
								TASK_PRIORITY_GEN,
								&task_state[ 2 ].handle );
								
	configASSERT( task_status == pdPASS );
	xSemaphoreTake( init_synchronisation, portMAX_DELAY );
	
	task_status = xTaskCreate( display_handler,
							   "DISP",
							   TASK_STACK_DISP,
						       &init_synchronisation,
							   TASK_PRIORITY_DISP,
							   &task_state[ 3 ].handle );
	configASSERT( task_status == pdPASS );
	xSemaphoreTake( init_synchronisation, portMAX_DELAY );
	

	
	/* Initialization completed, suspend the task */
	vTaskSuspend( NULL ); 
}