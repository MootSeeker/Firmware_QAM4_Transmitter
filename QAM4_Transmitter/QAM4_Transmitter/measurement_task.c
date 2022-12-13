/*
 * measurement_task.c
 *
 * Created: 13.12.2022 19:28:12
 *  Author: kevin
 */ 

#include "main.h"

st_measurement gst_measurement; 


void measurement_task( void* pvParameters )
{
	st_measurement *pst_meas = &gst_measurement; 

	en_measurement_state state = MEAS_IDLE; 
	    
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
				
				break; 
			}
			
			case MEAS_SENSOR_GET_DATA: 
			{
				
				state = MEAS_IDLE; 
				break; 
			}
			
			case MEAS_SAVE_DATA: 
			{
				
				state = MEAS_IDLE; 
				break; 
			}
			
			case MEAS_ERROR: 
			default:
			{
				
				break; 
			} 
		}
		vTaskDelay( 10 / portTICK_RATE_MS ); 
	}
}