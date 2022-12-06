/**
 * @file   twiMaster.c
 *
 * @brief  Brief description of the content of template.c
 * @author Kevin Perillo, Juventus Techniker Schule
 * @date   04.12.2022 - first implementation
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
 * Copyright (c) 2022 Juventus Techniker Schule
 */


// ********************************************************************************
/**
 * @brief  Includes
 *
 * Section for module-specific include files
 * If all include files are inserted in main.h, only the file main.h must be included here
 */
#include "main.h"

// I2C Settings
#define CPU_SPEED 32000000
#define BAUDRATE    400000
#define TWI_BAUD ( F_SYS, F_TWI ) (( F_SYS / ( 2 * F_TWI )) - 5 )
#define TWI_BAUDSETTING TWI_BAUD ( CPU_SPEED, BAUDRATE )

// ******************************************************************************** 
/**
 * @brief  Static function prototypes
 *
 * Section for module-specific function prototypes (static) for functions that are only valid within the
 * module
 */
 static uint8_t i2cControl( uint8_t ack, i2cCmd_t cmd ); 

// ********************************************************************************
/**
 * @brief  Static functions definitions
 *
 * Definition area for the module-specific functions (static) previously defined within "Static function
 * prototypes"
 */
 static uint8_t i2cControl(uint8_t ack, i2cCmd_t cmd) 
 {
	 ack = ( ack > 0 ? 1 : 0 );
	 ack <<= 2;
	 return ack | (cmd & 0x03);
 }


// ********************************************************************************
/**
 * @brief  Global functions definitions
 *
 * Definition area for the global functions previously defined within "Global function prototypes"
 */

/**
 *
 */ 
void twi_init( void )
{
	// Init GPIO Pins
	PORTC.DIRSET = 0x03;
	PORTC.OUT = 0x03;
	
	// Set I2C to Master
	TWIC.MASTER.CTRLC  = i2cControl(1, NOACT);
	TWIC.MASTER.BAUD   = TWI_BAUDSETTING;
	TWIC.MASTER.CTRLA  = TWI_MASTER_ENABLE_bm;
	TWIC.MASTER.STATUS = TWI_MASTER_BUSSTATE_IDLE_gc;
}

void twi_read( uint8_t add, uint8_t reg, uint8_t n, uint8_t* data )
{
	TWIC.MASTER.ADDR = add;
	
	while(!(TWIC.MASTER.STATUS&TWI_MASTER_WIF_bm));
	
	TWIC.MASTER.DATA = (reg);
	TWIC.MASTER.ADDR = (add | 0x01);
	TWIC.MASTER.CTRLC = i2cControl((n>1?1:0), START);
	
	for(int i = 0; i < n; i++) 
	{
		while(!(TWIC.MASTER.STATUS&TWI_MASTER_RIF_bm));
		data[i] = TWIC.MASTER.DATA;
		TWIC.MASTER.CTRLC = i2cControl((i>=n-1?1:0), (i>=n-1?STOP:BYTEREC));
	}
}

uint8_t twi_readByte( uint8_t add, uint8_t reg )
{
	TWIC.MASTER.ADDR = add;
	
	while(!(TWIC.MASTER.STATUS&TWI_MASTER_WIF_bm));
	
	TWIC.MASTER.DATA = (reg);
	TWIC.MASTER.ADDR = (add | 0x01);
	
	while(!(TWIC.MASTER.STATUS&TWI_MASTER_RIF_bm));
	
	uint8_t returndata = TWIC.MASTER.DATA;
	TWIC.MASTER.CTRLC = i2cControl(0, STOP);
	
	return returndata;
}

void twi_write( uint8_t add, uint8_t reg, uint8_t n, uint8_t* data )
{
	TWIC.MASTER.ADDR = add;
	while(!(TWIC.MASTER.STATUS&TWI_MASTER_WIF_bm));
	TWIC.MASTER.DATA = (reg);
	while(!(TWIC.MASTER.STATUS&TWI_MASTER_WIF_bm));
	for(int i = 0; i < n; i++) 
	{
		TWIC.MASTER.DATA = data[i];
		while(!(TWIC.MASTER.STATUS&TWI_MASTER_WIF_bm));
	}
	
	TWIC.MASTER.CTRLC = i2cControl(0, STOP);
}

void twi_writeByte( uint8_t add, uint8_t reg, uint8_t data )
{
	TWIC.MASTER.ADDR = add;
	
	while(!(TWIC.MASTER.STATUS&TWI_MASTER_WIF_bm));
	
	TWIC.MASTER.DATA = (reg);
	
	while(!(TWIC.MASTER.STATUS&TWI_MASTER_WIF_bm));
	
	TWIC.MASTER.DATA = data;
	
	while(!(TWIC.MASTER.STATUS&TWI_MASTER_WIF_bm));
	
	TWIC.MASTER.CTRLC = i2cControl(0, STOP);
}