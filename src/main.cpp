#include <Arduino.h>

int count;
int jam, menit, detik;
int jam_awal=0,
    menit_awal=0,
    detik_awal;

void setup() {
Serial.println("integrating with github");
//=====================================Timer Init===================================================
  cli(); //disable interrupt



  //set timer0 8bit
  TCCR0A = 0;
  TCCR0B = 0;
  TCNT0 = 0; //counter value

  //Set Compare Match Register
  OCR0A = 124; //asumsi (16*10^6)/(2000*64)-1 (harus dibawah 255, asumsi dengan prescaler 2kHz)

  //Turn on CTC mode
  TCCR0A |= (1<< WGM01);
  // Set CS01 and CS00 bits for 64 prescaler
  TCCR0B |= (1 << CS01) | (1 << CS00);
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);


  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei(); //allows interrupt

//=================================================================================================

Serial.begin(9600);

  jam = jam_awal + jam;
  menit = menit_awal + menit;
  detik = detik_awal + detik;
}

ISR(TIMER0_COMPA_vect){
//Serial.println("-"); cek vcs
}

ISR(TIMER1_COMPA_vect){
//  Serial.println(count);

  count++;
  detik = count;

  if(count == 60){
    count = 0;
    menit++;
  }

  if(menit == 60){
    menit = 0;
    jam++;
  }

  if(jam == 12){
    jam = 0;
  }

  Serial.print(jam);Serial.print(" : ");Serial.print(menit);Serial.print(" : ");Serial.println(detik);

}


void loop() {


}
