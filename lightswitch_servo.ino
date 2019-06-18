#include <Servo.h>  
#include <IRremote.h>

#define MY_PROTOCOL NEC
#define RIGHT_ARROW 0xFF02FD
#define LEFT_ARROW 0xFF22DD

IRrecv myReceiver(22); //pin that receiver is set on 
decode_results results;


Servo myServo;
int16_t pos;      // variable to store the servo position
int16_t Speed;    // Number of degrees to move each time a button (left/right) is pressed
uint32_t Previous; // Hangles NEC repeat codes


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myServo.attach(23);
  Speed = 90 ;
  pos = 0;
  myServo.write(0);
  myReceiver.enableIRIn();
  myReceiver.blink13(true);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (myReceiver.decode(&results)){
    if (results.decode_type == NEC){
      Serial.print("NEC: ");
      
    //else if (results.decode_type == SONY){
      //  Serial.print("SONY: ");}
    //else if (results.decode_type == UNKNOWN){
      //    Serial.print("UNKNOWN: ")
       // } 
    switch (results.value){
        case RIGHT_ARROW: pos = min(180, pos + Speed); break;
        case LEFT_ARROW: pos = max(0, pos - Speed); break;
      }

      
      myServo.write(pos);
      //Serial.print(pos);
      Previous = results.value;

    }

    else if (results.decode_type == UNKNOWN){
      Serial.print("UNKNOWN: ");
    }
      Serial.println(results.value, HEX);
      myReceiver.resume();
  }

  
}
