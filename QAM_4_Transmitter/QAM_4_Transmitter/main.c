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

	vTaskStartScheduler();
	return 0;
}
