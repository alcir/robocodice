#include "Robot.h" //include the declaration for this class

#define TRIGGER_PIN 10
#define ECHO_PIN 11
#define MAX_DISTANCE 50

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

Robot::Robot(AccelStepper stepperUno, AccelStepper stepperDue, unsigned int avanzamento){
  
  _distanza = 0;

  steps = avanzamento;

  stepper1 = stepperUno;
  stepper2 = stepperDue;
  
  pinFinecorsa = A5;

  pingSpeed = 500; // How frequently are we going to send out a ping (in milliseconds). 50ms would be 20 times a second.
  
  pingTimer = millis(); // Start now.

}
 
// <<destructor>>
Robot::~Robot(){/*nothing to destruct*/}

int Robot::guarda() {

  if (millis() >= this->pingTimer) {   // pingSpeed milliseconds since last ping, do another ping.
    pingTimer += pingSpeed;             // Set the next ping time.

	 _distanza=sonar.ping_cm();

	 return _distanza;

  }

   return 100;  // si assume che la distanza cercata non sia superiore a un metro

}

void Robot::reset() {

  stepper1.setMaxSpeed(2000.0);
  stepper1.setAcceleration(500.0);
    
  stepper2.setMaxSpeed(2000.0);
  stepper2.setAcceleration(500.0);

}

void Robot::anima(void) {

  this->reset();
 
  pinMode(13, OUTPUT); // led alto
  pinMode(A4, OUTPUT); // led retromarcia
  // pinMode(A3, OUTPUT); 
  pinMode(A2, OUTPUT); // led sinistro
  pinMode(A1, OUTPUT); // led destro

  pinMode(pinFinecorsa, INPUT);

}

void Robot::vai_avanti() {
	vai_avanti(this->steps);
}

void Robot::vai_avanti(unsigned int passi) {

  this->reset();

  endPoint = passi;
   
  //Serial.println("Avantii");
  //Serial.println(endPoint);

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

}

void Robot::avanti_tutta(void) {

  this->reset();
  stepper1.setSpeed(1000);
  stepper2.setSpeed(-1000);

  stepper1.runSpeed();
  stepper2.runSpeed();
  
}

void Robot::vai_indietro() {

	vai_indietro(this->steps/2);

}

void Robot::vai_indietro(unsigned int passi) {

  digitalWrite(A4, HIGH);

  stepper1.setCurrentPosition(0);
  stepper2.setCurrentPosition(0);
 
  endPoint = passi;

  stepper1.setSpeed(2000);
  stepper2.setSpeed(2000);
  
  // stepper1.moveTo(-endPoint/2);  
  // stepper2.moveTo(+endPoint/2);

  stepper1.moveTo(-endPoint);  
  stepper2.moveTo(+endPoint);
 
  while (stepper1.distanceToGo() != 0) {
    // stepper1.run();
    // stepper2.run();
    
    stepper1.setSpeed(1000);
    stepper2.setSpeed(1000);
      
    stepper1.runSpeedToPosition();
    stepper2.runSpeedToPosition();
  }

  stepper1.setCurrentPosition(0);
  stepper2.setCurrentPosition(0);

  digitalWrite(A4, LOW);  

}

void Robot::girati_verso_sinistra() {

	girati_verso_sinistra(this->steps/2);

}

void Robot::girati_verso_sinistra(unsigned int passi) {

  digitalWrite(A2, HIGH); 
  
  this->reset();

  stepper1.setCurrentPosition(0);
  stepper2.setCurrentPosition(0);

  endPoint = passi;

  Serial.println("sin ");
  Serial.println(endPoint);

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

void Robot::girati_verso_destra() {

	girati_verso_destra(this->steps/2);

}

void Robot::girati_verso_destra(unsigned int passi) {

  digitalWrite(A1, HIGH); 
  
  this->reset();

  stepper1.setCurrentPosition(0);
  stepper2.setCurrentPosition(0);

  endPoint = passi;

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

void Robot::fine_lavoro(void) {

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

void Robot::attendi(void) {
 // Serial.println("attendo");
  stepper1.stop();
  stepper2.stop();
  stepper1.disableOutputs();
  stepper2.disableOutputs();
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);
  delay(200);
}

bool Robot::sensore_fine_corsa() {

   return digitalRead(pinFinecorsa);

}
