/*
 * time_manager.c
 *
 *  Created on: Apr 7, 2017
 *      Author: waseemh
 */

#include "time_manager.h"
/*
 * private variables
 */
static int 						time_count=0;
static time_manager_cmd_t 		time_manager_cmd=basic_sync;
static uint32_t 				interruptMask=0;

/*
 * public variables
 */
/*
 * private functions
 */
/*
 * public functions
 */
void 		time_manager_init(void){
	//GPIO_PinModeSet(GPS_SIG_PORT, GPS_INT, gpioModeInput, 0);
	GPIO_PinModeSet(GPS_SIG_PORT, GPS_TIME_PULSE, gpioModeInput, 0);
	GPIO_IntConfig(GPS_SIG_PORT,GPS_TIME_PULSE,true,false,true);
	//GPIO_IntConfig(GPS_SIG_PORT,GPS_INT,true,false,false);
	GPIO_IntClear(_GPIO_IF_MASK);
	//GPIO_IntEnable();
    NVIC_EnableIRQ(TIME_MANAGER_IRQn);
    return;
}
time_manager_cmd_t 		time_manager_get_cmd(void){
	return time_manager_cmd;
}

unsigned long 		time_manager_unixTimestamp(int year, int month, int day,
              int hour, int min, int sec)
{
  const short days_since_beginning_of_year[12] = {0,31,59,90,120,151,181,212,243,273,304,334};

  int leap_years = ((year-1)-1968)/4
                  - ((year-1)-1900)/100
                  + ((year-1)-1600)/400;

  long days_since_1970 = (year-1970)*365 + leap_years
                      + days_since_beginning_of_year[month-1] + day-1;

  if ( (month>2) && (year%4==0 && (year%100!=0 || year%400==0)) )
    days_since_1970 += 1; /* +leap day, if year is a leap year */

  return sec + 60 * ( min + 60 * (hour + 24*days_since_1970) );
}
/*
 * ISRs
 */
void 	TIME_MANAGER_ISR(){

	 interruptMask = GPIO_IntGetEnabled();
     GPIO_IntClear(interruptMask);
     time_count++;
	 time_manager_cmd=basic_sync;
     if(time_count%(BASIC_SYNCH_SECONDS)==0 && time_count!=ADVANCE_SYNCH_SECONDS){	//60
         SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;
     }
     if(time_count==ADVANCE_SYNCH_SECONDS){
    	 time_manager_cmd=advance_sync;
    	 time_count=0;
         SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;
     }
}
