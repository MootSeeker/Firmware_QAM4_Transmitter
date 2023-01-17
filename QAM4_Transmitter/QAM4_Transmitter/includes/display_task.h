/**
 * @file   display_task.h
 *
 * @brief  	Brief description of the content of display_task.h
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


#ifndef DISPLAY_TASK_H_
#define DISPLAY_TASK_H_

 // ********************************************************************************
 /**
 * @brief  Includes
 *
 * Section for module-specific include files
 * - Normally not necessary in header files
 */

 
 // ********************************************************************************
 /**
 * @brief  Macros
 *
 * Section for module-specific definitions (constants) and macros
 */

 
 // ********************************************************************************
 /**
 * @brief  Enumerations
 *
 * Section for module-specific enumerations
 */
typedef enum 
{
	DISP_IDLE, 
	DISP_SHOW_MEASUREMENT, 
	DISP_SHOW_ERROR, 
	DISP_SHOW_VERSION
}en_Display_State;

 // ********************************************************************************
 /**
 * @brief  Structures
 *
 * Section for module-specific structures
 */
typedef struct 
{
	uint8_t cmd; 
	uint8_t layout; 
}st_display;

 // ********************************************************************************
 /**
 * @brief  Global variables
 *
 * Section for module-specific global variables
 */
extern st_display gst_display; 

 // ********************************************************************************
 /**
 * @brief  Global function prototypes
 *
 * Section for module-specific global function prototypes
 */
void display_handler( void *pvParameters ); 
void display_clear( void ); 
void display_show_data( void ); 


#endif /* END: DISPLAY_TASK_H_ */