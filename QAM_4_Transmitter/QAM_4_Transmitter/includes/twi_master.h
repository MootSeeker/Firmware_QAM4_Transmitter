/*
 * twi_master.h
 *
 * Created: 12.11.2022 07:26:50
 *  Author: kevin
 */ 


#ifndef TWI_MASTER_H_
#define TWI_MASTER_H_

/*! Baud register setting calculation. Formula described in datasheet. */
#define TWI_BAUD(F_SYS, F_TWI) ((F_SYS / (2 * F_TWI)) - 5)


/*! Transaction status defines. */
#define TWIM_STATUS_READY              0
#define TWIM_STATUS_BUSY               1


/*! Transaction result enumeration. */
typedef enum TWIM_RESULT_enum 
{
	TWIM_RESULT_UNKNOWN          = (0x00<<0),
	TWIM_RESULT_OK               = (0x01<<0),
	TWIM_RESULT_BUFFER_OVERFLOW  = (0x02<<0),
	TWIM_RESULT_ARBITRATION_LOST = (0x03<<0),
	TWIM_RESULT_BUS_ERROR        = (0x04<<0),
	TWIM_RESULT_NACK_RECEIVED    = (0x05<<0),
	TWIM_RESULT_FAIL             = (0x06<<0),
} TWIM_RESULT_t;

/*! Buffer size defines */
#define TWIM_WRITE_BUFFER_SIZE         8
#define TWIM_READ_BUFFER_SIZE          8

/*! \brief TWI master driver struct
 *
 *  TWI master struct. Holds pointer to TWI module,
 *  buffers and necessary varibles.
 */
typedef struct TWI_Master 
{
	TWI_t *interface;								/*!< Pointer to what interface to use */
	register8_t address;                            /*!< Slave address */
	register8_t writeData[TWIM_WRITE_BUFFER_SIZE];  /*!< Data to write */
	register8_t readData[TWIM_READ_BUFFER_SIZE];    /*!< Read data */
	register8_t bytesToWrite;                       /*!< Number of bytes to write */
	register8_t bytesToRead;                        /*!< Number of bytes to read */
	register8_t bytesWritten;                       /*!< Number of bytes written */
	register8_t bytesRead;                          /*!< Number of bytes read */
	register8_t status;                             /*!< Status of transaction */
	register8_t result;                             /*!< Result of transaction */
}TWI_Master_t;

void TWI_MasterInit(TWI_Master_t *twi, TWI_t *module, TWI_MASTER_INTLVL_t intLevel, uint8_t baudRateRegisterSetting);
void TWI_MasterInterruptHandler(TWI_Master_t *twi);
void TWI_MasterArbitrationLostBusErrorHandler(TWI_Master_t *twi);
void TWI_MasterWriteHandler(TWI_Master_t *twi);
void TWI_MasterReadHandler(TWI_Master_t *twi);
void TWI_MasterTransactionFinished(TWI_Master_t *twi, uint8_t result);

TWI_MASTER_BUSSTATE_t TWI_MasterState(TWI_Master_t *twi);

TWIM_RESULT_t TWI_MasterReady(TWI_Master_t *twi);
TWIM_RESULT_t TWI_MasterWrite(TWI_Master_t *twi,  uint8_t address, uint8_t * writeData, uint8_t bytesToWrite);
TWIM_RESULT_t TWI_MasterRead(TWI_Master_t *twi, uint8_t address, uint8_t bytesToRead);
TWIM_RESULT_t TWI_MasterWriteRead(TWI_Master_t *twi, uint8_t address, uint8_t *writeData, uint8_t bytesToWrite, uint8_t bytesToRead);

/*! TWI master interrupt service routine.
 *
 *  Interrupt service routine for the TWI master. Copy the needed vectors
 *  into your code.
 *
    ISR(TWIE_TWIM_vect)
    {
      TWI_MasterInterruptHandler(&twiMaster);
    }
 *
 */

#endif /* I2C_H_ */