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
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
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


#endif /* MAIN_H_ */