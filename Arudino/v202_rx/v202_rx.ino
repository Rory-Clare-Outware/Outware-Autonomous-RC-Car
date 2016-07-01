/* v202_rx.ino -- An arduino sketch to test the protocol v202
 *
 * Copyright (C) 2016 execuc
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

//NOTE: Bind the controller after the code is running on the arduino

#include <SPI.h>
#include "v202_protocol.h"

nrf24l01p wireless; 
v202Protocol protocol;

unsigned long time = 0;
 
// the setup routine runs once when you press reset:
void setup() {
  // SS pin must be set as output to set SPI to master !
  pinMode(SS, OUTPUT);
  Serial.begin(115200);
  // Set CE pin to D8 (D9) and CS pin to D7 (D53)
  wireless.setPins(9, 53);
  protocol.init(&wireless);
  
  time = micros();
  Serial.println("Start");
}

rx_values_t rxValues;

bool bind_in_progress = false;
unsigned long newTime;

void loop() 
{
  time = micros();
  uint8_t value = protocol.run(&rxValues); 
  newTime = micros();
   
  switch( value )
  {
    case  BIND_IN_PROGRESS:
      if(!bind_in_progress)
      {
        bind_in_progress = true;
        Serial.println("Bind in progress");
      }
    break;
    
    case BOUND_NEW_VALUES:
      //newTime = micros();
      /*Serial.print(newTime - time); //120 ms for 16 Mhz
      Serial.print(" :\t");Serial.print(rxValues.throttle);
      Serial.print("\t"); Serial.print(rxValues.yaw);
      Serial.print("\t"); Serial.print(rxValues.pitch);
      Serial.print("\t"); Serial.print(rxValues.roll);
      Serial.print("\t"); Serial.print(rxValues.trim_yaw);
      Serial.print("\t"); Serial.print(rxValues.trim_pitch);
      Serial.print("\t"); Serial.print(rxValues.trim_roll);
      Serial.print("\t"); Serial.print(rxValues.flags);
      Serial.print("\t"); Serial.println(rxValues.crc);*/
      //time = newTime;

      
      Serial.print(newTime - time); //120 ms for 16 Mhz (currently showing as 180ms)
      Serial.print(" :\t");Serial.print(rxValues.throttle);
      Serial.print("\t Steer:"); Serial.print(rxValues.yaw);
      Serial.print("\t Throttle:"); Serial.print(rxValues.pitch);
      Serial.print("\t"); Serial.print(rxValues.roll);
      Serial.print("\t ST Trim:"); Serial.print(rxValues.trim_yaw);
      Serial.print("\t TH Trim:"); Serial.print(rxValues.trim_pitch);
      Serial.print("\t ?:"); Serial.print(rxValues.trim_roll);
      Serial.print("\t"); Serial.print(rxValues.flags);
      Serial.print("\t CRC:"); Serial.println(rxValues.crc);
      
    break;
    
    case BOUND_NO_VALUES:
      //Serial.print(newTime - time); Serial.println(" : ----"); // 32ms for 16Mhz
    break;

    case ERROR_SIGNAL_LOST:
	    //Serial.print(newTime - time); Serial.println(" : ----");
    break;
    
    default:
    break;
  }
  delay(2);
}
