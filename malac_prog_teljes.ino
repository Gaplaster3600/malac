// A TELJES MALAC ELŐADÁS MIRK 2022 2.0. (SAMU AZ ELSŐT ELCSESZTE)

#include "AlphaBot.h"
#include <Servo.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *left = AFMS.getMotor(2);
Adafruit_DCMotor *right = AFMS.getMotor(1);

/*
    DEFINÍCIÓK
*/

void varjPls() {
  delay(500);  
}

int turnSpeed = 69;
int forwardSpeed = 100;

int LSensorPin = 7;
int RSensorPin = 8;

int LSensor;              //Bal távolságérzékelő értéke(változó)
int RSensor;              //Jobb távolságérzékelő értéke(változó)

AlphaBot rZ = AlphaBot();

/*
    FÜGGVÉNY(KERÜLÉS)
*/

void ProximityConfig()
{
  pinMode(RSensorPin, INPUT);         //Definiálja a jobb távolságérzékelő bemeneti pinjét
  pinMode(LSensorPin, INPUT);         //Definiálja a bal távolságérzékelő bemeneti pinjét
}

/*
    FÜGGVÉNY(PÁRATLANSOR)
*/

void patl()
  {
     delay(400);
     rZ.Forward(1200);     //1 másodpercig előremegy
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

/*
    FÜGGVÉNY(PÁROSSOR)
*/

  void pos()
  {
     delay(400);
     rZ.Forward(1200);     //1 másodpercig előremegy
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

/*
    SEBESSÉG MEG A KERÜLÉS BEÁLLÍTÁSA
*/

void setup() {
  ProximityConfig();
  rZ.SetSpeed(150);
  Serial.begin(9600);
  AFMS.begin();
  left->setSpeed(turnSpeed);
  right->setSpeed(turnSpeed);
}

void loop() {
     switch(Serial.parseInt())
  {
     
     case 1:
      rZ.motorRun(turnSpeed, 0);
      break;

     case 2:
      rZ.motorRun(0, turnSpeed);
      break;

     case 3:
      rZ.motorRun(moveSpeed, moveSpeed);
      break;

    case 4:
      rZ.motorRun(-moveSpeed, -moveSpeed);
      break;

     case -1:
      rZ.Right(750);
   varjPls();

   rZ.Forward(600);
   varjPls();

   rZ.Left(850);
   varjPls();
      break;

    case -2:
      patl();
    pos();
    patl();
    pos(); 
      break;

    case -3:
      rZ.Right(750);
   varjPls();

   rZ.Forward(600);
   varjPls();

   rZ.Left(850);
   varjPls();
      break;

    default:
      left->run(RELEASE);
      right->run(RELEASE);
      break;
  }
}
}
