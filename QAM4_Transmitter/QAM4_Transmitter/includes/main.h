/*
 * main.h
 *
 * Created: 04.12.2022 14:07:52
 *  Author: kevin
 */ 


#ifndef MAIN_H_
#define MAIN_H_

/*---------- Global includes ---------- */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/*---------- Controller includes ----------*/ 
#include <avr/io.h>
#include <avr/interrupt.h>

#include "avr_compiler.h"
#include "pmic_driver.h"
#include "TC_driver.h"
#include "clksys_driver.h"
#include "sleepConfig.h"
#include "port_driver.h"

/* FreeRTOS includes ---------- */
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#include "stack_macros.h"

/*---------- Template includes --------- */
//Utilities
#include "mem_check.h"
#include "init.h"
#include "errorHandler.h"
//Display
#include "NHD0420Driver.h"
//Modulation
#include "qaminit.h"
#include "qamgen.h"
//Sensor

/* ---------- Private includes ---------- */
#include "twiMaster.h"
#include "lsm9ds1.h"
#include "measurement_task.h"
#include "display_task.h"


#define TASK_STATES_MAX ( 4 )

/* Task Stack Sizes
 * NOTE: Stack sizes in WORDs, Heap in BYTEs! */
#define TASK_STACK_INIT              ( configMINIMAL_STACK_SIZE )
#define TASK_STACK_MEAS				 ( configMINIMAL_STACK_SIZE )
#define TASK_STACK_GEN				 ( configMINIMAL_STACK_SIZE + 500 )
#define TASK_STACK_DISP				 ( configMINIMAL_STACK_SIZE )

/* Task Priorities */
#define TASK_PRIORITY_INIT           ( 3 )
#define TASK_PRIORITY_MEAS			 ( 2 )
#define TASK_PRIORITY_GEN			 ( 3 )
#define TASK_PRIORITY_DISP			 ( 1 )


// ..........................................................................................................
/**
 * @brief  Universal usable union for float data values
 */
typedef union _unionf32
{
    /* Example 1.234 ( = 0x3F9DF3B6 : IEEE-754) stored as float
     *                                                                     MSB            LSB
     * as_float:      | SEEEEEEE | EMMMMMMM | MMMMMMMM | MMMMMMMM |  =>  | 3F | 9D | F3 | B6 |
     * as_uint32:     | SEEEEEEE | EMMMMMMM | MMMMMMMM | MMMMMMMM |  =>  | 3F | 9D | F3 | B6 |
     * as_uint16[0]:                        | MMMMMMMM | MMMMMMMM |                | F3 | B6 |
     * as_uint16[1]:  | SEEEEEEE | EMMMMMMM |                            | 3F | 9D |
     * as_uint8[0]:                                    | MMMMMMMM |                     | B6 |
     * as_uint8[1]:                         | MMMMMMMM |                           | F3 |
     * as_uint8[2]:              | EMMMMMMM |                                 | 9D |
     * as_uint8[3]:   | SEEEEEEE |                                       | 3F |
     */
	float    as_float;      // 1 * 4 byte (IEEE format)
	uint32_t as_uint32;     // 1 * 4 byte
	uint16_t as_uint16[2];  // 2 * 2 byte
    uint8_t  as_uint8[4];   // 4 byte
} union_float_type;

#endif /* MAIN_H_ */