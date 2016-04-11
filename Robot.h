#ifndef robot_H
#define robot_H

#include <Arduino.h>
#include <AccelStepper.h>
#include <NewPing.h>

class Robot {
public:
   Robot(AccelStepper stepperUno, AccelStepper stepperDue, unsigned int Steps);
   ~Robot();
   void anima();
	void vai_avanti();
   void vai_avanti(unsigned int endPoint);
   void avanti_tutta();
   void vai_indietro();
   void vai_indietro(unsigned int endPoint);
   void vai_avanti_fisso();
   void girati_verso_destra();
   void girati_verso_sinistra();
	void girati_verso_destra(unsigned int endPoint);
   void girati_verso_sinistra(unsigned int endPoint);	
   void fine_lavoro();
   void attendi();
   bool sensore_fine_corsa();
   int guarda(); 

private:
   void reset();

   int pinFinecorsa;

   unsigned int TRIGGER_PIN;
   unsigned int ECHO_PIN;
   unsigned int MAX_DISTANCE;
   unsigned int _distanza;

   unsigned int pingSpeed;  // How frequently are we going to send out a ping (in milliseconds). 50ms would be 20 times a second.
   unsigned long pingTimer; // Holds the next ping time.

   unsigned int steps;
   int endPoint; // numero di step
   AccelStepper stepper1;
   AccelStepper stepper2;
};

#endif
