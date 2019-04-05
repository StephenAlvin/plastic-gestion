#include <avr/wdt.h>

const int knock_lungs= A3;
const int lungs_green= 2;
const int lungs_red= 3;
const int lungs_blue= 4;

const int knock_uterus= A0; 
const int uterus_green= 11;
const int uterus_red= 12;
const int uterus_blue= A4;

const int knock_heart= A2;
const int heart_green= 5;
const int heart_red= 6;
const int heart_blue= 7;

const int knock_kidney= A1;
const int kidney_green= 8;
const int kidney_red= 9;
const int kidney_blue= 10;

const int solutions_blue= A5;

const int SPEAKER= 13;

const int threshold= 100;

//............................................defining boolean values
bool lungs_on;
bool heart_on;
bool uterus_on;
bool kidney_on;

void song_1(){ //..............................speaker code 1
  tone(SPEAKER,392,100) ; // so
  delay(100) ;
  tone(SPEAKER,440,100) ; // la
  delay(100) ;
  tone(SPEAKER,494,100) ; // di
  delay(100) ;
  }
void song_2(){ //..............................speaker code 2
  tone(SPEAKER,330,100) ; // mi
  delay(100) ;
  tone(SPEAKER,294,100) ; // re
  delay(100) ;
  tone(SPEAKER,523,500) ; // do
  delay(500) ;
  }
void game_end(){ //.............................game end lights 
  digitalWrite(kidney_blue, LOW);
  digitalWrite(heart_blue, LOW);
  digitalWrite(uterus_blue, LOW);
  digitalWrite(lungs_blue, LOW);
  digitalWrite(kidney_red, HIGH);
  digitalWrite(heart_red, HIGH);
  digitalWrite(uterus_red, HIGH);
  digitalWrite(lungs_red, HIGH);
  digitalWrite(kidney_green, LOW);
  digitalWrite(heart_green, LOW);
  digitalWrite(uterus_green, LOW);
  digitalWrite(lungs_green, LOW);
  delay(500);
  digitalWrite(solutions_blue, HIGH);
  digitalWrite(kidney_blue, HIGH);
  digitalWrite(heart_blue, HIGH);
  digitalWrite(uterus_blue, HIGH);
  digitalWrite(lungs_blue, HIGH);
  digitalWrite(kidney_red, LOW);
  digitalWrite(heart_red, LOW);
  digitalWrite(uterus_red, LOW);
  digitalWrite(lungs_red, LOW);
  digitalWrite(kidney_green, LOW);
  digitalWrite(heart_green, LOW);
  digitalWrite(uterus_green, LOW);
  digitalWrite(lungs_green, LOW);
}

void setup(){//......................................SETUP
  Serial.begin(9600);

  MCUSR = 0; //-------IMPORTANT DUN DELET

  pinMode(knock_kidney, INPUT_PULLUP);
  pinMode(knock_uterus, INPUT_PULLUP);
  pinMode(knock_lungs, INPUT_PULLUP);
  pinMode(knock_heart, INPUT_PULLUP);
  
  pinMode(solutions_blue, OUTPUT);
  
  pinMode(lungs_green, OUTPUT);
  pinMode(lungs_red, OUTPUT);
  pinMode(lungs_blue, OUTPUT);

  pinMode(heart_green, OUTPUT);
  pinMode(heart_red, OUTPUT);
  pinMode(heart_blue, OUTPUT);
  
  pinMode(uterus_red, OUTPUT);
  pinMode(uterus_green, OUTPUT);
  pinMode(uterus_blue, OUTPUT);
  
  pinMode(kidney_red, OUTPUT);
  pinMode(kidney_green, OUTPUT);
  pinMode(kidney_blue, OUTPUT);
  
  bool lungs_on = false; //.........................false means red
  digitalWrite(lungs_red, HIGH);
  digitalWrite(lungs_green, LOW);
  digitalWrite(lungs_blue, LOW);
  bool heart_on = false;
  digitalWrite(heart_red, HIGH);
  digitalWrite(heart_green, LOW);
  digitalWrite(heart_blue, LOW);
  bool kidney_on = false;
  digitalWrite(kidney_red, HIGH);
  digitalWrite(kidney_green, LOW);
  digitalWrite(heart_blue, LOW);
  bool uterus_on = false;
  digitalWrite(uterus_red, HIGH);
  digitalWrite(uterus_green, LOW);
  digitalWrite(uterus_blue, LOW);
}

byte lung_val = 0;
byte uterus_val = 0;
byte kidney_val = 0;
byte heart_val = 0;

void loop() {//.................................................LOOP

//...............................................................Defining Sensors
  int lung_val= 1023 - analogRead(knock_lungs);
  int uterus_val= 1023 - analogRead(knock_uterus);
  int heart_val= 1023 - analogRead(knock_heart);
  int kidney_val= 1023 - analogRead(knock_kidney);
  
//.........................................SETTING UP THE VARIABLES FOR LIGHTING

  if (lungs_on){
    digitalWrite(lungs_green, HIGH);
    digitalWrite(lungs_red, LOW);
  }
  else{
    digitalWrite(lungs_green, LOW);
    digitalWrite(lungs_red, HIGH);
  }
  
  if (heart_on){
    digitalWrite(heart_green, HIGH);
    digitalWrite(heart_red, LOW);
  }
  else{
    digitalWrite(heart_green, LOW);
    digitalWrite(heart_red, HIGH);
  }
  
  if (kidney_on){
    digitalWrite(kidney_green, HIGH);
    digitalWrite(kidney_red, LOW);
  }
  else{
    digitalWrite(kidney_green, LOW);
    digitalWrite(kidney_red, HIGH);
  }
  
  if (uterus_on){
    digitalWrite(uterus_green, HIGH);
    digitalWrite(uterus_red, LOW);
  }
  else{
    digitalWrite(uterus_green, LOW);
    digitalWrite(uterus_red, HIGH);
  }
  
//.................................SETTING UP THE SCRIPT
  
  if(lung_val >= threshold){
    Serial.write(lung_val);
    Serial.println(lung_val);
    lungs_on = not lungs_on;
    song_1();
    delay(300);
  }
  if(uterus_val>= threshold){
    Serial.write(uterus_val);
    Serial.println(uterus_val);
    uterus_on = not uterus_on;
    song_1();
    delay(300);

  }
  if(heart_val>= threshold){
    Serial.write(heart_val);
    Serial.println(heart_val);
    heart_on = not heart_on;
    song_1();
    delay(300);

  }
  if(kidney_val>= threshold){
    Serial.write(kidney_val);
    Serial.println(kidney_val);
    kidney_on = not kidney_on;
    song_1();
    delay(300);
  }
  if (lungs_on == false && heart_on == false && kidney_on == false && uterus_on == false){ //........BLUE LIGHTS
    game_end();
    song_2();
    delay(10000);
    wdt_enable(WDTO_15MS);
    for(;;);
  }

  
}
