/* Simple sketch to select which 1.2 GHZ reciever
  to use for the video signal. Or any reciever
  with a volatge based RSSI signal.
  This is just the start
*/

// Target board = Arduino Mini Pro (5V)


#include "U8glib.h"

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);  // I2C / TWI

// Setup variables

// ADC input pins
int rxa = A0;  // ADC input of reciever A
int rxb = A1;  // ADC input of reciever B
// int rxc = ?;  // ADC input of reciever C (future)
// int rxd = ?;  // ADC input of reciever D (future)

// Manual button  pins
int manauto = 3; // Button to automatically pick reciever
int mana = 4;  // Button to manualy pick reciever A
int manb = 2;  // Button to manualy pick reciever B
// int manc = ?;  // Button to manualy pick reciever C (future)
// int mand = ?;  // Button to manualy pick reciever D (future)
int mode = 0; // diversity mode on startup, 0=Auto, 1= rx A, 2= rx B, etc...

// Display LED pins
int leda = 13; // Reciever A LED, use built in
int ledb = 1; // Reciever B LED
// int ledc = ?; // Reciever C LED (future)
// int ledd = ?; // Reciever D LED (future)

int userx = 1; // set initial rx to rx A

// Buzzer
int buzz = 8; // pin for buzzer
int tonefreqa = 1000; // frequency in Hz
int tonefreqb = 1500; // frequency in Hz

// Outputs for LCD display.
// ???

int RSSIA = 0;
int RSSIB = 0;
float volta = 0;
float voltb = 0;
float ssa = 0;
float ssb = 0;


void setup() {
  Serial.begin(9600); // setup serial for debug
  pinMode(rxa, INPUT); // rx A input
  pinMode(rxb, INPUT); // rx B input
  // use internal pullups, buttons will pull to low
  pinMode(manauto, INPUT_PULLUP); // input for Auto mode
  pinMode(mana, INPUT_PULLUP);  // input for manually select rx A
  pinMode(manb, INPUT_PULLUP);  // input for manually select rx B

  pinMode(leda, OUTPUT); // rx A LED (likely use built in LED for rx a)
  pinMode(ledb, OUTPUT); // rx B LED

  pinMode(buzz, OUTPUT);
  BuzzerHello();
  delay(500);
  BuzzTone();

}



void loop() {

  // read buttons and set mode
  int buttona = digitalRead(mana);
  int buttonb = digitalRead(manb);
  int buttonauto = digitalRead(manauto);

  // set RX mode
  if (buttona = 0) {
    mode = 1; // set rx A
  }
  else if (buttonb = 0) {
    mode = 2; // set rx B
  } else
    mode = 0; // set auto

  // change mode if needed//


  // read RSSI and convert to voltage and percent

  RSSIA = analogRead(rxa);
  volta = RSSIA * (5.0 / 1023.0);
  ssa = RSSIA * (100.0 / 1023.0);
  RSSIB = analogRead(rxb);
  voltb = RSSIB * (5.0 / 1023.0);
  ssb = RSSIB * (100.0 / 1023.0);

  // display readings
  u8g.firstPage();
  do {
    draw(volta, voltb, ssa, ssb);
  } while ( u8g.nextPage() );

  // decide on reciever

  

}  // Close main loop


// functions

// function select reciever A
void setrxa() {
  userx = 1;
  digitalWrite(ledb, LOW); // set ledb off
  digitalWrite(leda, HIGH); // set leda on
  // send output to switch
  tone(buzz, tonefreqa);
  delay(100); // 1000 = 1 sec
  noTone(buzz);
}


// function select reciever B
void setrxb() {
  userx = 2;
  digitalWrite(leda, LOW); // set leda off
  digitalWrite(ledb, HIGH); // set ledb on
  // sens output to switch
  tone(buzz, tonefreqb);
  delay(100); // 1000 = 1 sec
  noTone(buzz);
}

void draw(float a, float b, int aa, int bb) {
  // graphic commands to redraw the complete screen should be placed here
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  u8g.drawStr( 0, 22, "RX-A      V    %");
  u8g.drawStr( 0, 44, "RX-B      V    %");
  u8g.drawStr( 0, 60, "Counter " " units");
  u8g.setPrintPos(45, 22);
  u8g.print(a);
  u8g.setPrintPos(45, 44);
  u8g.print(b);
  u8g.setPrintPos(100, 22);
  u8g.print(aa);
  u8g.setPrintPos(100, 44);
  u8g.print(bb);
}

// bip bip bip...
  void BuzzerHello()
  {
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(buzz, HIGH);
      delay(30);
      digitalWrite(buzz, LOW);
      delay(30);
    }
  }

// buzz tone test
  void BuzzTone()
  {
    tone(buzz, 1000);
    delay(100);
    noTone(buzz);
    delay(250);
    tone(buzz, 1500);
    delay(100);
    noTone(buzz);
  }
