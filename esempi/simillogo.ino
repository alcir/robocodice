#include <Robot.h>
#include <NewPing.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
#include <SoftwareSerial.h>

#define BT_RX_PIN A0
#define BT_TX_PIN A3

#define HALFSTEP 8

#define motorPin1  2     // IN1 ULN2003 ruota destra
#define motorPin2  3     // IN2 ULN2003 ruota destra
#define motorPin3  4     // IN3 ULN2003 ruota destra
#define motorPin4  5     // IN4 ULN2003 ruota destra

#define motorPin5  6     // IN1 ULN2003 ruota sinistra
#define motorPin6  7     // IN2 ULN2003 ruota sinistra
#define motorPin7  8     // IN3 ULN2003 ruota sinistra
#define motorPin8  9     // IN4 ULN2003 ruota sinistra

AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);
AccelStepper stepper2(HALFSTEP, motorPin5, motorPin7, motorPin6, motorPin8);

SoftwareSerial BTSerial(BT_RX_PIN, BT_TX_PIN);

unsigned int Avanzamento = 4896;

char ReadBT;
String comando;

String comandoprec;

Robot NomeRobot(stepper1, stepper2, Avanzamento);

void setup() {
  
  Serial.begin(9600);
  BTSerial.begin(38400);
  randomSeed(analogRead(0));
  NomeRobot.anima(); // Diamo vita al robot
  unsigned long StartTime = millis();
  Serial.println("Pronti!");
  
}

void loop() {

  while (BTSerial.available()) {
    ReadBT = BTSerial.read();
    comando = comando + ReadBT;
    //Serial.println("messaggio");
    //Serial.println(ReadBT);
  }

  if ( comando.length() > 0 ) {
    Serial.println("Comando ricevuto");
    volatile char tokenChar = ';';
    int i = 0;

    String steps;
    String pezzo = comando;

    while (pezzo != "end") {

      pezzo = comando.substring(0, comando.indexOf(tokenChar));

      Serial.print("pezzo- ");
      Serial.println(pezzo);
      Serial.print("comando- ");
      Serial.println(comando);

      comando = processo(pezzo, comando);

    }

    Serial.println("Fine comandi");
    comando = "";

  }

  NomeRobot.attendi();

}

String processo(String pezzo, String fcomando) {

  String steps;

  Serial.print("funzione ");
  Serial.println(pezzo);

  if (pezzo.startsWith("fd")) {
    Serial.println("avanti ");
    steps = pezzo.substring(2, pezzo.length());
    Serial.println(steps.toInt());
    NomeRobot.vai_avanti(map(steps.toInt(), 0, 20, 0, 4896));
  } else if (pezzo.startsWith("bk")) {
    Serial.println("indietro ");
    steps = pezzo.substring(2, pezzo.length());
    Serial.println(steps.toInt());
    NomeRobot.vai_indietro(map(steps.toInt(), 0, 20, 0, 4896));
  } else if (pezzo.startsWith("rt")) {
    Serial.println("destra ");
    steps = pezzo.substring(2, pezzo.length());
    Serial.println(steps.toInt());
    NomeRobot.girati_verso_destra(map(steps.toInt(), 0, 180, 0, 4896));
  } else if (pezzo.startsWith("lt")) {
    Serial.println("sinistra ");
    steps = pezzo.substring(2, pezzo.length());
    Serial.println(steps.toInt());
    NomeRobot.girati_verso_sinistra(map(steps.toInt(), 0, 180, 0, 4896));
  } else if (pezzo.startsWith("repeat")) {
    Serial.println("ripeti ");
    steps = pezzo.substring(6, pezzo.length());
    Serial.println(steps.toInt());
    volatile char tokenChar = ';';
    fcomando = fcomando.substring(pezzo.length() + 1);
    String fcomandoOrig = String(fcomando);
    for (int i = 0; i < steps.toInt(); i++) {
      fcomando = String(fcomandoOrig);
      pezzo = fcomando.substring(0, fcomando.indexOf(tokenChar));
      while (pezzo != "stop") {
        Serial.print("ripetizione ");
        Serial.println(i);
        Serial.print("pezzo-- ");
        Serial.println(pezzo);
        Serial.print("comando-- ");
        Serial.println(fcomando);
        fcomando = processo(pezzo, fcomando);
        pezzo = fcomando.substring(0, fcomando.indexOf(tokenChar));       
      }
    }
  }

  fcomando = fcomando.substring(pezzo.length() + 1);

  Serial.println("...");

  return fcomando;

}
