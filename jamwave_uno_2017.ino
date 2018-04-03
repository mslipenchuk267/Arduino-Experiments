
#include <SoftwareSerial.h>
SoftwareSerial BTserial(0, 1); // RX | TX
int incomingAudio;

void setup(){
  BTserial.begin(115200);
  cli();//disable interrupts
  
  //set up continuous sampling of analog pin 0
  
  //clear ADCSRA and ADCSRB registers
  ADCSRA = 0;
  ADCSRB = 0;
  
  ADMUX |= (1 << REFS0); //set reference voltage
  ADMUX |= (1 << ADLAR); //left align the ADC value- so we can read highest 8 bits from ADCH register only
  
  ADCSRA |= (1 << ADPS2) | (1 << ADPS0); //set ADC clock with 32 prescaler- 16mHz/32=500kHz
  ADCSRA |= (1 << ADATE); //enabble auto trigger
  ADCSRA |= (1 << ADIE); //enable interrupts when measurement complete
  ADCSRA |= (1 << ADEN); //enable ADC
  ADCSRA |= (1 << ADSC); //start ADC measurements
  
  sei();//enable interrupts

  //if you want to add other things to setup(), do it here

}

ISR(ADC_vect) {//when new ADC value ready
  incomingAudio = ADCH;//update the variable incomingAudio with new value from A0 (between 0 and 255)
}

void loop(){
BTserial.print(incomingAudio);
}


