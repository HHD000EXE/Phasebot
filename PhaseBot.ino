/*
  Set up connection and set gyre
*/
void LSS_Init()
{
  LSS::initBus(Serial, LSS_BAUD); // initialize connection
  delay(2000);

  ALL.wheelRPM(0); // stop all wheels
  delay(2000);     // wait at least 1.25s to complete

  ALL.reset(); // RESET virtual angular position
  delay(5000); // wait at least 1.25s to complete

  // set gyre directions
  R_LEAD_LEG.setGyre(+1);
  L_LEAD_LEG.setGyre(-1);
  L_HIND_LEG.setGyre(-1);
  R_HIND_LEG.setGyre(+1);
  delay(500);
}

void LSS_Init_Simple()
{
  ALL.reset(); // RESET virtual angular position
  delay(2000); // wait at least 1.25s to complete
  
  // set gyre directions
  R_LEAD_LEG.setGyre(+1);
  L_LEAD_LEG.setGyre(-1);
  L_HIND_LEG.setGyre(-1);
  R_HIND_LEG.setGyre(+1);
  delay(500);
}

/*
   set all wheels going at some RPM
*/
void startMove(void)
{
  for (int i = 3; i >= 4; i--)
  {
    LSSs[i].wheelRPM(OMEGA);
  }
}

/*
   Stop all wheels moving
*/
void stopMove()
{
  for (int i = 0; i < 4; i++)
  {
    LSSs[i].wheelRPM(0);
  }
}

/*
   tune each motor's angular speed
   to approach the correct phi
*/
void approach(const Gait &g, bool align, long int &elapsed, const int &inhibition_1, const int &inhibition_2, const int &inhibition, int &dPhi, int32_t &Phi, int32_t &offset_leg0, bool &speed_sign, const int &delay_cp, int &temp)
{
  //set up the refrence leg
  
  Phi = LSSs[0].getPosition() / 10 + offset_leg0;
  if (Phi < 0) {
    Phi = - Phi;
  }
  Phi %= 360;

 if (g.name[0] == 'B')    // beulher clock for bounding gait start
  {
    if (Phi >= 0 && Phi  < 120)
    {
      LSSs[0].wheelRPM(OMEGA / 2);
      LSSs[1].wheelRPM(OMEGA / 2);
      
      temp = ((LSSs[2].getPosition() + offset_leg0) / 10) % 360 - Phi * 2;
      if (temp < -180){
        temp += 360;
        }
      dPhi = temp - 120;

      LSSs[2].wheelRPM(OMEGA - dPhi / inhibition + delay_cp);
      LSSs[3].wheelRPM(OMEGA - dPhi / inhibition + delay_cp);

      if (align == 1)
      {
        dPhi = (LSSs[3].getPosition() - LSSs[2].getPosition()) / 10 ;

        LSSs[3].wheelRPM(OMEGA - dPhi / inhibition_1);
        
        dPhi = (LSSs[1].getPosition() - LSSs[0].getPosition()) / 10 ;

        LSSs[1].wheelRPM(OMEGA/2 - dPhi / inhibition_2);
//        Serial.println("tt");
//        Serial.println(OMEGA/2 - dPhi / inhibition_2);
//        Serial.println();
//        Serial.println("tt");
      }
    }
    else
    {
      LSSs[0].wheelRPM(OMEGA);
      LSSs[1].wheelRPM(OMEGA);
      LSSs[2].wheelRPM(OMEGA / 2);
      LSSs[3].wheelRPM(OMEGA / 2);

      if (align == 1)
      {        
        dPhi = (LSSs[3].getPosition() - LSSs[2].getPosition()) / 10 ;

        LSSs[3].wheelRPM(OMEGA/2 - dPhi / inhibition_1);
        
        dPhi = LSSs[1].getPosition() / 10 - LSSs[0].getPosition() / 10 ;

        LSSs[1].wheelRPM(OMEGA - dPhi / inhibition_2);
      }
    }
  }    // beulher clock for trotting gait end// beulher clock for bounding gait end


  if (g.name[0] == 'T')    // beulher clock for trotting gait start
  {
    if (Phi >= 0 && Phi  < 120)
    {
      LSSs[0].wheelRPM(OMEGA / 2);
      LSSs[2].wheelRPM(OMEGA / 2);

      temp = ((LSSs[1].getPosition() / 10) + offset_leg0) % 360 - Phi * 2;
      if (temp < -180){
        temp += 360;
        }
      dPhi = temp - 120;

      LSSs[1].wheelRPM(OMEGA - dPhi / inhibition);
      LSSs[3].wheelRPM(OMEGA - dPhi / inhibition);

      if (align == 1)
      {
        dPhi = (LSSs[3].getPosition() - LSSs[1].getPosition()) / 10 ;

        LSSs[3].wheelRPM(OMEGA - dPhi / inhibition_1);
        
        dPhi = LSSs[2].getPosition() / 10 - LSSs[0].getPosition() / 10 ;

        LSSs[2].wheelRPM(OMEGA/2 - dPhi / inhibition_2);
      }
    }
    else
    {
      LSSs[0].wheelRPM(OMEGA);
      LSSs[2].wheelRPM(OMEGA);
      LSSs[1].wheelRPM(OMEGA / 2);
      LSSs[3].wheelRPM(OMEGA / 2);

      if (align == 1)
      {        
        dPhi = (LSSs[3].getPosition() - LSSs[1].getPosition()) / 10 ;

        LSSs[3].wheelRPM(OMEGA/2 - dPhi / inhibition_1);
        
        dPhi = LSSs[2].getPosition() / 10 - LSSs[0].getPosition() / 10 ;

        LSSs[2].wheelRPM(OMEGA - dPhi / inhibition_2);
      }
    }
  }    // beulher clock for trotting gait end


  if (g.name[0] == 'P')   // beulher clock for pacing gait start
  {
    if (Phi >= 0 && Phi  < 120)
    {
      LSSs[0].wheelRPM(OMEGA_P / 2);
      LSSs[3].wheelRPM(OMEGA_P / 2);

      temp = ((LSSs[1].getPosition() / 10 + offset_leg0)) % 360 - Phi * 2;
      if (temp < -180){
        temp += 360;
        }
      dPhi = temp - 120;

      LSSs[1].wheelRPM(OMEGA_P - dPhi / inhibition);
      LSSs[2].wheelRPM(OMEGA_P - dPhi / inhibition);

      if (align == 1)
      {
        dPhi = (LSSs[3].getPosition() - LSSs[0].getPosition()) / 10 ;

        LSSs[3].wheelRPM(OMEGA_P/2 - dPhi / inhibition_1);
        
        dPhi = LSSs[2].getPosition() / 10 - LSSs[1].getPosition() / 10 ;

        LSSs[2].wheelRPM(OMEGA_P - dPhi / inhibition_2);
      }
    }
    else
    {
      LSSs[0].wheelRPM(OMEGA_P);
      LSSs[3].wheelRPM(OMEGA_P);
      LSSs[1].wheelRPM(OMEGA_P / 2);
      LSSs[2].wheelRPM(OMEGA_P / 2);

      if (align == 1)
      {        
        dPhi = (LSSs[3].getPosition() - LSSs[0].getPosition()) / 10 ;

        LSSs[3].wheelRPM(OMEGA_P - dPhi / inhibition_1);
        
        dPhi = LSSs[2].getPosition() / 10 - LSSs[1].getPosition() / 10 ;

        LSSs[2].wheelRPM(OMEGA_P/2 - dPhi / inhibition_2);
      }
    }
  }   // beulher clock for pacing gait end
}

