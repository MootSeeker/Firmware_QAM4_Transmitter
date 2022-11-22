/*
 * main.h
 *
 * Created: 08.11.2022 17:52:40
 *  Author: kevin
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include <string.h>


// FreeRTOS includes 
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#include "stack_macros.h"

// AVR includes
#include "avr_compiler.h"

// Driver Files 
#include "pmic_driver.h"
#include "TC_driver.h"
#include "clksys_driver.h"
#include "sleepConfig.h"
#include "port_driver.h"
#include "mem_check.h"
#include "errorHandler.h"

// Modules
#include "init.h"
#include "NHD0420Driver.h"
#include "qamgen.h"
#include "measurement.h"

/*--- System configuration --------------------------------------------------------------------------------
 *
 */
/* Task stack size
 * NOTE: Stack size in WORDs, Heap in BYTEs! 
 */
 #define TASK_STACK_MEAS	( configMINIMAL_STACK_SIZE + 200 )
 
 
 /* Task Priorities */
 #define TASK_PRIORITY_MEAS	( 2 )
 
 /* Task Handles */
 #define TASK_HANDLE_MEAS	( 1 )






#endif /* MAIN_H_ */