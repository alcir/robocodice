#include <AccelStepper.h>
#include <NewPing.h>
#include <Robot.h>


#define HALFSTEP 8

// motor pins
#define motorPin1  2     // IN1 on the ULN2003 driver 1
#define motorPin2  3     // IN2 on the ULN2003 driver 1
#define motorPin3  4     // IN3 on the ULN2003 driver 1
#define motorPin4  5     // IN4 on the ULN2003 driver 1

#define motorPin5  6     // IN1 on the ULN2003 driver 2
#define motorPin6  7     // IN2 on the ULN2003 driver 2
#define motorPin7  8    // IN3 on the ULN2003 driver 2
#define motorPin8  9    // IN4 on the ULN2003 driver 2

// #define buttonPin A5

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);
AccelStepper stepper2(HALFSTEP, motorPin5, motorPin7, motorPin6, motorPin8);

bool buttonState = 0;

unsigned int randNumber;
unsigned int Distanza = 0;

Robot robot(stepper1, stepper2, 4096);

void setup() {
  delay(1000); //sime time to put the robot down after swithing it on
  //pinMode(buttonPin, INPUT);
  //stepper1.setMaxSpeed(3000.0);
  //stepper1.setSpeed(1000);

  //stepper2.setMaxSpeed(2000.0);
  //stepper2.setSpeed(-1000);

  robot.anima();
  Serial.begin(115200);
  
  randomSeed(analogRead(0));
}


void loop() {

 //Serial.println(robot.sensore_fine_corsa());
 int Distanza = robot.guarda();
  if ((Distanza > 9 or Distanza == 0) and robot.sensore_fine_corsa() == 0) {
    
    robot.avanti_tutta();
    
  } else {
    // robot.girati_verso_destra();
    // robot.girati_verso_sinistra();
    // robot.vai_avanti();
    robot.vai_indietro();
    
    randNumber = random(1, 100);

    if (randNumber > 50 ) {
      robot.girati_verso_destra();
    } else {
      robot.girati_verso_sinistra();
    }
    
    Distanza = 0;
    // robot.vai_avanti();
    //stepper2.runSpeed();
    //stepper1.moveTo(12000);
  }
}
