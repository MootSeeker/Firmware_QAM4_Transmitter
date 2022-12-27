/*
 * lsm9ds1.c
 *
 * Created: 06.12.2022 10:23:49
 *  Author: kevin
 */ 


#include "main.h"

 int16_t gx = 0;
 int16_t gy = 0;
 int16_t gz = 0;
 int16_t ax = 0;
 int16_t ay = 0;
 int16_t az = 0;
 int16_t mx = 0;
 int16_t my = 0;
 int16_t mz = 0;
 
 float temperature = 0;
 
void LSM9DS1Init(void) 
{
	  twi_init();
	  //InitGyro
	  twi_writeByte(GYROACCADDRESS, CTRL_REG1_G, 0xC8); //Add Datarate & Scale - Full Scale = 500dps
	  twi_writeByte(GYROACCADDRESS, CTRL_REG2_G, 0x00);
	  twi_writeByte(GYROACCADDRESS, CTRL_REG3_G, 0x00);
	  
	  //InitACC
	  twi_writeByte(GYROACCADDRESS, CTRL_REG6_XL, 0x98); //Add Datarate & Scale
	  twi_writeByte(GYROACCADDRESS, CTRL_REG7_XL, 0x00);
	  
	  //General Gyro & ACC Config
	  twi_writeByte(GYROACCADDRESS, CTRL_REG8, 0x04);
	  twi_writeByte(GYROACCADDRESS, CTRL_REG9, 0x10);
	  twi_writeByte(GYROACCADDRESS, FIFO_CTRL, 0xC0);

	  //InitMag
	  twi_writeByte(MAGADDRESS, CTRL_REG1_M, 0x1C); //Add Datarate
	  twi_writeByte(MAGADDRESS, CTRL_REG2_M, 0x00); //Set Scale
	  twi_writeByte(MAGADDRESS, CTRL_REG3_M, 0x00);
	  twi_writeByte(MAGADDRESS, CTRL_REG4_M, 0x00);
	  twi_writeByte(MAGADDRESS, CTRL_REG5_M, 0x00);

	  //Enable Gyro and ACC
	  twi_writeByte(GYROACCADDRESS, CTRL_REG4, 0x38);
	  twi_writeByte(GYROACCADDRESS, CTRL_REG5_XL, 0x38);
}
  
  void readACCData(void) 
  {
	  uint8_t temp[6];
	  twi_read( GYROACCADDRESS, OUT_X_L_XL, 6, temp );
	  ax = (temp[1] << 8)| temp[0];
	  ay = (temp[3] << 8)| temp[2];
	  az = (temp[5] << 8)| temp[4];
  }
  
  void readGyroData(void) {
	  uint8_t temp[6];
	  twi_read(GYROACCADDRESS, OUT_X_L_G, 6, temp);
	  gx = (temp[1] << 8)| temp[0];
	  gy = (temp[3] << 8)| temp[2];
	  gz = (temp[5] << 8)| temp[4];
  }
  
  void readMagData(void) 
  {
	  uint8_t temp[6];
	  twi_read(MAGADDRESS, OUT_X_L_M, 6, temp);
	  mx = (temp[1] << 8)| temp[0];
	  my = (temp[3] << 8)| temp[2];
	  mz = (temp[5] << 8)| temp[4];
  }
  
  void readTempData( void ) 
  {
	  uint8_t temp[2];
	  int16_t tempValue = 0;
	  twi_read(GYROACCADDRESS, OUT_TEMP_L, 2, temp);
	  tempValue = ((( int16_t ) temp[ 1 ] << 12 ) | temp[ 0 ] << 4 ) >> 4;
	  temperature *= 0.9;
	  temperature += (( float ) tempValue / 16 ) + 25;  
  }
  
  int16_t getGyroData( int axis ) 
  {
	  switch( axis ) 
	  {
		  case X_AXIS:
		  return gx;
		  break;
		  case Y_AXIS:
		  return gy;
		  break;
		  case Z_AXIS:
		  return gz;
		  break;
	  }
	  return 0;
  }
  
  
  int16_t getACCData( int axis ) 
  {
	  switch( axis ) 
	  {
		  case X_AXIS:
		  return ax;
		  break;
		  case Y_AXIS:
		  return ay;
		  break;
		  case Z_AXIS:
		  return az;
		  break;
	  }
	  return 0;
  }
  
  
  int16_t getMagData( int axis ) 
  {
	  switch( axis ) 
	  {
		  case X_AXIS:
		  return mx;
		  break;
		  case Y_AXIS:
		  return my;
		  break;
		  case Z_AXIS:
		  return mz;
		  break;
	  }
	  return 0;
  }
  
  
  float getTemperatureData( ) 
  {
	  readTempData( ); 
	  return temperature; 
  }