/*
 * QAM4_Transmitter.c
 *
 * Created: 20.03.2018 18:32:07
 * Author : Martin Burger
 */ 

//#include <avr/io.h>
#include "avr_compiler.h"
#include "pmic_driver.h"
#include "TC_driver.h"
#include "clksys_driver.h"
#include "sleepConfig.h"
#include "port_driver.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "event_groups.h"
#include "stack_macros.h"

#include "mem_check.h"

#include "init.h"
#include "errorHandler.h"
#include "NHD0420Driver.h"

#include "qaminit.h"
#include "qamgen.h"


extern void vApplicationIdleHook( void );

void vApplicationIdleHook( void )
{	
	
}

int main(void)
{
	vInitClock();
	vInitDisplay();
	
	initDAC();
	initDACTimer();
	initGenDMA();
	
	xTaskCreate(vQuamGen, NULL, configMINIMAL_STACK_SIZE+500, NULL, 2, NULL);

	vDisplayClear();
	vDisplayWriteStringAtPos(0,0,"QAM4 Transmitter");
	vDisplayWriteStringAtPos(1,0,"EDUBoard Version");
	vDisplayWriteStringAtPos(2,0,"V1.00 Beta");
	vTaskStartScheduler();
	return 0;
}
