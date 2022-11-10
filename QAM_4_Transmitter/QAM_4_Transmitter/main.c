/*
 * QAM_4_Transmitter.c
 *
 * Created: 20.03.2018 18:32:07
 * Author : chaos
 */ 

#include "main.h"


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
	initADC();
	initADCTimer();
	initDecDMA();
	
	xTaskCreate(vQuamGen, NULL, configMINIMAL_STACK_SIZE+500, NULL, 2, NULL);
	
	vDisplayClear();
	vDisplayWriteStringAtPos(0,0,"FreeRTOS 10.0.1");
	vDisplayWriteStringAtPos(1,0,"EDUBoard 1.0");
	vDisplayWriteStringAtPos(2,0,"QAMDECGEN-Base");

	vTaskStartScheduler();
	return 0;
}
