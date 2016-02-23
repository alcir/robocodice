#include "robot.h" //include the declaration for this class

#define TRIGGER_PIN 10
#define ECHO_PIN 11
#define MAX_DISTANCE 50

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

robot::robot(AccelStepper stepperUno, AccelStepper stepperDue, unsigned int avanzamento){
  
  _distanza = 0;

  steps = avanzamento;

  stepper1 = stepperUno;
  stepper2 = stepperDue;
  
  pinFinecorsa = A5;

  pingSpeed = 500; // How frequently are we going to send out a ping (in milliseconds). 50ms would be 20 times a second.
  
  pingTimer = millis(); // Start now.

}
 
// <<destructor>>
robot::~robot(){/*nothing to destruct*/}

int robot::guarda() {

  if (millis() >= this->pingTimer) {   // pingSpeed milliseconds since last ping, do another ping.
    pingTimer += pingSpeed;      // Set the next ping time.

	 _distanza=sonar.ping_cm();
    //Serial.print("ooooo ");
    //Serial.println(distanza);
	 return _distanza;

  }

   return 100;

}

void robot::reset() {

  stepper1.setMaxSpeed(2000.0);
  stepper1.setAcceleration(500.0);
    
  stepper2.setMaxSpeed(2000.0);
  stepper2.setAcceleration(500.0);

}

void robot::anima(void) {

  this->reset();
 
  pinMode(13, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(pinFinecorsa, INPUT);
}

void robot::vai_avanti(void) {

  //digitalWrite(A3, HIGH); 

  this->reset();

  endPoint = this->steps;

  stepper1.setSpeed(1000);
  stepper2.setSpeed(1000);
  
  stepper1.moveTo(endPoint);  
  stepper2.moveTo(-endPoint);
  
  while (stepper1.distanceToGo() != 0) {
    stepper1.setSpeed(1000);
    stepper2.setSpeed(1000);
      
    stepper1.runSpeedToPosition();
    stepper2.runSpeedToPosition();
  }

  stepper1.setCurrentPosition(0);
  stepper2.setCurrentPosition(0);

  digitalWrite(A3, LOW); 

}

void robot::avanti_tutta(void) {

  //digitalWrite(A3, HIGH); 

  this->reset();
  stepper1.setSpeed(1000);
  stepper2.setSpeed(-1000);

  stepper1.runSpeed();
  stepper2.runSpeed();

  digitalWrite(A3, LOW); 
  
}

void robot::vai_indietro(void) {

  digitalWrite(A4, HIGH);
 
  endPoint = this->steps;
  stepper1.setCurrentPosition(0);
  stepper2.setCurrentPosition(0);

  stepper1.setSpeed(2000);
  stepper2.setSpeed(2000);
  
  stepper1.moveTo(-endPoint);  
  stepper2.moveTo(+endPoint);
  
  while (stepper1.distanceToGo() != 0) {
    stepper1.run();
    stepper2.run();
  }

  stepper1.setCurrentPosition(0);
  stepper2.setCurrentPosition(0);

  digitalWrite(A4, LOW);  

}


void robot::girati_verso_sinistra(void) {

  digitalWrite(A2, HIGH); 
  
  this->reset();

  stepper1.setCurrentPosition(0);
  stepper2.setCurrentPosition(0);

  endPoint = 2400;

  stepper1.setSpeed(2000);
  stepper2.setSpeed(2000);

  stepper1.moveTo(endPoint+150);  
  stepper2.moveTo(endPoint);
  
  while (stepper1.distanceToGo() != 0) {
    stepper1.run();
    stepper2.run();
  }

  stepper1.setCurrentPosition(0);
  stepper2.setCurrentPosition(0);

  digitalWrite(A2, LOW); 
  
}

void robot::girati_verso_destra(void) {

  digitalWrite(A1, HIGH); 
  
  this->reset();

  stepper1.setCurrentPosition(0);
  stepper2.setCurrentPosition(0);

  endPoint = 2400;

  stepper1.setSpeed(1000);
  stepper2.setSpeed(1000);

  stepper1.moveTo(-endPoint);  
  stepper2.moveTo(-endPoint);
  
  while (stepper1.distanceToGo() != 0) {
    stepper1.run();
    stepper2.run();
  }

  stepper1.setCurrentPosition(0);
  stepper2.setCurrentPosition(0);

  digitalWrite(A1, LOW); 
  
}

void robot::fine_lavoro(void) {


  stepper1.stop();
  stepper2.stop();

  stepper1.disableOutputs();
  stepper2.disableOutputs();
 
  while (true) {
    digitalWrite(13, HIGH);
    delay(200);
    digitalWrite(13, LOW);
    delay(200);
  }

}

bool robot::sensore_fine_corsa() {

   return digitalRead(pinFinecorsa);

}
