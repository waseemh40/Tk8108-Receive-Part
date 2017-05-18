/*
 * radio_reg_map.h
 *
 *  Created on: Apr 11, 2017
 *      Author: waseemh
 */

#ifndef SRC_RADIO_REG_MAP_H_
#define SRC_RADIO_REG_MAP_H_

/*
 * write mode addresses
 */
#define 	OP_MODE_W			0x81
#define 	PA_RAMP_W			0x8A
#define 	MODEM_CONFIG1_W		0x9D
#define 	MODEM_CONFIG2_W		0x9E
#define 	TEST_W				0xB9
/*
 * read mode addresses
 */
#define 	OP_MODE_R			0x01
#define 	PA_RAMP_R			0x0A
#define 	MODEM_CONFIG1_R		0x1D
#define 	MODEM_CONFIG2_R		0x1E
#define 	TEST_R				0x39
#define 	VERSION				0x42		//device version should be 0x22...

#endif /* SRC_RADIO_REG_MAP_H_ */
