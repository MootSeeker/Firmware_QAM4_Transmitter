/*
 * QAM4_Transmitter.c
 *
 * Created: 06.12.2022 18:57:08
 * Author : Kevin Perillo
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
	
	LSM9DS1Init( ); 
	readTempData( ); 
	
	initDAC();
	initDACTimer();
	initGenDMA();
	
	xTaskCreate(vQuamGen, NULL, configMINIMAL_STACK_SIZE+500, NULL, 2, NULL);

	vDisplayClear();
	vDisplayWriteStringAtPos(0,0,"QAM4 Transmitter");
	vDisplayWriteStringAtPos(1,0,"EDUBoard Version");
	vDisplayWriteStringAtPos(2,0,"V1.00 Beta");
	
	// For Testing just create data on the begining
	createSendData(); 
	
	vTaskStartScheduler();
	return 0;
}
