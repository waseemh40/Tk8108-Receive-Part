
#ifndef SRC_RADIO_H_
#define SRC_RADIO_H_

#include "radio_reg_map.h"
#include "spi.h"
#include "pinmap.h"
#include "delay.h"
#include "rs232.h"

	/*
	 * LoRa engine register values for desired settings
	 */
		//LoRa modes
#define SLEEP_MODE				0x80
#define STDBY_MODE				0x81
#define TX_MODE					0x83
#define RX_CONTINUOUS_MODE		0x85
#define RX_SINGLE_MODE			0x86
		//RF Frequency (869.85 MHz)
#define FC_MSB					0xD9
#define FC_MIB					0x76
#define FC_LSB					0x67
#define Fc						868.3 	//(in MHz)
		//RF output power
#define	PA_7dBm					0x08
#define	PA_13dBm				0x0E
#define	PA_20dBm				0x8F	//18dBm or max...
		//PA Ramp time
#define	PA_RAMP_TIME			0x08	//50usec
		//LNA settings
#define LNA_GAIN_DEFAULT		0x23	//maximum gain, default LNA current
#define IRQ_ENABLE				0x37	//RxTimeout, RxDone and TxDone enabled
		//Modem configurations
#define	COFNFIG_SETTINGS_1		0x72	//BW=125KHz, CR=1(4/5), Explicit Header
#define	COFNFIG_SETTINGS_2		0x74	//SF=7, CRC on, RxTimeoutMSB=0
#define	COFNFIG_SETTINGS_3		0x04	//AGC for LNA
#define RX_TIMEOUT				0xff
		//Packet settings
#define	PREAMBLE_LENGTH			0x08	//Actual length=12.25 symbols
#define PAYLOAD_LENGTH			0x0A	//50=32;200=C8;242=F2
#define	MAX_PAYLOAD_LENGTH		0x40
		//RF end settings
#define	INVERT_IQ				0x67
		//Public/private WAN
#define	SYNCH_WORD				0x12
		//DIO Mapping
#define	DIO_RX_MAPPING			0x00
#define	DIO_TX_MAPPING			0x40
	/*
	 * FIFO base addresses
	 */
#define TX_BASE_ADDRESS			0x80
#define RX_BASE_ADDRESS			0x0a

/*
 * public variables
 */

/*
 * private functions
 */
void 			write_fifo(unsigned char *data, uint8_t size);
void 			read_fifo(uint8_t size,unsigned char *data);
void 			write_reg(uint8_t addr, uint8_t cmd);
uint8_t 		read_reg(uint8_t addr);
uint8_t 		get_package(unsigned char *RFM_Rx_Package);
/*
 * public functions
 */
uint8_t			RFM_Init(void);
void 			RFM_on(void);
void 			RFM_off(void);
void 			RFM_Send_Package(unsigned char  *RFM_Tx_Package,
				uint8_t Package_Length);
uint8_t 		RFM_Receive(unsigned char  *RFM_Rx_Package);

#endif /* SRC_RADIO_H_ */
