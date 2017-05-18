/*
 * app_manager.h
 *
 *  Created on: May 2, 2017
 *      Author: waseemh
 */

#ifndef SRC_APP_MANAGER_H_
#define SRC_APP_MANAGER_H_

#include "delay.h"
#include "rgb_led.h"
#include "tbr.h"
#include "rs232.h"
#include "ublox_gps.h"
#include "radio.h"
#include "ff.h"
#include "diskio.h"


#define WRITE_SIZE		25
#define INIT_RETRIES	10

	/*
	 * shared variables
	 */

	/*
	 * private functions
	 */
bool 			file_sys_setup(uint16_t year,uint8_t date,uint8_t day,
											char buf[]);
bool 			tbr_cmd_update_rgb_led(tbr_cmd_t tbr_cmd, time_t timestamp);
	/*
	 * public functions
	 */
bool 			app_manager_init(void);
void 			app_manager_tbr_synch_msg(uint8_t time_manager_cmd, nav_data_t nav_data);
nav_data_t 		app_manager_get_nav_data(void);

#endif /* SRC_APP_MANAGER_H_ */
