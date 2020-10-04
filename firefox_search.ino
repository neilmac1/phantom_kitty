#include <Keyboard.h>

/* Firefox_search_1.0 
*  This code is last updated 23 APR 2020 and is designed for the firefox browser
*  
*This particular code is meant to be used on a USB type microcontroller.  (Beetle USB) Use Arduino Leonardo as board type.
*It works by pointing to the search bar, and inserting random characters to intiate an autocomplete search, which are modified and picked at random.
*It is meant to be run autonomously on a computer when not in use to pollute unethical data gathering services. 
*
*/

//Adjust the following based on what you want the program to do.

int max_iterations = 4; //(feel free to change) max iterations for each search entry
int max_letters = 3; //enter a number of letters to use for max letters consecutively (larger would make more jibberish, keep small)
int max_characters = 41; //this should correspond to the number below
int characters[41] = {'a','a','a','b','c','d','d','e','e','e','e','f','g','h','h','i','i','j','k','l','l','m','n','n','o','o','p','q','r','r','s','s','t','t','t','u','v','w','x','y','z'};  //array of all letters only characters[41]
int max_searches_before_clear = 17; //after this many searches, the browsing history is cleared so prior searches no longer guide future searches

//don't change the following
int iterations = 0;  //intialization variable 
int iterations_to_use = 1; //intialization variable
int letters_to_use = 1; //intialization variable
int key_to_press = 1; //intialization variable
int downs_to_press = 1; //intialization variable
int letter = 1;//intialization variable
int downs = 1;//intialization variable
int cumulative_searches=0;//intialization variable
int seed_0=1; //seed values are for making the a randomseed more random.  Reading A0 did not do well.
int seed_1=1;
int seed_3=1;


void setup() 
{
   Serial.begin(9600);
   Keyboard.begin();
   seed_0=analogRead(A0)*analogRead(A1)*analogRead(A2)*analogRead(A3)*analogRead(A4);
   delay(50);
   seed_1=analogRead(A0)*analogRead(A1)*analogRead(A2)*analogRead(A3)*analogRead(A4);
   delay(50);
   seed_3=analogRead(A0)*analogRead(A1)*analogRead(A2)*analogRead(A3)*analogRead(A4);
   randomSeed(seed_0+seed_1+seed_3); //apparently the random is not random.  This block seeds the random value.  A0-A4 are used with the code above which worked well in testing.
   delay(random(0,100));
   if (random(0,100) < 50){  //this block has a XX% chance (whatever after the less than sign is of running the following code, which reseeds the random value
   seed_0=analogRead(A0)*analogRead(A1)*analogRead(A2)*analogRead(A3)*analogRead(A4);
   delay(50);
   seed_1=analogRead(A0)*analogRead(A1)*analogRead(A2)*analogRead(A3)*analogRead(A4);
   delay(50);
   seed_3=analogRead(A0)*analogRead(A1)*analogRead(A2)*analogRead(A3)*analogRead(A4);
   randomSeed(seed_0+seed_1+seed_3); //reads random value
   Serial.println(random(0,100)); //test a random sequence (should be different each time)
   Serial.print("\t");  //new line
   Serial.println(analogRead(A0)); //prints the read (should be different each time)
   }   
}

