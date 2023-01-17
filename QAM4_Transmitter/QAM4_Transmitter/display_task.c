/**
 * @file   display_task.c
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
st_display gst_display;

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
				vDisplayWriteStringAtPos(3,0,"V1.03 Beta - Release");
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