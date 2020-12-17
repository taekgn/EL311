/*
 * Assignment 1
 * Taekgeun Ji
 */
float time = 1.0; //this variable made for counting time, the reason of float chosen is because it's more efficent to count than integer
//the second led blinks 5 past which is odd number therefore variable type decided as float.
void setup() {
  // put your setup code here, to run once: 
pinMode(9, OUTPUT); //this code makes the led with channel 9 to output
pinMode(13, OUTPUT); //this code makes the led with channel 13 to output
pinMode(8, OUTPUT); //this code makes the buzzer with channel 8 to output
}
void loop(){
  // put your main code here, to run repeatedly:
  if(time == 6.0) //this "if" statement makes to beep when 10 seconds past the buzzer and blinking leds as well.
  {
    tone(8, 523, 1000); //The buzzer starts to beep for a second as the elasped time reached 10 seconds
digitalWrite(9, HIGH), digitalWrite(13, HIGH);
  delay(1000);
  time = time + 0.5; // adding the a half it counts the time by doing this process it checks by a second.
   digitalWrite(9, LOW), digitalWrite(13, LOW);
  delay(1000);
  time = time + 0.5;
  time = time - 5.0; //By command of this line the elasped time goes back to the initial stage therefore it makes to be looped infinitely
    }
    digitalWrite(9, HIGH); //led addressed channel as 9 starts to blink for a second
    delay(1000);  //1
    time = time + 0.5;
    if(time == 3.5) //this "if" statement makes to blink 2 of leds when 5 seconds past.
{
   digitalWrite(9, LOW), digitalWrite(13, HIGH);
  delay(1000);
  time = time + 0.5;
   digitalWrite(9, HIGH), digitalWrite(13, LOW);
  delay(1000);
  digitalWrite(9, LOW);
  time = time + 0.5;
  }
    digitalWrite(9, LOW);
    delay(1000); //2
    time = time + 0.5;
    }
