#include <LSS.h>
#include <EEPROM.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

#include "libraries/Gait.h"
#include "libraries/Remote.h"
#include "libraries/Legs.h"

#define LSS_BAUD (LSS_DefaultBaud)

int temp;
int beg,en;
int32_t debug = 0;

int move_sign = 0;  bool align = 0; bool speed_sign = 0;
int OMEGA = 34; // in RPM
int OMEGA_P = 26; // in RPM
const int inhibition = 15;const int inhibition_1 = 3;const int inhibition_2 = 3; const int delay_cp = 0;
int dPhi = 0; int32_t Phi = 0;
int32_t offset_leg0 = 0;

Gait gait = bounding;
char name_t;

long int start = 0;   // track time
long int elapsed = 0;    // track time

// LCD declaration
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// currently using elijah's remote & robot
const Bounds bounds = remote1;

// instantiate input struct
RawInput raw;
Position pos;

void setup()
{
  //    zero();
  //    LSS_Setup(gait);     // move legs into position
  //    startMove();         // begin rotation
  //    LCD_gait(lcd, gait); // print gait to screen
  LSS_Init();
  RemoteSetup();       // setup serial connection
}

void loop()
{
//  beg = millis();
  Serial.println(" ");
  Serial.println(Phi);
  Serial.println((LSSs[2].getPosition() / 10) % 360 );
  elapsed = millis();
  gait = RemoteRead(raw, pos, move_sign);     // read in updates from remote
  if ((name_t != gait.name[0]) && move_sign == 0)
  {
    LSS_Setup(gait);
    name_t = gait.name[0];
//    LCD_gait(lcd, gait);             // show gait on screen
  }

  if (move_sign == 0)
  {
    stopMove();                      // stop moving
  }
  
  else
  {
    if (elapsed > start + 1000)
    {
      start = elapsed;
      align = 1;
    }
    
    approach(gait, align, elapsed, inhibition_1, inhibition_2, inhibition, dPhi, Phi, offset_leg0, speed_sign, delay_cp, temp);                 // read in updates from remote
    
    if (align == 1)
      align = 0;
  }
//  en = millis();
//  Serial.println(en - beg);
}
