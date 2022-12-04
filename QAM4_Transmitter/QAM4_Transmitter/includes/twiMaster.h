/*
 * twiMaster.h
 *
 * Created: 04.12.2022 14:22:16
 *  Author: kevin
 */ 


#ifndef TWIMASTER_H_
#define TWIMASTER_H_




//I2C Commands
typedef enum i2cCmd_Tag
{
	NOACT	= 0,
	START	= 1,
	BYTEREC = 2,
	STOP		= 3
}i2cCmd_t;

void twi_init( void );
void twi_read( uint8_t add, uint8_t reg, uint8_t n, uint8_t* data );
void twi_write( uint8_t add, uint8_t reg, uint8_t n, uint8_t* data ); 
void twi_writeByte( uint8_t add, uint8_t reg, uint8_t data );

uint8_t twi_readByte( uint8_t add, uint8_t reg );

#endif /* TWIMASTER_H_ */