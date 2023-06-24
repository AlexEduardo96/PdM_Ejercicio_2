/****************************Declare libraries ********************************/
#include "teclas.h"
#include <Arduino.h>
/******************************Prototype Function******************************/
typedef void (*PrintFunction)(dbn_t* data);
void fsmButtonInit(dbn_t* data);
void fsmButtonUpdate(dbn_t* data,int16_t SW1, int16_t SW2,int16_t LED_GREEN, int16_t LED_YELLOW, int16_t LED_RED, PrintFunction printFunc);
void fsmButtonError(dbn_t* data);
void buttonPressed(dbn_t* data ,int16_t SW1, int16_t SW2,int16_t LED_GREEN, int16_t LED_YELLOW, int16_t LED_RED, PrintFunction printFunc);
void buttonReleased(dbn_t* data, int16_t SW1, int16_t SW2, PrintFunction printFunc);
int16_t nbDelay(int16_t t_delay);