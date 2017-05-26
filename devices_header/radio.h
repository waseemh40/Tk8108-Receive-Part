
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
#define RX_MODE					0x85
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
#define	SYNCH_WORD				0x34
		//DIO Mapping
#define	DIO_RX_MAPPING			0x00
#define	DIO_TX_MAPPING			0x40
	/*
	 * FIFO base addresses
	 */
#define TX_BASE_ADDRESS			0x80
#define RX_BASE_ADDRESS			0x00

typedef enum{
	radio_sleep_mode=0,
	radio_tx_mode,
	radio_rx_mode,
	radio_standby_mode,
}radio_mode_t;
/*
 * public variables
 */


/*
 * private functions
 */
void 			write_fifo(uint8_t *data, uint8_t size);
uint8_t* 		read_fifo(uint8_t size);
void 			write_cmd(uint8_t addr, uint8_t cmd);
uint8_t 		read_cmd(uint8_t addr);
void 			change_mode(radio_mode_t radio_mode);
/*
 * public functions
 */
uint8_t			radio_init(radio_mode_t radio_mode);
void 			radio_on(void);
void 			radio_off(void);
void 			radio_transmit_string(uint8_t *tx_buf, uint8_t size);
uint8_t 		radio_rx_string(void);
uint8_t 		RFM_Get_Package(uint8_t *RFM_Rx_Package);
#endif /* SRC_RADIO_H_ */
