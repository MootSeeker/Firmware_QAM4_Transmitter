/**
 * @file   measurement_task.h
 *
 * @brief  	Brief description of the content of measurement_task.h
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


#ifndef MEASUREMENT_TASK_H_
#define MEASUREMENT_TASK_H_

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
	MEAS_IDLE, 
	MEAS_SENSOR_GET_DATA, 
	MEAS_SAVE_DATA, 
	MEAS_ERROR
}en_measurement_state;

 // ********************************************************************************
 /**
 * @brief  Structures
 *
 * Section for module-specific structures
 */
typedef struct 
{
	float temperature; 
	
}st_measurement;

 // ********************************************************************************
 /**
 * @brief  Global variables
 *
 * Section for module-specific global variables
 */
st_measurement gst_measurement; 

 // ********************************************************************************
 /**
 * @brief  Global function prototypes
 *
 * Section for module-specific global function prototypes
 */
void measurement_task( void* pvParameters ); 
void meas_lock_mutex( void ); 
void meas_unlock_mutex( void ); 


#endif /* END: MEASUREMENT_TASK_H_ */