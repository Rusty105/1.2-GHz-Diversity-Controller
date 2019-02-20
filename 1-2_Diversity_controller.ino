/* Simple sketch to select which 1.2 GHZ reciever
* to use for the video signal. Or any reciever
* with a volatge based RSSI signal.
* This is just the start
*/

// Target board = Arduino Mini Pro (5V)


// Setup variables

// ADC input pins
int rxa = 1;  // ADC input of reciever A
int rxb = 1;  // ADC input of reciever B
// int rxc = ?;  // ADC input of reciever C (future)
// int rxd = ?;  // ADC input of reciever D (future)

// Manual button  pins
int manauto = 1; // Button to automatically pick reciever
int mana = 1;  // Button to manualy pick reciever A
int manb = 1;  // Button to manualy pick reciever B
// int manc = ?;  // Button to manualy pick reciever C (future)
// int mand = ?;  // Button to manualy pick reciever D (future)
int mode = 0; // diversity mode on startup, 0=Auto, 1= rx A, 2= rx B, etc...

// Display LED pins
int leda = 13; // Reciever A LED, use built in
int ledb = 1; // Reciever B LED
// int ledc = ?; // Reciever C LED Future)
// int ledd = ?; // Reciever D LED (future)

int userx = 1; // set initial rx to rx A

// Buzzer
int buzz = 1; // pin for buzzer
int tonefreqa = 1000; // frequency in Hz
int tonefreqb = 2000; // frequency in Hz

// Outputs for LCD display.
// ???


void setup() {  
   Serial.begin(9600); // setup serial for debug
   pinMode(rxa, INPUT); // rx A input
   pinMode(rxb, INPUT); // rx B input

   pinMode(manauto, INPUT); // input for Auto mode
   pinMode(mana, INPUT);  // input for manually select rx A
   pinMode(manb, INPUT);  // input for manually select rx B

   pinMode(leda, OUTPUT); // rx A LED (likely use built in LED for rx a)
   pinMode(ledb, OUTPUT); // rx B LED

   pinMode(buzz, OUTPUT);
}

 

void loop(){

// read buttons and set mode
   int buttona = digitalRead(mana);
   int buttonb = digitalRead(manb);
   int buttonauto = digitalRead(manauto);
  
// set RX mode
   if (buttona = 1){
      mode=1;  // set rx A
   }
   else if (buttonb = 1){
      mode=2;  // set rx B
   }else
      mode=0;  // set auto

// change mode if needed//
   
   
// read RSSI and convert to voltage

   int RSSIA = analogRead(rxa);
   float volta = RSSIA*(5.0/1023.0);
   int RSSIB = analogRead(rxb);
   float voltb = RSSIB*(5.0/1023.0);

// display readings

// decide on reciever


// set reciever if necessary

//


// loop 

 }  // Close main loop


// functions

// function select reciever a
void setrxa(){
   userx=1;
   digitalWrite(ledb,LOW); // set ledb off
   digitalWrite(leda,HIGH); // set leda on
   tone(buzz, tonefreqa);
   delay(100); // 1000 = 1 sec
   noTone(buzz);
}


// function select reciever b
void setrxb(){
   userx=2;
   digitalWrite(leda,LOW); // set leda off
   digitalWrite(ledb,HIGH); // set ledb on
   tone(buzz, tonefreqb);
   delay(100); // 1000 = 1 sec
   noTone(buzz);
}
