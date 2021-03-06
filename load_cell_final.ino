
/*Project: Aqua Drone : An unmanned water-body-garbage cleaning robot
 * Authors: Rutvij Joshi,Hrishikesh Hallur,Swaraj Tembhurne
 * Filename:Load cell + GSM final code
 */


#include "HX711.h"
#define DOUT  3
#define CLK  2

float calibration_factor = -115200; 
HX711 scale; //Create object name "scale" to use HX711.h functions

void setup() {
     
  Serial.begin(9600);
  Serial1.begin(9600); //Initialize UART0 and set baud rate to 9600
  scale.begin(DOUT, CLK); //Initialize UART1 and set baud rate to 9600
  scale.set_scale();
  scale.tare(); //Reset the scale to 0
  delay(100);
}

void send_msg()
{
  Serial1.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(500);  
  Serial1.println("AT+CMGS=\"+91x\"\r"); // Replace x with mobile number
  delay(300);
  Serial1.println("I am full");// The SMS text you want to send
  delay(300);
  Serial1.println((char)26);// ASCII code of CTRL+Z
}

void loop() {
  
  scale.set_scale(calibration_factor);
  Serial.print("Reading: ");
  float z=scale.get_units(); //Get reading
  z=(z/2.25);//Conversion from lbs to kg
  Serial.print(z);
  Serial.print(" kgs");
  if(z>1)  //Send SMS after exceeding threshold
  {
    send_msg();
    Serial.println("SMS SENT");
  }
  Serial.println();
}
