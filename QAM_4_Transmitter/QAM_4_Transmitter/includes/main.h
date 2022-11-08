/*
 * main.h
 *
 * Created: 08.11.2022 17:52:40
 *  Author: kevin
 */ 


#ifndef MAIN_H_
#define MAIN_H_

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






#endif /* MAIN_H_ */