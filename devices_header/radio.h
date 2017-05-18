/*
 * radio.h
 *
 *  Created on: Apr 11, 2017
 *      Author: waseemh
 */

#ifndef SRC_RADIO_H_
#define SRC_RADIO_H_

#include "spi.h"
#include "pinmap.h"
#include "radio_reg_map.h"
#include "delay.h"
/*
 * public variables
 */

/*
 * private functions
 */

/*
 * public functions
 */
void 		radio_init(void);
void 		radio_on(void);
void 		radio_off(void);
void 		radio_tx_string(char *msg);
void 		radio_write_cmd(uint8_t addr, uint8_t cmd);
uint8_t 	radio_read_cmd(uint8_t addr);

#endif /* SRC_RADIO_H_ */
