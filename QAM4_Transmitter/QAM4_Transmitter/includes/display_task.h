/*
 * display_task.h
 *
 * Created: 10.01.2023 19:36:44
 *  Author: kevin
 */ 


#ifndef DISPLAY_TASK_H_
#define DISPLAY_TASK_H_

typedef enum 
{
	DISP_IDLE, 
	DISP_SHOW_MEASUREMENT, 
	DISP_SHOW_ERROR, 
	DISP_SHOW_VERSION
}en_Display_State;

typedef struct 
{
	uint8_t cmd; 
	uint8_t layout; 
}st_display;

extern st_display gst_display; 


void display_handler( void *pvParameters ); 
void display_clear( void ); 
void display_show_data( void ); 


#endif /* DISPLAY_TASK_H_ */