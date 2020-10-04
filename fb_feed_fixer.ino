#include <Keyboard.h>

/*fb_feed_fixer
 * randomly likes posts when plugged in.
 * unplug to stop.
 * uses the Beetle USB board.  Use Arduino Leonardo as board type when uploading.
 * updated 10/03/2020
 */
 

int max_iterations = 8; //(max iterations for scrolling down, vary between 5-12 ish, or lower if you really like a lot of things)
int down_presses=1; //intialization value
int sequence=1; //initialization value


void setup() {
  // put your setup code here, to run once:
pinMode(A2, INPUT);
pinMode(A0, INPUT);
Serial.begin(9600);
randomSeed(analogRead(A0));
delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:

while (analogRead(A2) > 501) {  //This is to reprogram the board.  Place your finger agross the 5V and A2 pins and it gets stuck in the loop.  Check serial monitor to see numbers printing to know its stuck.  
  Serial.println(analogRead(A2));
  Serial.println(analogRead(A0));
  (delay(200));  //without this, you couldn't reprogram the the board as it would be adding letters to your code all the time.  (lesson learned)
}
if (random(0,100) < 25){
  randomSeed(analogRead(A0)); //Some randommess attempt
  }  
if (random(0,100) < 10){
  randomSeed(analogRead(A0)); //Some randommess attempt
  }  

down_presses = random(1, max_iterations);

for (int sequence =1; sequence <= down_presses; sequence++){ //randomly picks value between 1 and max iterations to press down
  Keyboard.write('j');  //scroll down
  delay(random(700,3500)); //random delay between down scrolls
}
delay(random(1500,3500)); //pause before liking
Keyboard.write('l'); //l to like
delay(random(1000,7000)); //pause to reflect on after liking
}
