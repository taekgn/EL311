int sensorValue = 0;
const byte interruptPin = 2;
volatile byte buttonState = LOW;

long randomnum = random(9000, 48000); // the random parameter with the range from 9 to 48 seconds
unsigned long beginTime = 0;
unsigned long currentTime = 0;
long difference = currentTime - beginTime ;

const float notes[] = {131, 138.59, 146.83, 155.56, 164.81, 174.61, 185.00, 196.00, 207.65, 220.00, 233.08, 246.94,
261.63, 277.18, 293.66, 311.13, 329.63, 349.23, 369.99, 392.00, 415.30, 440.00, 466.16, 493.88,
523.25, 554.37, 587.33, 622.25, 659.25, 698.46, 739.99, 783.99, 830.61, 880.00, 93.332, 987.77, 1046.50, 1108.73
}; //this is a arraylist for the musical organ method
const float noteCount = sizeof notes / sizeof notes[0];

void blink() {
    
    digitalWrite(13, HIGH);
    digitalWrite(9, LOW);
    delay(1000);
    digitalWrite(13, LOW);
  }

void musicalOrgan() 
{
      sensorValue = analogRead(A0); //reads the changing in potentiometre.
      sensorValue = map(sensorValue, 0, 1108, 0, 131); //maps value from the potentiometre from 131 to 1108
      tone(8, notes[map(sensorValue, 0, 1108, 0, noteCount -1.0)], 131); //arrange the values in notes to make sound
      analogWrite(8, sensorValue); //makes to beep the buzzer
}


void setup() {
  // put your setup code here, to run once:
pinMode(2,INPUT); //setting up push button to input
pinMode(2, INPUT_PULLUP);
pinMode(8, OUTPUT); //setting up buzzer to make sound
pinMode(9, OUTPUT); //led
pinMode(13,OUTPUT); //led2
//attachInterrupt(digitalPinToInterrupt(2), blink, RISING); //this command line makes to halt present running method or function and run blink method
}

void loop() 
{
    //musicalOrgan();
    buttonState = digitalRead(2);

    if(buttonState == 1)
    {
      beginTime = millis();
      attachInterrupt(digitalPinToInterrupt(2), blink, RISING); // this method calls the blink function to offset ongoing function.
      //int button2 = digitalRead(2);
      digitalWrite(9, HIGH);
      delay(randomnum);
      digitalWrite(9, LOW);
      buttonState = LOW;
    }
  }