void LSS_Setup(const Gait &gait)
{
  LSS_Init_Simple();
  for (int i = 0; i < 4; i++)                        // perform initial alignment
    LSSs[i].move(((gait.offsets[i] + cal[i]) % 360) * 10); // multiply to tenths of degrees
  delay(2500);                                       // wait to complete
}

void RemoteSetup()
{
  Serial.begin(115200); // begin serial connection
  // set pins to read in
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
}

/**
   Read in a `Gait` from a the remote control
*/
Gait RemoteRead(RawInput &raw,
                Position &pos, int &move_sign)
{
  // read in raw values
  raw.lStck = pulseIn(A2, INPUT);
  raw.lKnob = pulseIn(A4, INPUT);
  raw.rKnob = pulseIn(A5, INPUT);

  // normalize to [0, 1]
  pos.lKnob = (raw.lKnob - bounds.lKnobMin) / (bounds.lKnobMax - bounds.lKnobMin);
  pos.rKnob = (raw.rKnob - bounds.rKnobMin) / (bounds.rKnobMax - bounds.rKnobMin);
  pos.lStck = (raw.lStck - bounds.lStckMin) / (bounds.lStckMax - bounds.lStckMin);

  // scale to [-180, +180]
  pos.lKnob *= 360;
  pos.rKnob *= 360;
  pos.lStck *= 360;

  Gait g; // represent the current gait

  if (0 < pos.lKnob && pos.lKnob < 120)
    g = bounding;

  if (120 < pos.lKnob && pos.lKnob < 240)
    g = trotting;

  if (240 < pos.lKnob && pos.lKnob < 360)
    g = pacing;

  if (pos.rKnob > 180)  // remote control start and stop
    move_sign = 1;
  else
    move_sign = 0;

  return g;
}
