/*
 * measurement_task.h
 *
 * Created: 13.12.2022 19:27:08
 *  Author: kevin
 */ 


#ifndef MEASUREMENT_TASK_H_
#define MEASUREMENT_TASK_H_

typedef enum 
{
	MEAS_IDLE, 
	MEAS_SENSOR_GET_DATA, 
	MEAS_SAVE_DATA, 
	MEAS_ERROR
}en_measurement_state;

typedef struct 
{
	float temperature; 
	
}st_measurement;

st_measurement gst_measurement; 

void measurement_task( void* pvParameters ); 


#endif /* MEASUREMENT_TASK_H_ */