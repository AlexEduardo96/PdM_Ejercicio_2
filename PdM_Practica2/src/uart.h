/****************************Declare libraries***************************/
#include "Arduino.h"
/***************************Function to print key state**************/
void myPrint(dbn_t* data){
  if (data->estado == 1){
    Serial.print("Tecla: ");
    Serial.print(data->tecla-1); //Print in the UART communication of the state of the Key
    Serial.print("\t Estado: Presionado\n");
  } else if (data->estado == 0){
    Serial.print("Tecla: ");
    Serial.print(data->tecla-1); //Print in the UART communication of the state of the Key
    Serial.print("\t Estado: Liberado\n");
  }
  
}

