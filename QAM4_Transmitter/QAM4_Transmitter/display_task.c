/*
 * display_task.c
 *
 * Created: 10.01.2023 19:36:19
 *  Author: kevin
 */ 

#include "main.h"

st_display gst_display;

void display_handler( void *pvParameters )
{
	SemaphoreHandle_t init_synchronisation = *( SemaphoreHandle_t* )pvParameters;
	configASSERT( init_synchronisation );
	
	st_display *pst_display = &gst_display; 
	
	//Set Display to show version for init
	en_Display_State state = DISP_SHOW_VERSION;
	en_Display_State old_cmd = state;  
	pst_display->cmd = state; // Save state for global 
	
	TickType_t old_time, runtime; 
	
	vInitDisplay();
	display_clear();
	
	// Give synchronization semaphore back to init-Task
	xSemaphoreGive( init_synchronisation );
	
	for( ;; )
	{
		switch( state )
		{
			case DISP_IDLE: 
			{
				 
				vDisplayWriteStringAtPos(3,0,"Device is Ideling");
				
				// Read new command if available
				if(old_cmd != pst_display->cmd)
				{
					state = pst_display->cmd;
					old_cmd = state; 
				}
				else
				{
					old_cmd = DISP_IDLE; 
				}
 
				break; 
			}
			
			case DISP_SHOW_MEASUREMENT: 
			{
				float temp; 
				
				meas_lock_mutex( ); 
				{
					st_measurement *pst_meas = &gst_measurement;
					temp = pst_meas->temperature; 
				}
				meas_unlock_mutex( ); 
				
				display_clear( );
				vDisplayWriteStringAtPos(0,0,"QAM4 Transmitter");
				vDisplayWriteStringAtPos( 1, 0, "Temp: %f C", temp );
				
				old_cmd = state; 
				state = DISP_IDLE; 
				break; 
			}
			
			case DISP_SHOW_VERSION: 
			{
				display_clear( ); 
				
				vDisplayWriteStringAtPos(0,0,"QAM4 Transmitter");
				vDisplayWriteStringAtPos(1,0,"EDUBoard Version");
				vDisplayWriteStringAtPos(3,0,"V1.02 Beta - Release");
				state = DISP_SHOW_MEASUREMENT; 
				break; 
			}
			
			case DISP_SHOW_ERROR:	//Error Case
			default: 
			{
				display_clear( );
				
				vDisplayWriteStringAtPos(0,0,"Error!");
				vDisplayWriteStringAtPos(1,0,"Transmission is not");
				vDisplayWriteStringAtPos(2,0,"Possible!");
				vDisplayWriteStringAtPos(3,0,"Please Reset");
				break; 
			}
		}
		vTaskDelay( 1000 / portTICK_RATE_MS ); 
	}
}



void display_clear( void )
{
	vDisplayClear();
}

void display_show_data( void );