/*
 * qaminit.c
 *
 *  Created: 06.12.2022 18:57:51
 *  Author: Kevin Perillo
 */ 

#include "main.h"

uint16_t dacBuffer0[ NR_OF_SAMPLES ] = {  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
										0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
										0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
										0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

uint16_t dacBuffer1[ NR_OF_SAMPLES ] = {  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
										0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
										0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
										0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };


void initDAC( void ) 
{
	DACB.CTRLA   = DAC_CH0EN_bm;
	DACB.CTRLB   = DAC_CH0TRIG_bm;
	DACB.CTRLC   = 0x00;
	DACB.EVCTRL  = 0x00;
	DACB.CTRLA  |= DAC_ENABLE_bm;
	PORTB.DIRSET = 0x04;
}

void initDACTimer( void ) 
{
	TC0_ConfigClockSource( &TCD0, TC_CLKSEL_DIV1_gc );
	TC0_ConfigWGM( &TCD0, TC_WGMODE_SINGLESLOPE_gc );	
	TC_SetPeriod( &TCD0, 32000000 / ( GENERATOR_FREQUENCY_INITIAL_VALUE ));  
	EVSYS.CH0MUX = EVSYS_CHMUX_TCD0_OVF_gc; //Setup Eventsystem when timer TCD0 overflows
}

void initCommonDMA( void ) 
{
	if( evDMAState == NULL ) 
	{
		evDMAState = xEventGroupCreate();
		DMA.CTRL = 0;
		DMA.CTRL = DMA_RESET_bm;
		while ((DMA.CTRL & DMA_RESET_bm) != 0);

		DMA.CTRL = DMA_ENABLE_bm | DMA_DBUFMODE_CH01CH23_gc;
	}
}

void initGenDMA( void ) 
{
	initCommonDMA( );
	
	DMA.CH0.REPCNT    = 0;
	DMA.CH0.CTRLB    |= 0x01;
	DMA.CH0.CTRLA     = DMA_CH_BURSTLEN_2BYTE_gc | DMA_CH_SINGLE_bm | DMA_CH_REPEAT_bm;					// ADC result is 2 byte 12 bit word
	DMA.CH0.ADDRCTRL  =	DMA_CH_SRCRELOAD_TRANSACTION_gc | DMA_CH_SRCDIR_INC_gc | DMA_CH_DESTRELOAD_BURST_gc | DMA_CH_DESTDIR_INC_gc;	// reload source after every burst, reload dest after every transaction
	DMA.CH0.TRIGSRC   = DMA_CH_TRIGSRC_DACB_CH0_gc;
	DMA.CH0.TRFCNT    = NR_OF_SAMPLES*2;	// always the number of bytes, even if burst length > 1
	DMA.CH0.SRCADDR0  = (( uint16_t )( &dacBuffer0[ 0 ]) >> 0 ) & 0xFF;
	DMA.CH0.SRCADDR1  = (( uint16_t )( &dacBuffer0[ 0 ]) >>  8 ) & 0xFF;
	DMA.CH0.SRCADDR2  = 0;
	DMA.CH0.DESTADDR0 = (( uint16_t )( &DACB.CH0DATA ) >> 0 ) & 0xFF;
	DMA.CH0.DESTADDR1 = (( uint16_t )( &DACB.CH0DATA ) >> 8 ) & 0xFF;
	DMA.CH0.DESTADDR2 = 0;

	DMA.CH1.REPCNT    = 0;
	DMA.CH1.CTRLB    |= 0x01;
	DMA.CH1.CTRLA     = DMA_CH_BURSTLEN_2BYTE_gc | DMA_CH_SINGLE_bm | DMA_CH_REPEAT_bm;
	DMA.CH1.ADDRCTRL  = DMA_CH_SRCRELOAD_TRANSACTION_gc | DMA_CH_SRCDIR_INC_gc | DMA_CH_DESTRELOAD_BURST_gc | DMA_CH_DESTDIR_INC_gc;
	DMA.CH1.TRIGSRC   = DMA_CH_TRIGSRC_DACB_CH0_gc;
	DMA.CH1.TRFCNT    = NR_OF_SAMPLES * 2;
	DMA.CH1.SRCADDR0  = (( uint16_t )( &dacBuffer1[ 0 ] ) >> 0 ) & 0xFF;
	DMA.CH1.SRCADDR1  = (( uint16_t )( &dacBuffer1[ 0 ] ) >>  8 ) & 0xFF;
	DMA.CH1.SRCADDR2  = 0;
	DMA.CH1.DESTADDR0 = (( uint16_t )( &DACB.CH0DATA ) >> 0 ) & 0xFF;
	DMA.CH1.DESTADDR1 = (( uint16_t )( &DACB.CH0DATA ) >> 8 ) & 0xFF;
	DMA.CH1.DESTADDR2 = 0;
	
	DMA.CH0.CTRLA |= DMA_CH_ENABLE_bm;
	DMA.CH1.CTRLA |= DMA_CH_ENABLE_bm; // later, not yet tested!
	
	xEventGroupSetBits(evDMAState, DMAGENREADY);
}

//void initDecDMA(void) {
	//initCommonDMA();
	//
	//DMA.CH2.REPCNT = 0;
	//DMA.CH2.CTRLB |= 0x01;
	//DMA.CH2.CTRLA = DMA_CH_BURSTLEN_2BYTE_gc | DMA_CH_SINGLE_bm | DMA_CH_REPEAT_bm;
	//DMA.CH2.ADDRCTRL = DMA_CH_SRCRELOAD_BURST_gc | DMA_CH_SRCDIR_INC_gc | DMA_CH_DESTRELOAD_TRANSACTION_gc | DMA_CH_DESTDIR_INC_gc;
	//DMA.CH2.TRIGSRC = DMA_CH_TRIGSRC_ADCA_CH0_gc;
	//DMA.CH2.TRFCNT = NR_OF_SAMPLES*2;
	//DMA.CH2.SRCADDR0 = ((uint16_t)(&ADCA.CH0.RES) >> 0) & 0xFF;
	//DMA.CH2.SRCADDR1 = ((uint16_t)(&ADCA.CH0.RES) >> 8) & 0xFF;
	//DMA.CH2.SRCADDR2 = 0x00;
	//DMA.CH2.DESTADDR0 = ((uint16_t)(&adcBuffer0[0]) >> 0) & 0xFF;
	//DMA.CH2.DESTADDR1 = ((uint16_t)(&adcBuffer0[0]) >> 8) & 0xFF;
	//DMA.CH2.DESTADDR2 = 0x00;
//
	//DMA.CH3.REPCNT = 0;
	//DMA.CH3.CTRLB |= 0x01;
	//DMA.CH3.CTRLA = DMA_CH_BURSTLEN_2BYTE_gc | DMA_CH_SINGLE_bm | DMA_CH_REPEAT_bm;
	//DMA.CH3.ADDRCTRL = DMA_CH_SRCRELOAD_BURST_gc | DMA_CH_SRCDIR_INC_gc | DMA_CH_DESTRELOAD_TRANSACTION_gc | DMA_CH_DESTDIR_INC_gc;
	//DMA.CH3.TRIGSRC = DMA_CH_TRIGSRC_ADCA_CH0_gc;
	//DMA.CH3.TRFCNT = NR_OF_SAMPLES*2;
	//DMA.CH3.SRCADDR0 = ((uint16_t)(&ADCA.CH0.RES) >> 0) & 0xFF;
	//DMA.CH3.SRCADDR1 = ((uint16_t)(&ADCA.CH0.RES) >> 8) & 0xFF;
	//DMA.CH3.SRCADDR2 = 0x00;
	//DMA.CH3.DESTADDR0 = ((uint16_t)(&adcBuffer1[0]) >> 0) & 0xFF;
	//DMA.CH3.DESTADDR1 = ((uint16_t)(&adcBuffer1[0]) >> 8) & 0xFF;
	//DMA.CH3.DESTADDR2 = 0x00;
//
	//DMA.CH2.CTRLA |= DMA_CH_ENABLE_bm;
	//DMA.CH3.CTRLA |= DMA_CH_ENABLE_bm;
	//
	//xEventGroupSetBits(evDMAState, DMADECREADY);
//}