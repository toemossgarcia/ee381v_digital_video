/* Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */

#include <Encoder.h>

#define CH1_ENC1	A4
#define CH1_ENC2	A5
#define CH1_INT 	2

#define CH4_ENC1	A2
#define CH4_ENC2	A3
#define CH4_INT 	3

#define CH1_PWM		6
#define CH1_DIR		7
#define CH1_CUR		A1

#define CH2_PWM		9
#define CH2_DIR		8

#define CH3_PWM	        10
#define CH3_DIR	        11

#define CH4_PWM		5
#define CH4_DIR		12
#define CH4_CUR		A0

#define POT		A6
#define PUSHBTN		13

#define OFF		0
#define SLOW		120
#define NORM		180
#define FAST		255

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder enc1(CH1_ENC1, CH1_ENC2);
Encoder enc4(CH4_ENC1, CH4_ENC2);

//   avoid using pins with LEDs attached

void setup() {
  Serial.begin(9600);
  Serial.println("Basic Encoder Test:");

  pinMode(POT,INPUT);
  pinMode(PUSHBTN,INPUT);  

  pinMode(CH1_PWM,OUTPUT);
  pinMode(CH1_DIR,OUTPUT);
  pinMode(CH2_PWM,OUTPUT);
  pinMode(CH2_DIR,OUTPUT);
  pinMode(CH3_PWM,OUTPUT);
  pinMode(CH3_DIR,OUTPUT);
  pinMode(CH4_PWM,OUTPUT);
  pinMode(CH4_DIR,OUTPUT);  

  digitalWrite(CH1_DIR,LOW);
  digitalWrite(CH2_DIR,HIGH);
  digitalWrite(CH3_DIR,LOW);  
  digitalWrite(CH4_DIR,LOW);
}

long oldPosition  = -999;
long newPosition = -999;
long oldPosition2  = -999;
long newPosition2 = -999;
int potVal = 0;
int oldPotVal = 1;
int out = 0;
int motorDisabled = 0;
int i;

void loop() {
  if (digitalRead(PUSHBTN) == LOW)
  {
    i = 0;
    delay(200);    
    do {
      // determine the control point :p
      potVal = analogRead(POT);
      out = map(potVal, 0, 1023, 0, 255);
      /* Serial.println(i++); */
      if (out < SLOW)		out = 0;
      else if (out < NORM)	out = SLOW;
      else if (out < FAST)	out = NORM;
      else          		out = FAST;

      // set the speed
      analogWrite(CH1_PWM,out);
      analogWrite(CH2_PWM,out);
      analogWrite(CH3_PWM,out);
      analogWrite(CH4_PWM,out);
    } while(digitalRead(PUSHBTN) == HIGH);

    // turn off motors
    analogWrite(CH1_PWM,0);
    analogWrite(CH2_PWM,0);
    analogWrite(CH3_PWM,0);
    analogWrite(CH4_PWM,0);

    // wait a while to read button again
    delay(200);
  }


  newPosition = enc1.read();
  newPosition2 = enc4.read();
  if (newPosition != oldPosition)
  {
    oldPosition = newPosition;
    Serial.println(newPosition);
  }
  if (newPosition2 != oldPosition2)
  {
    oldPosition2 = newPosition2;    
    Serial.print(", "); Serial.println(newPosition2);
  }  

}