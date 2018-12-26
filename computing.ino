#include <Arduino.h>
#include <math.h>
#define mega
#ifdef due
  #include <variant.h>
#endif

void setup(){
Serial.begin(9600);
pinMode(7,OUTPUT);
  for(int i=2;i<=53;i++){
    pinMode(i,OUTPUT);
  }
}
 long int a;
void loop() {
  a=micros();
  for(int i=2;i<=53;i++)
   SET(i);
//  digitalWrite(i,HIGH);
  Serial.println( micros() - a); 
}
//_______________________________________________ARDUINO DUE________________________________________________________________

#ifdef due
void SET(int digitalPin)
{
  Pio* Port = g_APinDescription[digitalPin].pPort; 
    unsigned int pin = g_APinDescription[digitalPin].ulPin;
    Port ->PIO_SODR =  pin ;
}

void CLEAR(int digitalPin)
{
  Pio* Port = g_APinDescription[digitalPin].pPort; 
    unsigned int pin = g_APinDescription[digitalPin].ulPin;
    Port ->PIO_CODR =  pin ;
}
// SET Time period 53 pins= 24 microseconds
//digitalWrite Time period 53 pins = 118 microseconds
#endif


//______________________________________________ARDUINO UNO MEGA etc_________________________________________________

#ifdef mega
void SET(uint8_t x){

    uint8_t port = digitalPinToPort(x);
    uint8_t pin =  digitalPinToBitMask(x);
    volatile uint8_t *output = portOutputRegister(port);
    
    uint8_t oldSREG = SREG;
    cli();
    *output |= pin;
    SREG = oldSREG;     
}

void CLEAR(uint8_t x){
    uint8_t port = digitalPinToPort(x);
    uint8_t pin =  digitalPinToBitMask(x);
    volatile uint8_t *output = portOutputRegister(port);
    
    uint8_t oldSREG = SREG;
    cli();
    *output |= pin;
    SREG = oldSREG;  
}
#endif
//digitalWrite Time Period = 216 microseconds
//SET Time Period = 120 micro seconds
