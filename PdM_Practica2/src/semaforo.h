
#include <Arduino.h>    //libery to arduino

/******** Data declared as structure type ***************/
typedef enum  {
  ESTADO_INICIAL,
  ESTADO_1,
  ESTADO_2
}estadoMEF_t;

/******** Data declared as enumeration type ***************/
typedef enum {
  NORMAL_MODE,
  DISCONNECTED_MODE,
  ALARM_MODE,
} fsmTrafficLightMode_t;

/*********** declaration of variables as external *********/
extern fsmTrafficLightMode_t fsmTrafficMode;
extern int16_t baseTime;     // Base time for the program when it starts

estadoMEF_t estadoActual;

/*********** function to initialize MEF of the traffic light*/
void fsmTrafficLightInit(int16_t LED_GREEN, int16_t LED_YELLOW, int16_t LED_RED) {
  fsmTrafficMode = NORMAL_MODE;
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, LOW);  
}

/********* function to set mode the traffic light **********/
void setTrafficLightMode(fsmTrafficLightMode_t mode,int16_t LED_GREEN, int16_t LED_YELLOW, int16_t LED_RED) {
  fsmTrafficMode = mode;
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, LOW);
}

/********* function to change mode the traffic light **********/
void changeTrafficLightMode(int16_t LED_GREEN, int16_t LED_YELLOW, int16_t LED_RED) {
  switch (fsmTrafficMode) {
    case NORMAL_MODE:
      setTrafficLightMode(DISCONNECTED_MODE, LED_GREEN, LED_YELLOW, LED_RED);
      break;
    case DISCONNECTED_MODE:
      setTrafficLightMode(ALARM_MODE, LED_GREEN, LED_YELLOW, LED_RED);
      break;
    case ALARM_MODE:
      setTrafficLightMode(NORMAL_MODE, LED_GREEN, LED_YELLOW, LED_RED);
      break;
  }
}

/****** function to initialize MEF of the traffic light in normal mode*/
void InicializarMEF() {
  estadoActual = ESTADO_INICIAL;
}

/****** Function to update state of FEM traffic light in normal mode ******/
void ActualizarMEF(int16_t baseTime,int16_t LED_GREEN, int16_t LED_YELLOW, int16_t LED_RED) {
  switch (estadoActual) {
    case ESTADO_INICIAL:
      if (nbDelay(baseTime*4)) {    //time that will last in ESTADO_2 before returning to ESTADO_INICIAL
        digitalWrite(LED_GREEN, HIGH);
        digitalWrite(LED_YELLOW, LOW);
        digitalWrite(LED_RED, LOW);
        estadoActual = ESTADO_1;
      }
      break;
    case ESTADO_1:
      if (nbDelay(baseTime*6)) {  //time that will remain in ESTADO_INICIAL before going to ESTADO_1
        digitalWrite(LED_GREEN, HIGH);
        digitalWrite(LED_YELLOW, HIGH);
        digitalWrite(LED_RED, LOW);
        estadoActual = ESTADO_2;
      }
      break;
    case ESTADO_2:
      if (nbDelay(baseTime)) {    //time that will remain in ESTADO_1 before going to ESTADO_2
        digitalWrite(LED_GREEN, LOW);
        digitalWrite(LED_YELLOW, LOW);
        digitalWrite(LED_RED, HIGH);
        estadoActual = ESTADO_INICIAL;
      }
      break;
  }
}

/************ function to update MEF of traffic light ************/
void fsmTrafficLightUpdate(int16_t LED_GREEN, int16_t LED_YELLOW, int16_t LED_RED) {
  switch (fsmTrafficMode) {
    case NORMAL_MODE:
    ActualizarMEF(baseTime, LED_GREEN, LED_YELLOW, LED_RED);
    break;
    case DISCONNECTED_MODE:
    if (nbDelay(baseTime)){
        digitalWrite(LED_YELLOW, !digitalRead(LED_YELLOW)); //flashes yellow led with a delay time of baseTime
    }
    break;
    case ALARM_MODE:
    if (nbDelay(baseTime)){
        digitalWrite(LED_RED, !digitalRead(LED_RED)); //flashes red led with a delay time of baseTime
    }
    break;
  }
}


