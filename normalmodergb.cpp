#include "common.h"

extern uint8_t rgbcolor;

void normalmodergb_callback(){
  while(true){
    if(current_mode == NORMAL_MODE){
      
    }
    else
      event_flags.wait_any(NORMAL_MODE);
  }
}