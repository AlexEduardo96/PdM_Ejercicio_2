#include <Arduino.h>
#include <stdio.h>

typedef enum {
  BUTTON_UP,
  BUTTON_DOWN,
  BUTTON_FALLING,
  BUTTON_RISING,
} fsmButtonState_t;

typedef struct {
  int16_t tecla;
  int16_t delay;
  fsmButtonState_t estado;
} dbn_t;

extern dbn_t dbnSW1;
extern dbn_t dbnSW2;


extern int16_t baseTime;                  // Base time for the program when it starts

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


void fsmButtonInit(dbn_t* data) {
  data->estado = BUTTON_UP;
}


void fsmButtonError(dbn_t* data) {
  data->estado = BUTTON_UP;
}


typedef void (*PrintFunction)(dbn_t* data);

void changeTrafficLightMode(int16_t LED_GREEN, int16_t LED_YELLOW, int16_t LED_RED);
void buttonPressed(dbn_t* data, int16_t SW1, int16_t SW2,int16_t LED_GREEN, int16_t LED_YELLOW, int16_t LED_RED, PrintFunction printFunc) {
  if (data->tecla == SW1) {
    // Cambiar la base de tiempo del modo normal
    baseTime = baseTime / 2;

    if (baseTime < 250) {
      baseTime = 1000;
    }
    printFunc(data);
  } else if (data->tecla == SW2) {
    // Cambiar el modo de operación del semáforo
    changeTrafficLightMode(LED_GREEN,LED_YELLOW,LED_RED);
    printFunc(data);
  }
  //printFunc("Tecla presionada: ", data);
}




void buttonReleased(dbn_t* data, int16_t SW1, int16_t SW2, PrintFunction printFunc) {
  //if (data->tecla == SW1) {
    printFunc(data);
  //} else if (data->tecla == SW2) {
    // No se requiere ninguna acción específica al soltar el botón SW2
  //}
}

void fsmButtonUpdate(dbn_t* data,int16_t SW1, int16_t SW2,int16_t LED_GREEN, int16_t LED_YELLOW, int16_t LED_RED, PrintFunction printFunc) {
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
          buttonPressed(data, SW1,SW2,LED_GREEN,LED_YELLOW,LED_RED, printFunc);
        } else {
          data->estado = BUTTON_UP;
        }
      }
      break;
    case BUTTON_RISING:
      if (nbDelay(data->delay)) {
        if (digitalRead(data->tecla)) {
          data->estado = BUTTON_UP;
          buttonReleased(data, SW1, SW2, printFunc);
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

