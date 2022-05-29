
#include "AlphaBot.h"

int LSensorPin = 7;      //A bal távolságérzékelő pinjének beállítása
int RSensorPin = 8;      //A jobb távolságérzékelő pinjének beállítása
int m = 0;               //Az m változó beállítása 0-ra(ez lesz az üzenet értéke)                      

int LSensor;              //Bal távolságérzékelő értéke(változó)
int RSensor;              //Jobb távolságérzékelő értéke(változó)

AlphaBot rZ = AlphaBot();

void ProximityConfig()
{
  pinMode(RSensorPin, INPUT);         //Definiálja a jobb távolságérzékelő bemeneti pinjét
  pinMode(LSensorPin, INPUT);         //Definiálja a bal távolságérzékelő bemeneti pinjét
}

void kijon_a_hazbol() {
  rZ.MotorRun(-130, -150);
  delay(200);
  rZ.LeftCircle(375);
  rZ.MotorRun(130, 150);
  delay(1000);
  rZ.RightCircle(337);
  rZ.MotorRun(130, 150);
  delay(2000);
  rZ.RightCircle(337);
  rZ.MotorRun(130, 150);
  delay(1000);
  rZ.LeftCircle(375);
  }

void paratlan_sor()
{
  delay(400);
  rZ.MotorRun(130, 150);     //1 másodpercig előremegy
  rZ.Brake();

  delay(400);
  rZ.Backward(1200);  //1 másodpercig hátramegy
  rZ.Brake();

  delay(400);
  rZ.LeftCircle(1200);  //1 másodpercig balra tesz egy kört
  rZ.Brake();

  delay(400);
  rZ.Backward(1200);  //1 másodpercig hátramegy
  rZ.Brake();

  delay(400);
  rZ.MotorRun(0, 250);  //Balra tesz egy kört; bal motor sebessége: 0, jobb motor sebessége: 250
  delay(1200);
  rZ.Brake();

  delay(1600);
}

void paros_sor()
{
  delay(400);
  rZ.MotorRun(130, 150);     //1 másodpercig előremegy
  rZ.Brake();

  delay(400);
  rZ.Backward(1200);  //1 másodpercig hátramegy
  rZ.Brake();

  delay(400);
  rZ.LeftCircle(1200);  //1 másodpercig balra tesz egy kört
  rZ.Brake();

  delay(400);
  rZ.Backward(1200);  //1 másodpercig hátramegy
  rZ.Brake();

  delay(400);
  rZ.MotorRun(250, 0);  //Jobbra tesz egy kört; bal motor sebessége: 250, jobb motor sebessége: 0
  delay(1200);
  rZ.Brake();

  delay(1600);
}

void setup() {
  Serial.begin(9600);
  ProximityConfig();
  rZ.SetSpeed(150);
  kijon_a_hazbol();
}

void loop() {

  RSensor = digitalRead(RSensorPin);            //LOW = van jel; HIGH = nincs jel
  LSensor = digitalRead(LSensorPin);            //LOW = van jel; HIGH = nincs jel
  
  if (LSensor == HIGH && RSensor == HIGH) {       //Ha nincs előtte akadály, menjen előre
    rZ.MotorRun(130, 150);
  }

  else if (LSensor == HIGH && RSensor == LOW) {   //Ha a jobb érzékelő kap jelet, forduljon balra
    rZ.Backward(175);
    rZ.LeftCircle(425);
    rZ.MotorRun(130, 150);
    delay(1750);
    rZ.RightCircle(345);
    rZ.MotorRun(130, 150);
    delay(1750);
    rZ.RightCircle(345);
    rZ.MotorRun(130, 150);
    delay(1750);
    rZ.LeftCircle(425);
    rZ.MotorRun(130, 150);
  }

  else if (RSensor == HIGH && LSensor == LOW) {   //Ha a bal érzékelő kap jelet, forduljon jobbra
    rZ.Backward(175);
    rZ.RightCircle(345);
    rZ.MotorRun(130, 150);
    delay(1750);
    rZ.LeftCircle(425);
    rZ.MotorRun(130, 150);
    delay(1750);
    rZ.LeftCircle(425);
    rZ.MotorRun(130, 150);
    delay(1750);
    rZ.RightCircle(345);
    rZ.MotorRun(130, 150);
  }

  else                                          //Ellenkező esetben keressen másik utat keres
  {
    rZ.LeftCircle();
    delay(5);
    rZ.MotorRun(130, 150);
    delay(1750);
  }

  while(Serial.available()>0) {
    m = Serial.parseInt();
    }

  if(m==1) {
      paratlan_sor();
      paros_sor();
      paratlan_sor();
      paros_sor();
    } 
  }
