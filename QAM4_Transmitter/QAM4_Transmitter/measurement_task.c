/**
 * @file   measurement_task.c
 *
 * @brief  	Brief description of the content of test.c
 * @author 	kevin, Juventus Techniker Schule
 * @date   	Jan 15, 2023 - first implementation
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
st_measurement gst_measurement; 

SemaphoreHandle_t meas_mutex; 

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
void measurement_task( void* pvParameters )
{
	st_measurement *pst_meas = &gst_measurement; 

	en_measurement_state state = MEAS_IDLE; 
	TickType_t old_time, runtime;
	
	// Create Mutex to protect measurement data
	meas_mutex = xSemaphoreCreateMutex( ); 
	if(meas_mutex != NULL) xSemaphoreGive( meas_mutex ); 
	    
	SemaphoreHandle_t init_synchronisation = *( SemaphoreHandle_t* )pvParameters;
	configASSERT( init_synchronisation );
	
	LSM9DS1Init( );
	readTempData( );
		
	// Give synchronization semaphore back to init-Task 
	xSemaphoreGive( init_synchronisation );
	
	for( ;; )
	{
		switch( state )
		{
			case MEAS_IDLE: 
			{
				runtime = xTaskGetTickCount( );
				if(( runtime - old_time ) >= 1000 )
				{
					state = MEAS_SENSOR_GET_DATA; 
					old_time = runtime;
				}
				else
				{
					state = MEAS_IDLE; 
				}
				break; 
			}
			
			case MEAS_SENSOR_GET_DATA: 
			{
				xSemaphoreTake( meas_mutex, portMAX_DELAY ); 
				{
					pst_meas->temperature = getTemperatureData( );	
				}
				xSemaphoreGive( meas_mutex );
				
				st_display *pst_display = &gst_display; 
				pst_display->cmd = DISP_SHOW_MEASUREMENT; 
				
				createSendData( ); 
				
				state = MEAS_IDLE; 
				break; 
			}
			
			case MEAS_ERROR:		//Error Case 
			default:
			{
				
				break; 
			} 
		}
		vTaskDelay( 10 / portTICK_RATE_MS ); 
	}
}


void meas_lock_mutex( void )
{
	xSemaphoreTake( meas_mutex, portMAX_DELAY ); 
}

void meas_unlock_mutex( void )
{
	xSemaphoreGive( meas_mutex ); 
}