/**
 * @file   qamgen.c
 *
 * @brief  	Brief description of the content of test.c
 * @author 	kevin, Juventus Techniker Schule
 * @date   	Jan 10, 2023 - first implementation
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
 * Copyright (c) 2023 Juventus Techniker Schule
 */

 // ********************************************************************************
 /**
 * @brief  Includes
 *
 * Section for module-specific include files
 * If all include files are inserted in main.h, only the file main.h must be included here
 */
#include "main.h"

// ******************************************************************************** 
/**
* @brief  Constant variables
*
* Section for module-specific constant variables (static) that are only valid within the module
*/
 
// Sinus Lookup table for 100% amplitude 
const int16_t sinLookup100[ NR_OF_SAMPLES * 2 ] = { 0x0,0x18F,0x30F,0x471,0x5A7,0x6A6,0x763,0x7D8,
												    0x7FF,0x7D8,0x763,0x6A6,0x5A7,0x471,0x30F,0x18F,
													0x0,0xFE71,0xFCF1,0xFB8F,0xFA59,0xF95A,0xF89D,0xF828,
													0xF801,0xF828,0xF89D,0xF95A,0xFA59,0xFB8F,0xFCF1,0xFE71,
													0x0,0x18F,0x30F,0x471,0x5A7,0x6A6,0x763,0x7D8,
													0x7FF,0x7D8,0x763,0x6A6,0x5A7,0x471,0x30F,0x18F,
													0x0,0xFE71,0xFCF1,0xFB8F,0xFA59,0xF95A,0xF89D,0xF828,
													0xF801,0xF828,0xF89D,0xF95A,0xFA59,0xFB8F,0xFCF1,0xFE71 };
														
// Sinus lookup table for 50% amplitude
const int16_t sinLookup50[ NR_OF_SAMPLES * 2 ] = {  0x0,0xC8,0x187,0x238,0x2D3,0x353,0x3B1,0x3EB,
													0x3FF,0x3EB,0x3B1,0x353,0x2D3,0x238,0x187,0xC8,
													0x0,0xFF38,0xFE79,0xFDC8,0xFD2D,0xFCAD,0xFC4F,0xFC15,
													0xFC01,0xFC15,0xFC4F,0xFCAD,0xFD2D,0xFDC8,0xFE79,0xFF38,
													0x0,0xC8,0x187,0x238,0x2D3,0x353,0x3B1,0x3EB,
													0x3FF,0x3EB,0x3B1,0x353,0x2D3,0x238,0x187,0xC8,
													0x0,0xFF38,0xFE79,0xFDC8,0xFD2D,0xFCAD,0xFC4F,0xFC15,
													0xFC01,0xFC15,0xFC4F,0xFCAD,0xFD2D,0xFDC8,0xFE79,0xFF38 };

// Defined buffer size
#define SENDBUFFER_SIZE 100 // Changed since we send more data

// ********************************************************************************
/**
* @brief  Global variables
*
* Section for global variables
*/
 
//uint8_t sendbuffer[SENDBUFFER_SIZE] = {0,1,0,1,0,1,2,1,3,0,1,1,3,2,1,0,0,1,0,1};

uint8_t sendbuffer[SENDBUFFER_SIZE];	// Dynamic buffer with max size of 100 symbols
uint8_t sendID = 0;						// ID of created data
uint8_t sendbuffer_size = 0;			// Dynamic buffer size
union_float_type senddataf;				// Data buffer to convert float in 4 bytes

// ********************************************************************************
/**
* @brief  Static variables
*
* Section for module-specific variables (static) that are only valid within the module
*/
 
// ******************************************************************************** 
/**
* @brief  Static function prototypes
*
* Section for module-specific function prototypes (static) for functions that are only valid within the
* module
*/
static void fillBuffer( uint16_t buffer[ NR_OF_SAMPLES ]); 

 // ********************************************************************************
 /**
 * @brief  Static functions definitions
 *
 * Definition area for the module-specific functions (static) previously defined within "Static function
 * prototypes"
 */
 
