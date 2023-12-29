#define EEPROM_SIZE 64

#include <EEPROM.h>

int addr_pH_Setpoint = 0 + sizeof(float);
int addr_pH_Range = addr_pH_Setpoint + sizeof(float);
int addr_feedTime = addr_pH_Range + sizeof(int);
int addr_stopTime = addr_feedTime + sizeof(int);
int addr_stirTime = addr_stopTime + sizeof(int);
int addr_calB4 = addr_stirTime + sizeof(float);
int addr_calB7 = addr_calB4 + sizeof(float);

void EEPROM_readInit()
{
  pH_setPoint = EEPROM.readFloat(addr_pH_Setpoint);
  pH_setPoint_range = EEPROM.readFloat(addr_pH_Range);
  feed_time = EEPROM.read(addr_feedTime);
  // stop_feed_time = EEPROM.read(addr_stopTime);
  pH_calibrate_pH4 = EEPROM.readFloat(addr_calB4);
  pH_calibrate_pH7 = EEPROM.readFloat(addr_calB7);

  if (isnan(pH_setPoint))
  {
    pH_setPoint = 7.0;
  }
  if (isnan(pH_setPoint_range))
  {
    pH_setPoint_range = 0.5;
  }
  if (isnan(feed_time))
  {
    feed_time = 10;
  }
  // if(isnan(stop_feed_time))
  // {
  //   stop_feed_time = 10;
  // }
  if (isnan(pH_calibrate_pH4))
  {
    pH_calibrate_pH4 = 1300.0;
  }
  if (isnan(pH_calibrate_pH7))
  {
    pH_calibrate_pH7 = 1400.0;
  }
}

void EEPROM_savePH()
{
  EEPROM.writeFloat(addr_calB4, pH_calibrate_pH4);
  EEPROM.writeFloat(addr_calB7, pH_calibrate_pH7);
  EEPROM.commit();
}

void EEPROM_setup()
{
  EEPROM.begin(EEPROM_SIZE);
}

void EEPROM_loop()
{
  EEPROM.writeFloat(addr_pH_Setpoint, pH_setPoint);
  EEPROM.writeFloat(addr_pH_Range, pH_setPoint_range);
  EEPROM.write(addr_feedTime, feed_time);
  // EEPROM.write(addr_stopTime, stop_feed_time);
  EEPROM.commit();
}
