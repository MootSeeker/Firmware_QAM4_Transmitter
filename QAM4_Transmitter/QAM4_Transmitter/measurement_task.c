/*
 * measurement_task.c
 *
 * Created: 13.12.2022 19:28:12
 *  Author: kevin
 */ 

#include "main.h"

st_measurement gst_measurement; 

SemaphoreHandle_t meas_mutex; 

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