void fillBuffer( uint16_t buffer[ NR_OF_SAMPLES ])
{
	static int pSendbuffer = 0;
	
	//Toggle a Pin at Start of transmission
	if( pSendbuffer == 0 )PORTB.OUTSET |= PIN0_bm; 
	else PORTB.OUTCLR |= PIN0_bm; 
	
	for( int i = 0; i < NR_OF_SAMPLES; i++ )
	{
		switch( sendbuffer[ pSendbuffer ])
		{
			case 0:
			buffer[ i ] = 0x800 + ( sinLookup50[ i ]);
			break;
			case 1:
			buffer[ i ] = 0x800 + ( sinLookup50[ i + 8 ]);
			break;
			case 2:
			buffer[ i ] = 0x800 + ( sinLookup50[ i + 16 ]);
			break;
			case 3:
			buffer[ i ] = 0x800 + ( sinLookup50[ i + 24 ]);
			break;
			case 99: // Debug Case to sync Oscilloscope
			buffer[ i ] = 0x800 + ( sinLookup100[ i ]);
			break;
			
			default:
			// Error Case
			break;
		}
	}
	
	if( pSendbuffer < sendbuffer_size - 1 )
	{
		pSendbuffer++;
	}
	else
	{
		pSendbuffer = 0;
	}
}

 // ********************************************************************************
 /**
 * @brief  Global functions definitions
 *
 * Definition area for the global functions previously defined within "Global function prototypes"
 */
 
void vQuamGen( void *pvParameters )
{
	SemaphoreHandle_t init_synchronisation = *( SemaphoreHandle_t* )pvParameters;
	configASSERT( init_synchronisation );
	
	// Test Pin to signal start of transmission
	PORTB.DIRSET |= PIN0_bm; 
	
	while( evDMAState == NULL ) 
	{
		vTaskDelay( 3 / portTICK_RATE_MS );
	}
			
	xEventGroupWaitBits(evDMAState, DMAGENREADY, false, true, portMAX_DELAY);
	xSemaphoreGive( init_synchronisation );

	for(;;) 
	{
		vTaskDelay( 10 / portTICK_RATE_MS );
	}
}

void createSendData( void )
{	
	sendID++;
	
	//char senddata[10] = "HelloWorld";
	uint8_t datalen = 4; // strlen(senddata);
			
	meas_lock_mutex( ); 
	{
		st_measurement *pst_meas = &gst_measurement;
		//Get Temperature to data buffer
		senddataf.as_float = pst_meas->temperature; 
	}
	meas_unlock_mutex( ); 

	//Add an extra symbol on the begining with a diffrent amplitude to check received signal on the other end.
	//sendbuffer[0] = 99;
	
	//Begin Buffer with two synch symbols for receiever
	sendbuffer[0] = 0;
	sendbuffer[1] = 0;
	
	//Parse ID
	sendbuffer[2] = sendID & 0x03;
	sendbuffer[3] = (sendID >> 2) & 0x03;
	
	//Parse Data length
	sendbuffer[4] = (datalen >> 0) & 0x03;
	sendbuffer[5] = (datalen >> 2) & 0x03;
	sendbuffer[6] = (datalen >> 4) & 0x03;
	sendbuffer[7] = (datalen >> 6) & 0x03;
	
	//Parse Data - 4 Bytes as 2bit symbol
	for(int i = 0; i < datalen;i++)
	{
		sendbuffer[8 + i*4 + 0] = (senddataf.as_uint8[i] >> 0) & 0x03;
		sendbuffer[8 + i*4 + 1] = (senddataf.as_uint8[i] >> 2) & 0x03;
		sendbuffer[8 + i*4 + 2] = (senddataf.as_uint8[i] >> 4) & 0x03;
		sendbuffer[8 + i*4 + 3] = (senddataf.as_uint8[i] >> 6) & 0x03;
	}
	
	//Calculate simple checksum so receiver could check if received correkt and save one byte checksum as 2bit symbol
	uint8_t checksum = 0;
	for(int i = 0; i < 8 + (datalen * 4); i++)
	{
		checksum += sendbuffer[i];
	}
	sendbuffer[7 + (datalen * 4) + 0] = (checksum >> 0) & 0x03;
	sendbuffer[7 + (datalen * 4) + 1] = (checksum >> 2) & 0x03;
	sendbuffer[7 + (datalen * 4) + 2] = (checksum >> 4) & 0x03;
	sendbuffer[7 + (datalen * 4) + 3] = (checksum >> 6) & 0x03;
	
	//Save Sendbuffer size
	sendbuffer_size = 7 + (datalen * 4) + 4;
}

ISR( DMA_CH0_vect )
{
	DMA.CH0.CTRLB |= 0x10;
	fillBuffer( &dacBuffer0[ 0 ]);
}

ISR( DMA_CH1_vect )
{
	DMA.CH1.CTRLB |= 0x10;
	fillBuffer( &dacBuffer1[ 0 ]);
}