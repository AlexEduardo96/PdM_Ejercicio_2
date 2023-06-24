#include "semaforo.h"

/****************** Prototype functions of semaforo.h ******************/
int16_t nbDelay(int16_t t_delay);
void fsmTrafficLightInit(int16_t LED_GREEN, int16_t LED_YELLOW, int16_t LED_RED);
void setTrafficLightMode(fsmTrafficLightMode_t mode,int16_t LED_GREEN, int16_t LED_YELLOW, int16_t LED_RED);
void fsmTrafficLightUpdate(int16_t LED_GREEN, int16_t LED_YELLOW, int16_t LED_RED);
void changeTrafficLightMode(int16_t LED_GREEN, int16_t LED_YELLOW, int16_t LED_RED);
void ActualizarMEF(int16_t baseTime,int16_t LED_GREEN, int16_t LED_YELLOW, int16_t LED_RED);
void InicializarMEF();

