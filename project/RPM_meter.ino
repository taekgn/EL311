//Taekgeun Ji tj208@kent.ac.uk 27MAR2020

/* Imports the software serial port library */
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
/* Select the input pin for the hall effect sensors output. */   
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define NUMFLAKES     10 // Number of snowflakes in the animation example
#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
/* DIO used to communicate with the Bluetooth module's TXD pin */
#define BT_SERIAL_RX_DIO 10 
/* DIO used to communicate with the Bluetooth module's RXD pin */
#define BT_SERIAL_TX_DIO 11
/* Initialise the software serial port */
SoftwareSerial BluetoothSerial(BT_SERIAL_RX_DIO, BT_SERIAL_TX_DIO); // RX, TX
//Above codes are importing libraries to this script
int analogPin = A0; //Potentiometre  
int rotation = 0; //The number of object's rotation
int mag = 1; //The number of magnet on the object
volatile byte state = LOW; //This converts the indication of sensor to boolean state
int rpm = 0;   int Pot;   int voltlay = 3;   int hallSensorPin = 4;     int buzzer = 8;   int led = 9;   int led2nd = 13; int power = LOW;
int push = 2; //A tackle switch for freezing sceen
bool halt = true; //Boolean statement that decides operation of loop method
int condit = LOW; //Used for stating led power supplying
unsigned int previous; //Time parametre that stands for initiated time. Which's same as x_2 in denominator of derivative for only first measurement.
unsigned int collator; //It's a time parametre for differenciating rpm, which's same as x_1 in denominator of derivative
String str; //this variable is for serial communication with bluetooth module
String statement; //tells whether it's measuring or not
//Above codes are parametres and variables

void setup() {
  /* Initialise serial and DIO */
  /* Set the baud rate for the hardware serial port [Baud: a unit of transmission speed equal to the number of times a signal changes state per second.]*/
  Serial.begin(9600); //Kind o' an initialisation process opens serial port, sets data rate to 9600 bps
  /* Set the baud rate for the software serial port for bluetooth*/
  BluetoothSerial.begin(9600);

  /* If data is available from the Bluetooth module then pass it on to the 
     hardware serial port. */
  if (BluetoothSerial.available())
    Serial.write(BluetoothSerial.read());

   /* If data is available from the hardware serial port then pass it on 
      to the Bluetooth module. */
  if (Serial.available())
    BluetoothSerial.write(Serial.read());
    
   if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(500); // Pause for few seconds
  
  pinMode(voltlay,OUTPUT); //Setting up voltage relay as output
  pinMode(led, OUTPUT); //The led to indicate times of measurements
  pinMode(led2nd, OUTPUT); //The led to indicate times of measurements
  pinMode(buzzer, OUTPUT); //Notification for indication
  pinMode(hallSensorPin, INPUT); //Hall effect sensor to input data to microcontroller
  pinMode(push, INPUT); //Tackle switch to freeze screen
  pinMode(push, INPUT_PULLUP); //Tackle switch to freeze screen
  attachInterrupt(digitalPinToInterrupt(push), freezing, RISING); //Freeze the screen to hold RPM & Potentiometre value
}

void loop()
{
  while(halt == true)
  {
    //Entire codes are wrapped into while loop thus it's able to halt the ongoing process
    statement = "Activated!";
	  state = digitalRead(hallSensorPin); //Reads the digital output data from hall effect sensor
	  if (state == LOW) { 
    collator = millis(); //records the meausred time  
    condit = HIGH; //makes led to light up
    tone(buzzer, 523, 500); //Notification for indicating movement
    rotation += 1;
    statement = "Detected!";      
    rpm = (60000)/(collator - previous)*rotation/mag;
    previous = collator; //as copying collator parametre with previous, it able to differenciate
    collator = 0; //Collator must be initialised after differenciation for series processing
    }
    else if(rotation == 1 && state == LOW)
    {
      collator = millis();  
      condit = HIGH;
      previous = millis();
      statement = "Detected!";
      tone(buzzer, 523, 500); //Buzzer beeps when sensor has measured
      rotation += 1;            
      rpm = (60000)/(collator- previous)*rotation/mag;
      previous = collator;
      collator = 0; //Collator must be initialised after differenciation for series processing
    } 
    else{ condit = LOW; statement = "Activated!"; rpm = 0;}
    Pot = analogRead(analogPin); //Manages the voltage relay if it's more than certain value, it supplies electricity
    relay();
    str = "RPM: ";
    str += rpm;
    str += "& Pot: ";
    str += Pot;
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Taek J. RPM metre");    
    display.setCursor(0,11);
    display.println(statement);
    display.setCursor(0,22);
    display.println(rpm);
    display.setCursor(48,22);
    display.println(Pot);
    Serial.println("Welcome, This is Taek's RPM metre");
    Serial.println(str);
    digitalWrite(led, condit); //blinks when detected
    display.display();    
    delay(500); //To refresh the loop
  }
}

void freezing()
  {
    //By making boolean state to false, this method halts the loop method.
    halt = !halt;
  }

void thirteenth()
{
        //This method is for indication of voltage relay state via the 2nd led.
        /* This code doesn't work, due to the manually soldered #13 led on the board*/
        digitalWrite(led2nd, HIGH);
        delay(250);
        digitalWrite(led2nd, LOW);
        delay(250);
}

void relay()
{
  //This is a method supplying power to voltage relay via Potentiometre's statement
     if(Pot > 892 && halt == true) //if the potentiometre gives parametre which higher than 892, then it supplies voltage into the peripheral.
    {
      //In somehow, when it's connected to DC adaptor it doesn't work
      digitalWrite(voltlay, HIGH);
      delay(250);
    }
    else
    {
      digitalWrite(voltlay,LOW);
    }
}
