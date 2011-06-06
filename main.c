/*
  main.c - An embedded CNC Controller with rs274/ngc (g-code) support
  Part of Grbl

  Copyright (c) 2009-2011 Simen Svale Skogsrud

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include "planner.h"
#include "stepper.h"
#include "spindle_control.h"
#include "motion_control.h"
#include "gcode.h"
#include "serial_protocol.h"
#include "nuts_bolts.h"
#include "settings.h"
#include "wiring_serial.h"
#include "config.h"
#include "lcd.h"
#include <math.h>
#include <avr/pgmspace.h>

// #ifndef __AVR_ATmega328P__
// #  error "As of version 0.6 Grbl only supports atmega328p. If you want to run Grbl on an 168 check out 0.51 ('git co v0_51')"
// #endif

int main(void)
{
char print1[50];
  sp_init();      
  settings_init();  
  plan_init();
  st_init(); 
  spindle_init();   
  lcd_cnc_init();
  gc_init();  
  
  for(;;){
    sleep_mode(); // Wait for it ...
    sp_process(); // ... process the serial protocol
    
    /* Not sure if this will work, but trying anyway */
    //sprintf(print1, "X%f.3, Y%f.3, Z%f.3",(double)target[X_AXIS],(double)target[Y_AXIS],(double)target[Z_AXIS]); 
    lcd_set_line(2);                        // sets the screen position, line 3
    lcd_write_line(print1);
  }
  return 0;   /* never reached */
}
