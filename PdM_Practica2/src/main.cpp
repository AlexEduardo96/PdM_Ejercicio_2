/******************* Liberies ********************************/
#include "teclas.h"
#include "semaforo.h"
#include <Arduino.h>
#include <stdio.h>
#include "uart.h"

/**************** Constant & variables declaration **********/
const int16_t LED_GREEN = 12;   
const int16_t LED_YELLOW = 11;
const int16_t LED_RED = 10;
const int16_t SW1 = 2;    //switch to change velocity of operation 
const int16_t SW2 = 3;    //switch to change state of traffic ligth

/******* Constructor's declaration and initialization *****************/
fsmTrafficLightMode_t fsmTrafficMode = NORMAL_MODE;    // Operation mode for traffic light
int16_t baseTime = 500;                  // Base time for the program when it starts
dbn_t dbnSW1 = {SW1, 40, BUTTON_UP};
dbn_t dbnSW2 = {SW2, 40, BUTTON_UP};

void setup() {
  pinMode(SW1, INPUT);            //switches as input
  pinMode(SW2, INPUT);
  pinMode(LED_YELLOW, OUTPUT);    //leds as outpus
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  Serial.begin(9600);
}


void loop() {
  InicializarMEF();         //initialization of FEM for modes of traffic light  
  fsmButtonInit(&dbnSW1);   //initialization of FEM for button 1 
  fsmButtonInit(&dbnSW2);   //initialization of FEM for button 2 
  fsmTrafficLightInit(LED_GREEN, LED_YELLOW, LED_RED);    
  while (1) {
    fsmButtonUpdate(&dbnSW1,SW1,SW2,LED_GREEN, LED_YELLOW, LED_RED, myPrint);   //FEM to actualizate button1
    fsmButtonUpdate(&dbnSW2,SW1,SW2,LED_GREEN, LED_YELLOW, LED_RED, myPrint);   //FEM to actualizate button2
    fsmTrafficLightUpdate(LED_GREEN, LED_YELLOW, LED_RED);    //FEM to actualizate traffic light
  }
}