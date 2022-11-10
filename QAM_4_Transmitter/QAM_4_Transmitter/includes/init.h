/*
 * init.h
 *
 * Created: 20.03.2018 19:00:55
 *  Author: chaos
 */ 


#ifndef INIT_H_
#define INIT_H_

//QAM define 
#define NR_OF_SAMPLES						32UL
#define GENERATOR_FREQUENCY_INITIAL_VALUE	1000UL * NR_OF_SAMPLES
#define DECODER_FREQUENCY_INITIAL_VALUE		1000UL * NR_OF_SAMPLES

#define		DMAGENREADY	1<<0
#define		DMADECREADY	1<<0

EventGroupHandle_t evDMAState;


extern uint16_t dacBuffer0[NR_OF_SAMPLES];
extern uint16_t dacBuffer1[NR_OF_SAMPLES];
extern uint16_t adcBuffer0[NR_OF_SAMPLES];
extern uint16_t adcBuffer1[NR_OF_SAMPLES];

void initGenDMA(void);
void initDecDMA(void);
void initDAC(void);
void initADC(void);
void initDACTimer(void);
void initADCTimer(void);

void vInitClock(void);


#endif /* INIT_H_ */