void loop() {

    while (analogRead(A2) > 500) {  //This is to reprogram the board.  Place your finger agross the 5V and A2 pins and it gets stuck in the loop.  Check serial monitor to see numbers printing to know its stuck.  
    Keyboard.releaseAll();
    Serial.println(analogRead(A0));
    (delay(200));  //without this, you couldn't reprogram the the board as it would be adding letters to your code all the time.  (lesson learned)
    }
    if (random(0,100) < 25){
    seed_0=analogRead(A0)*analogRead(A1)*analogRead(A2)*analogRead(A3)*analogRead(A4);
    delay(50);
    seed_1=analogRead(A0)*analogRead(A1)*analogRead(A2)*analogRead(A3)*analogRead(A4);
    delay(50);
    seed_3=analogRead(A0)*analogRead(A1)*analogRead(A2)*analogRead(A3)*analogRead(A4);
    randomSeed(seed_0+seed_1+seed_3); //Some randommess on xx% of iterations
    }  
    
    //Step 1: Point the browser at the search bar
    Keyboard.press(KEY_LEFT_CTRL);
    delay(random(5,90));  //may need to make this random to confuse a discrete delay
    Keyboard.press('k'); //this is either 'e' or 'k' depending on browser
    delay(random(3,93));
    Keyboard.release(KEY_LEFT_CTRL);
    Keyboard.release('k');
    delay(random(500,1500));

    //Step 2: Select random number of iterations
    iterations_to_use = random(1,max_iterations); //picks a number between 1 and the iterations_max to use

    //Step 3: Step through the iterations by (step 3A) pressing a randeom sequence of characters between 1 and max_letters, (3B) pressing down 1-10 times, (3C) if looping, space, if done, enter.
    
    for (int iteration = 1; iteration <= iterations_to_use; iteration++) {
    
    //Step 3A

    if (iteration==1){
      letters_to_use = random(2, max_letters);  //picks number of letters to press during this iteration - larger numbers are gibberish.  Also, need at least 2 since 1 doesn't create an auto-suggest.
    }
    else {
      letters_to_use = random(1,2); //only 1 or 2 after first since it gets very nonsensical with 3 or more
    }
    for (int letter = 1; letter <= letters_to_use; letter++) {
    key_to_press=characters[random(0,max_characters)];
    
    Keyboard.write(key_to_press);
    delay(random(100,500)); 
    }

    //the following is necessary to reseed the random value so the searches are not the same each time.  (copy to other areas of the code if you feel so inclined)
    if (random(0,100) < 5){  //this block has a XX% chance (whatever after the less than sign is of running the following code, which reseeds the random value
    seed_0=analogRead(A0)*analogRead(A1)*analogRead(A2)*analogRead(A3)*analogRead(A4);
    delay(50);
    seed_1=analogRead(A0)*analogRead(A1)*analogRead(A2)*analogRead(A3)*analogRead(A4);
    delay(50);
    seed_3=analogRead(A0)*analogRead(A1)*analogRead(A2)*analogRead(A3)*analogRead(A4);
    randomSeed(seed_0+seed_1+seed_3); //reads a value that changes based on light reaching the sensor
    }

    //Step 3B
    if (iteration==1){
      downs_to_press = random(1, 9); //picks how many times down to press on the auto-complete entries
    }
    else {
      downs_to_press = random(1,5); //less downs after the first iteration
    }
    for (int downs = 1; downs <= downs_to_press; downs++) {
    Keyboard.write(KEY_DOWN_ARROW);
    delay(random(100,400));

    //reseeds random
    if (random(0,100) < 5){  //this block has a XX% chance (whatever after the less than sign is of running the following code, which reseeds the random value
    seed_0=analogRead(A0)*analogRead(A1)*analogRead(A2)*analogRead(A3)*analogRead(A4);
    delay(50);
    seed_1=analogRead(A0)*analogRead(A1)*analogRead(A2)*analogRead(A3)*analogRead(A4);
    delay(50);
    seed_3=analogRead(A0)*analogRead(A1)*analogRead(A2)*analogRead(A3)*analogRead(A4);
    randomSeed(seed_0+seed_1+seed_3); //reads a value that changes based on light reaching the sensor
    }}     

    if (iteration == iterations_to_use) {
      Keyboard.write(KEY_RETURN);
      delay(random(100,400));
    }
    else {
      Keyboard.write(' ');
      delay(random(400,900));
    }
    }

    delay(random(4000,8000));  //if you have a slow browser or windows 10 you may need to make this longer to account for lag after searches

    //Step 4: If the number of searches reaches the maximum defined, clear search history with ctrl-shift-del then enter
    if (cumulative_searches == max_searches_before_clear) {
      Keyboard.press(KEY_LEFT_CTRL);
      delay(random(150,300)); 
      Keyboard.press(KEY_LEFT_SHIFT);
      delay(random(100,300));
      Keyboard.press(KEY_DELETE);
      delay(random(100,300));
      Keyboard.release(KEY_LEFT_CTRL);
      Keyboard.release(KEY_LEFT_SHIFT);
      Keyboard.release(KEY_DELETE);
      delay(random(500,2000));
      Keyboard.write(KEY_RETURN);
      delay(random(100,400));
      cumulative_searches = 0; //resets the searches counter
      Keyboard.releaseAll();
      delay(random(2000,8000));
    }
    else {
      cumulative_searches++;  //if max searches before clear value not yet reached, increments the cumulative searches variable
    }

}
