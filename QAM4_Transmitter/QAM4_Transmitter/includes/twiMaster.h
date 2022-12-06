/**
 * @file   twiMaster.h
 *
 * @brief  Brief description of the content of template.h
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


#ifndef TWIMASTER_H_
#define TWIMASTER_H_

// ********************************************************************************
/**
 * @brief  Includes
 *
 * Section for module-specific include files
 * - Normally not necessary in header files
 */

 
// ********************************************************************************
/**
 * @brief  Macros
 *
 * Section for module-specific definitions (constants) and macros
 */
// I2C Settings
 #define CPU_SPEED 32000000
 #define BAUDRATE    400000
 #define TWI_BAUD(F_SYS, F_TWI) ((F_SYS / (2 * F_TWI)) - 5)
 #define TWI_BAUDSETTING TWI_BAUD(CPU_SPEED, BAUDRATE)
 
// ********************************************************************************
/**
 * @brief  Enumerations
 *
 * Section for module-specific enumerations
 */

//I2C Commands
typedef enum i2cCmd_Tag
{
	NOACT	= 0,
	START	= 1,
	BYTEREC = 2,
	STOP		= 3
}i2cCmd_t;

// ********************************************************************************
/**
 * @brief  Global function prototypes
 *
 * Section for module-specific global function prototypes
 */

void twi_init( void );
void twi_read( uint8_t add, uint8_t reg, uint8_t n, uint8_t* data );
void twi_write( uint8_t add, uint8_t reg, uint8_t n, uint8_t* data ); 
void twi_writeByte( uint8_t add, uint8_t reg, uint8_t data );

uint8_t twi_readByte( uint8_t add, uint8_t reg );

#endif /* TWIMASTER_H_ */