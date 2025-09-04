/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 https://docs.arduino.cc/learn/electronics/lcd-displays

*/

// include the library code:
#include <LiquidCrystal.h>



unsigned long startTime=micros();
unsigned long endTime=0;
unsigned long due=0;
unsigned long due2=0;
unsigned long due_p=0;
unsigned long endTime2=0;
int mess=0;
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to

const int trigPin = 24;
const int echoPin = 21;
double pk = 1.0;
int itr=0;
double s = 0.0;
double kk = 0.0;
double res = 0.0;
float duration, distance;
float du[10];
int i=0;
int update=0;
const int rs = 50, en = 52, d4 = 38, d5 = 36, d6 = 34, d7 = 32;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


double kalman_f(double z){
    double f = 1.0;
    double q = 0.5;
    double r = 0.1;
    double h = 1.0;
    pk = f * pk * f + q;
    s = r + h * pk * h;
    kk = (pk * h) / s;
    pk = (1 - kk * h) * pk;
    res = f * res + kk * (z - h * f * res);
    return res;

}
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(echoPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(echoPin), blink, CHANGE);

  pinMode(trigPin, OUTPUT);
  
  // Print a message to the LCD.
  
  lcd.print("Distance in cm");
}

void loop() {
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(2);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(10);
    digitalWrite(trigPin, HIGH);
    
   
    
   
  
  if (update==1){
  if (itr==10){
   
    
    lcd.setCursor(0, 1);
  // print the number of seconds since reset:
    lcd.print(kalman_f(((due)*.0343)/4));
    itr=0;
  }
  else{
      itr++;
      delay(100);

  }
  update=0;
  }
}

  void blink(){
     if((digitalRead(echoPin)==HIGH)&&(mess==0)){
      startTime = micros();
     }else{
    
       endTime2=micros();
      
       due2=startTime-endTime2;
     
     if ((due2-due_p)<20){
      due=due2+due_p;
      mess=1;
     }else{
     due_p=due;
     update=1;
     mess=0;
     }
     }
  }
  
 
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):


