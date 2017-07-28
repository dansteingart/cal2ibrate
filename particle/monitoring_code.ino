// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_Si7021.h>


Adafruit_Si7021 sensor = Adafruit_Si7021();

//       Serial.print("Humidity:    "); Serial.print(sensor.readHumidity(), 2);
//   Serial.print("\tTemperature: "); Serial.println(sensor.readTemperature(), 2);
//   delay(100);



//Simple Base Code for MAE 221 Fall 2016 Final Project
//This code allows for all ports to be read simultaneously, while setting points one at a time or all at once
//Send all port values as a nice json value to the "big_brother" variable
#include "math.h"

char publishString[200]; //a place holer for the publish string
int waiter = 10000; //in ms
int samps = 50; //sampler counter for smooth smoothness


void setup() //run this loop just once upon start, or upon reset
{
  //We'll use these to send the digital state
  Particle.function("setOutput", setOutput);
  Particle.function("setOutputs", setOutputs);


  sensor.begin();

  //set analog pins to input mode
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
  
  //set digital pins not used by MAX31855 (4,5,6) to output mode
  pinMode(D2, OUTPUT);
  pinMode(D3, INPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT); //led
  

  pinMode(D3, INPUT);
  digitalWrite(D4,HIGH);
  digitalWrite(D2,LOW);

}

void loop() //repeat this loop forever
{
    digitalWrite(7,1);
    //declare pin labels as integers
    int a0 = 0;
    int a1 = 0;
    int a2 = 0;
    int a3 = 0;
    int a4 = 0;
    int a5 = 0;
    int a6 = 0;
    int a7 = 0;
    
    int d2;
    int d3;
    int d4;
    int d5;
    int d6;

    //average the readings at each port for stability
    for (int j = 0; j < samps; j++) //sum values samps times
   {
     a0 += analogRead(A0);  
     a1 += analogRead(A1);  
     a2 += analogRead(A2);    
     a3 += analogRead(A3);  
     a4 += analogRead(A4);  
     a5 += analogRead(A5);  
     a6 += analogRead(A6);  
     a7 += analogRead(A7);
     
   }

    // take the average
    a0 = a0/samps;
    a1 = a1/samps;
    a2 = a2/samps;
    a3 = a3/samps;
    a4 = a4/samps;
    a5 = a5/samps;
    a6 = a6/samps;
    a7 = a7/samps;
    
    d2 = digitalRead(2);
    d3 = digitalRead(3);
    d4 = digitalRead(4);
    d5 = digitalRead(5);
    d6 = digitalRead(6);
    
    double T = sensor.readTemperature();
    double H = sensor.readHumidity();
    
    //wait countto clicks before sending publish data; blink the led every X to let us know how hard it's working
    sprintf(publishString,"{\"a0\": %d, \"a1\": %d, \"a2\": %d,\"a3\": %d,\"a4\": %d,\"a5\": %d,\"a6\": %d,\"a7\": %d,\"T\": %f,\"H\": %f,\"d2\": %d,\"d3\": %d}",a0,a1,a2,a3,a4,a5,a6,a7,T,H,d2,d3);
    //sprintf(publishString,"{\"T\": %d,\"H\": %d}",T,H);
    Particle.publish("pleesr_state",publishString);

    digitalWrite(7,0);

    delay(waiter);

}

//set one input
int setOutput(String potter)
{
  //break the input string down into two parts.  1st in the bit to control, second is the value.  e.g. 41 means 'pin 4 high', 30 means 'pin 3 low'
  digitalWrite(potter.charAt(0)-48,potter.charAt(1)-48); //subtract 48 to make sense of ascii (i.e. ascii(48) = 0)
  return potter.toInt();
}

//set all inputs at once
int setOutputs(String potter)
{
  //break the input string down into bit parts, update all.  e.g. 1001 sets 0 and 3 high, 1 and 2 low
  digitalWrite(0,potter.charAt(0)-48); //subtract 48 to make sense of ascii (i.e. ascii(48) = 0)
  digitalWrite(1,potter.charAt(1)-48); //subtract 48 to make sense of ascii (i.e. ascii(48) = 0)
  digitalWrite(2,potter.charAt(2)-48); //subtract 48 to make sense of ascii (i.e. ascii(48) = 0)
  digitalWrite(3,potter.charAt(3)-48); //subtract 48 to make sense of ascii (i.e. ascii(48) = 0)
  return potter.charAt(0);
}


