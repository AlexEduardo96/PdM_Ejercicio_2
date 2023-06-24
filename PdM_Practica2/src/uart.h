#include "Arduino.h"

void myPrint(dbn_t* data){
  
  if (data->estado == 1){
    Serial.print("Tecla: ");
    Serial.print(data->tecla-1);
    Serial.print("\t Estado: Presionado\n");
  } else if (data->estado == 0){
    Serial.print("Tecla: ");
    Serial.print(data->tecla-1);
    Serial.print("\t Estado: Liberado\n");
  }
  
}

