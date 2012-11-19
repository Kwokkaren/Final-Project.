/*
    Arduino Project
 Jesse Karen Yucas
 a living room control using Pressure Sensor on the chair  
 Control a lamp,fan, TV and blinder using a pressure sensor.
 */

int dimmer = 9;   //dimmer servor pin
int motorPin1 =  5;    // One motor wire connected to digital pin 5
int motorPin2 =  6;    // One motor wire connected to digital pin 6
int prevState = 0;
int currentState = 0;
int fadeAmount=4;
int brightness=100;


#include <Servo.h>;
#include <IRremote.h>

IRsend irsend;
Servo myservo;
int pos = 0;  // Variable to store the servo position 
const int yPin = 2; // accelorometer pin to measure the angle of the back

//The minimum and maximum values that came from
//the accelerometer while standing still
int minVal = 265;
int maxVal = 402;
double y;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  myservo.attach(9);
  pinMode(dimmer, OUTPUT);  
  Serial.begin(9600);
}


// the loop routine runs over and over again forever:
void loop() {
  int i;
  int yRead = analogRead(yPin); // input analog value of the accelerometer 
  int yAng = map(yRead, minVal, maxVal, -90, 90);
  Serial.println( yAng);


  int sensorValue1 = analogRead(A0); //input analog value of pressure sensor on the chair
  int sensorValue2= analogRead(A1); // input analog value of pressure sensor on the leg rest
  // print out the value you read:
  Serial.println(sensorValue1);
  Serial.println(sensorValue2);

  // if (sensorValue1 ==0&&sensorValue2==0&&yAng>95 ){
  //    myservo.write(0);
  //     Serial.println(" waiting");
  // }
  if (sensorValue1 >=25 && sensorValue2 <2 && yAng>=220 ) { //state 1: when someone is sitting on the chair
    currentState=1;
    if(currentState!=prevState){
      Serial.println(" sat");
      myservo.write(179);
      /* irsend.sendNEC(0xFF906F,32);// BUTTON 1
       analogWrite(motorPin2, 1500); //rotates motor
       digitalWrite(motorPin1, LOW);    // set the Pin motorPin2 LOW
       delay(8000); //waits
       digitalWrite(motorPin2, LOW); 
       delay(100);}
       */    }
    else{
      Serial.println("still sitting");

    }
    prevState=currentState;    
    delay(100); 
  } 

  else if (sensorValue1 >=25 && sensorValue2 >=2 && yAng >=220){  //state 2: when someone is sitting with the leg rest
    currentState=2;
    if(currentState!=prevState){
      Serial.println (" leg rest ");
      myservo.write(80);
      //   irsend.sendNEC(0xFFA05F,32);    
      delay(100);
    }

    else{
      Serial.println("leg still resting");
    } 
    prevState=currentState;  
    delay(100);
  } 

  else if (sensorValue1 >=25 &&sensorValue2>=2 && yAng<220){  //state 3: when someone is leaning at the back rest

   
   
      Serial.println(" sleeping mode ");

      for ( i=1; i<=10; i++ ) {
       // fade in from min to max in increments of 5 points:
       for(int fadeValue = 80 ; fadeValue <= 179; fadeValue +=3) { 
       // sets the value (range from 0 to 255):
       myservo.write(fadeValue);         
       // wait for 30 milliseconds to see the dimming effect    
       delay(30);}                           
       
       // fade out from max to min in increments of 5 points:
       for(int fadeValue = 179 ; fadeValue >= 80; fadeValue -=3) { 
       // sets the value (range from 0 to 255):
       myservo.write(fadeValue);         
       // wait for 30 milliseconds to see the dimming effect    
       delay(30);  
       //if (yAng>200){break;}     
       }  
       }   
       //   irsend.sendNEC(0xFF807F,32);    
       //   delay(100);
      
       
     /* analogWrite(dimmer, brightness);    

      // change the brightness for next time through the loop:
      brightness = brightness + fadeAmount;

      // reverse the direction of the fading at the ends of the fade: 
      if (brightness == 80 || brightness == 252) {
        fadeAmount = -fadeAmount ; 
      }     
      // wait for 30 milliseconds to see the dimming effect    
      delay(40); */ 

  }
  else if (sensorValue1 <25 && sensorValue2 <2 && yAng >=220){ //state0: when no one is sitting on the chair
    currentState=0;
    if(currentState!=prevState){
      Serial.println("empty chair");
      myservo.write(0);
      /*  irsend.sendNEC(0xFFAA55,32);// PAUSE
       delay(100);
       analogWrite(motorPin1, 1500); //rotates motor
       digitalWrite(motorPin2, LOW);    // set the Pin motorPin2 LOW
       delay(8000); //waits
       //digitalWrite(motorPin1, LOW); 
       //analogWrite(motorPin2, 1500); //rotates motor
       digitalWrite(motorPin1, LOW);    // set the Pin motorPin2 LOW
       delay(100); //waits
       
       */    }
    else{
      Serial.println("waiting");
      myservo.write(0);

    }
    prevState=currentState;
  }  
  delay(100);
}



