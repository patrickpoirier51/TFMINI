# TFMINI 
Signal conditionning and Filtering for use in close range

This range finder has a bad reading behavior (< 30cm) making the false signal jump to larger values (over 60cm)

Refer to image BENEWAKE_Dist_Strength_Filtered.jpg for more details.




BeneWake_TFMINI_CRC_Strength.ino

This program reads the binary message in this format
Byte1-2   Byte3   Byte4   Byte5     Byte6     Byte7     Byte8    Byte9
0x59 59   Dist_L  Dist_H  Strength_L  Strength_H   Reserved   Raw.Qual  CheckSum_

Extract the Distance and Signal Strength values and apply some filtering in order to use 
use the ranges finder as a distance measurement unit for landing a quadcopter under ArduPilot

The values of:
uint16_t strLimit = 1175;
uint16_t distLow = 465; 
uint16_t offset = 90;
Are determined experimentally by moving a reflective surface (colors cardboard) closer to sensor

uint16_t scale = 10; is adjusted according to sensor scaling == mm or cm output

Filtered serial output is sent @ 155200 baud to the flight controler and is consumed using the LightWare Serial driver.
SERIAL4_PROTOCOL = 9 (Lidar)
SERIAL4_BAUD = 115
RNGFND_TYPE = 8 (LightWareSerial)
RNGFND_SCALING = 1
RNGFND_MIN_CM = 5
RNGFND_MAX_CM = 1200
RNGFND_GNDCLEAR = 15  //This is the minimal value set by the Arduino filter (240-90= 150mm = 15cm)
