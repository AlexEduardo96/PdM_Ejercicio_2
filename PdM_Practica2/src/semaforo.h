#include <Arduino.h>

typedef enum  {
  ESTADO_INICIAL,
  ESTADO_1,
  ESTADO_2
}estadoMEF_t;

typedef enum {
  NORMAL_MODE,
  DISCONNECTED_MODE,
  ALARM_MODE,
} fsmTrafficLightMode_t;

extern fsmTrafficLightMode_t fsmTrafficMode;
extern estadoMEF_t estadoActual;
extern int16_t baseTime;                  // Base time for the program when it starts

void fsmTrafficLightInit(int16_t LED_GREEN, int16_t LED_YELLOW, int16_t LED_RED) {
  fsmTrafficMode = NORMAL_MODE;
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, LOW);  
}

void setTrafficLightMode(fsmTrafficLightMode_t mode,int16_t LED_GREEN, int16_t LED_YELLOW, int16_t LED_RED) {
  fsmTrafficMode = mode;
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, LOW);
}

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


void ActualizarMEF(int16_t baseTime,int16_t LED_GREEN, int16_t LED_YELLOW, int16_t LED_RED) {
  
  switch (estadoActual) {
    case ESTADO_INICIAL:
      if (nbDelay(baseTime*4)) {
        digitalWrite(LED_GREEN, HIGH);
        digitalWrite(LED_YELLOW, LOW);
        digitalWrite(LED_RED, LOW);
        estadoActual = ESTADO_1;
      }
      break;
    case ESTADO_1:
      if (nbDelay(baseTime*6)) {
        digitalWrite(LED_GREEN, HIGH);
        digitalWrite(LED_YELLOW, HIGH);
        digitalWrite(LED_RED, LOW);
        estadoActual = ESTADO_2;
      }
      break;
    case ESTADO_2:
      if (nbDelay(baseTime)) {
        digitalWrite(LED_GREEN, LOW);
        digitalWrite(LED_YELLOW, LOW);
        digitalWrite(LED_RED, HIGH);
        estadoActual = ESTADO_INICIAL;
      }
      
      break;
  }
}

void fsmTrafficLightUpdate(int16_t LED_GREEN, int16_t LED_YELLOW, int16_t LED_RED) {
  switch (fsmTrafficMode) {
    case NORMAL_MODE:
    ActualizarMEF(baseTime, LED_GREEN, LED_YELLOW, LED_RED);
    break;
    case DISCONNECTED_MODE:
      if (nbDelay(baseTime)) {
        digitalWrite(LED_YELLOW, !digitalRead(LED_YELLOW));
      }
      break;
    case ALARM_MODE:
      if (nbDelay(baseTime)) {
        digitalWrite(LED_RED, !digitalRead(LED_RED));
      }
      break;
  }
}

void InicializarMEF() {
  estadoActual = ESTADO_INICIAL;
}


