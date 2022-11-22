/*
 * measurement.h
 *
 * Created: 22.11.2022 14:34:55
 *  Author: kevin
 */ 


#ifndef MEASUREMENT_H_
#define MEASUREMENT_H_


typedef struct  
{
	//Measured values
	float temperature; 
	float humidity; 
	
	
}st_measurement;


extern st_measurement gst_measurement; 


void measurement_handler( void *pvParameters ); 

#endif /* MEASUREMENT_H_ */