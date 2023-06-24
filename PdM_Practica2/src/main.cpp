
#include "teclas.h"
#include "semaforo.h"
#include <Arduino.h>
#include <stdio.h>
#include "uart.h"

/**************** Constant & variables declaration **********/
const int16_t LED_GREEN = 12;
const int16_t LED_YELLOW = 11;
const int16_t LED_RED = 10;


const int16_t SW1 = 2;
const int16_t SW2 = 3;

/************ Finite State Machine for traffic light **********/

estadoMEF_t estadoActual;

//void myPrint(const char* message); 

/*void myPrint(const char* message) {
  Serial.println(message);
}*/
/*************************************************************/

/*typedef enum {
  BUTTON_UP,
  BUTTON_DOWN,
  BUTTON_FALLING,
  BUTTON_RISING,
} fsmButtonState_t;
*/
/*
typedef enum {
  NORMAL_MODE,
  DISCONNECTED_MODE,
  ALARM_MODE,
} fsmTrafficLightMode_t;
*/

fsmTrafficLightMode_t fsmTrafficMode = NORMAL_MODE;    // Operation mode for traffic light

int16_t baseTime = 500;                  // Base time for the program when it starts
/*
typedef struct {
  int16_t tecla;
  int16_t delay;
  fsmButtonState_t estado;
} dbn_t;
*/
dbn_t dbnSW1 = {SW1, 40, BUTTON_UP};
dbn_t dbnSW2 = {SW2, 40, BUTTON_UP};
/**************************************************************/



/************************** Function prototypes ***************/
//int16_t nbDelay(int16_t t_delay);
//void fsmButtonInit(dbn_t* data);
//void fsmButtonUpdate(dbn_t* data);
//void fsmButtonError(dbn_t* data);
//void buttonPressed(int16_t tecla);
//void buttonReleased(int16_t tecla);
//void fsmTrafficLightInit(void);
//void fsmTrafficLightUpdate(void);
//void setTrafficLightMode(fsmTrafficLightMode_t mode);
//void changeTrafficLightMode(void);
//void ActualizarMEF(int16_t baseTime);
//void InicializarMEF();

void setup() {
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  Serial.begin(9600);
}



void loop() {
  InicializarMEF();
  fsmButtonInit(&dbnSW1);
  fsmButtonInit(&dbnSW2);
  fsmTrafficLightInit(LED_GREEN, LED_YELLOW, LED_RED);
  while (1) {
    fsmButtonUpdate(&dbnSW1,SW1,SW2,LED_GREEN, LED_YELLOW, LED_RED, myPrint);
    fsmButtonUpdate(&dbnSW2,SW1,SW2,LED_GREEN, LED_YELLOW, LED_RED, myPrint);
    fsmTrafficLightUpdate(LED_GREEN, LED_YELLOW, LED_RED);
  }
}
/*
void fsmButtonInit(dbn_t* data) {
  data->estado = BUTTON_UP;
}*/
/*
void fsmButtonUpdate(dbn_t* data) {
  switch (data->estado) {
    case BUTTON_UP:
      if (!digitalRead(data->tecla)) {
        data->estado = BUTTON_FALLING;
      }
      break;
    case BUTTON_DOWN:
      if (digitalRead(data->tecla)) {
        data->estado = BUTTON_RISING;
      }
      break;
    case BUTTON_FALLING:
      if (nbDelay(data->delay)) {
        if (!digitalRead(data->tecla)) {
          data->estado = BUTTON_DOWN;
          buttonPressed(data->tecla);
        } else {
          data->estado = BUTTON_UP;
        }
      }
      break;
    case BUTTON_RISING:
      if (nbDelay(data->delay)) {
        if (digitalRead(data->tecla)) {
          data->estado = BUTTON_UP;
          buttonReleased(data->tecla);
        } else {
          data->estado = BUTTON_DOWN;
        }
      }
      break;
    default:
      fsmButtonError(data);
      break;
  }
}
*/
/*
void fsmButtonError(dbn_t* data) {
  data->estado = BUTTON_UP;
}

void buttonPressed(int16_t tecla) {
  if (tecla == SW1) {
    // Cambiar la base de tiempo del modo normal
    baseTime = baseTime / 2;

    if (baseTime < 250) {
      baseTime = 1000;
    }
  } else if (tecla == SW2) {
    // Cambiar el modo de operación del semáforo
    changeTrafficLightMode();
  }
}

void buttonReleased(int16_t tecla) {
  if (tecla == SW1) {
    // No se requiere ninguna acción específica al soltar el botón SW1
  } else if (tecla == SW2) {
    // No se requiere ninguna acción específica al soltar el botón SW2
  }
}
*/

/*
void fsmTrafficLightInit(void) {
  fsmTrafficMode = NORMAL_MODE;
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, LOW);  
}
*/
/*
void setTrafficLightMode(fsmTrafficLightMode_t mode) {
  fsmTrafficMode = mode;
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, LOW);
}
*/
/*
void changeTrafficLightMode(void) {
  switch (fsmTrafficMode) {
    case NORMAL_MODE:
      setTrafficLightMode(DISCONNECTED_MODE);
      break;
    case DISCONNECTED_MODE:
      setTrafficLightMode(ALARM_MODE);
      break;
    case ALARM_MODE:
      setTrafficLightMode(NORMAL_MODE);
      break;
  }
}
*/
/*
void fsmTrafficLightUpdate(void) {
  switch (fsmTrafficMode) {
    case NORMAL_MODE:
    ActualizarMEF(baseTime);
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
*/
/*
int16_t nbDelay(int16_t t_delay) {
  int16_t t_base = 1;
  static int16_t count = 0;
  int16_t n_time = t_delay / t_base;

  if (count >= n_time) {
    count = 0;
    return 1;
  } else {
    delay(t_base);
    count++;
    return 0;
  }
}
*/

/*
void InicializarMEF() {
  estadoActual = ESTADO_INICIAL;
}

void ActualizarMEF(int16_t baseTime) {
  
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
*/