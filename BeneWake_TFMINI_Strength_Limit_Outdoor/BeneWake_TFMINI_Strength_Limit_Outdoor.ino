
/*
TFMINI SIGNAL CONDITIONNING AND FILTERING FOE CLOSE RANGE
uint16_t strLimit = 1175;
uint16_t distLow = 465; 
uint16_t offset = 90;
Are determined experimentally by moving a reflective surface (colors cardboard) closer to sensor

uint16_t scale = 10; is adjusted according to sensor scaling == mm or cm output
*/
 
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX

uint8_t Framereceived[9];
uint8_t index;
uint16_t distance;
uint16_t offset = 0;
uint16_t scale = 1;
uint16_t strength;
uint16_t strLimit = 10;
uint16_t distLow = 46; 
uint16_t OutdoorMax = 700;

uint8_t Checksum(uint8_t *data, uint8_t length)
 {
     uint16_t  count;
     uint16_t  Sum = 0;
     
     for (count = 0; count < length; count++)
         Sum = Sum + data[count];
     return (Sum); 
 }

/* READ BINARY MODE 
Send this command for pix format(ascii x.xx cr-lf) output is 42 57 02 00 00 00 04 06
Send this command for standard output is   42 57 02 00 00 00 01 06 

Standard output= 
Byte1-2   Byte3   Byte4   Byte5     Byte6     Byte7     Byte8    Byte9
0x59 59   Dist_L  Dist_H  Strength_L  Strength_H   Reserved   Raw.Qual  CheckSum_
*/

void readlaser(){     
  if (mySerial.available() > 0) {
      uint8_t inChar = mySerial.read();
       if((inChar=='Y')&& (index==0)){
        Framereceived[index]=inChar;
        index++;
       }
       else{
         if( Framereceived[0]=='Y'){
          if(index<8){
            Framereceived[index]=inChar;
            index++;
          }
          else{
             Framereceived[index]=inChar;
             if( Framereceived[1]=='Y'){
              if(Checksum(Framereceived, 8)==Framereceived[8]){
              distance= (uint16_t)(Framereceived[2] + (Framereceived[3]*256));
              strength = (uint16_t)(Framereceived[4] + (Framereceived[5]*256));
              //Serial.print(distance);
              //Serial.print("   -   ");
              //Serial.print(strength);
              //Serial.println();             

                if ( (strength < strLimit) && (distance <= distLow ))  {
                  distance = OutdoorMax;
                    }   
                      
                    distance = constrain(distance, 14, 700);                    
                    distance = ((distance - offset)/scale); 
                    //Serial.print(strength);
                    //Serial.print("   -   ");
                    Serial.println(distance);
                   } 
                    
               }           
             for(uint8_t i=0;i<9;i++){
             Framereceived[i]=0;
             }
            index=0;
          }
       }
    }
  }

}

void setup() {
 Serial.begin(115200);
 mySerial.begin(115200);
 index=0;
 distance=0;
 strength=0;
}


void loop() {

 readlaser();
 //delay(100);

    
      
    
}


