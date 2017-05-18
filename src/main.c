#include "app_manager.h"
#include "time_manager.h"


int main() {
	 /*
	  ********************* Chip initialization*************
	  */
			CHIP_Init();
			CMU_HFRCOBandSet(cmuHFRCOBand_7MHz );
			CMU_OscillatorEnable(cmuOsc_HFRCO, true, true);
			CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFRCO);
	 /*
	  *******************************************************
	  */
	bool								flag=false;
	const unsigned char  				rs232_tx_buf[64];
	time_manager_cmd_t					time_manager_cmd=basic_sync;
	nav_data_t	 						nav_data;

	flag=app_manager_init();
	if(flag){
		sprintf((char *)rs232_tx_buf,"\tApp Manager Init Successful\t\n");
		rs232_transmit_string((unsigned char *)rs232_tx_buf,strlen((const char *)rs232_tx_buf));
	}
	else{
		sprintf((char *)rs232_tx_buf,"\tApp Manager Init Failed...\t\n");
		 rs232_transmit_string(rs232_tx_buf,strlen((const char *)rs232_tx_buf));
		 rgb_on(true,false,false);
		 return 0;
	}
	time_manager_init();
  while(1) {
	  SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
	  EMU_EnterEM1();
	  time_manager_cmd=time_manager_get_cmd();
	  if(time_manager_cmd==advance_sync) {
		  nav_data=app_manager_get_nav_data();
		  nav_data.gps_timestamp=time_manager_unixTimestamp(nav_data.year,nav_data.month,nav_data.day,
															nav_data.hour,nav_data.min,nav_data.sec);
	  }
	  app_manager_tbr_synch_msg(time_manager_cmd,nav_data);
   }
}
