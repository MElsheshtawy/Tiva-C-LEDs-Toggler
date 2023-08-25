#include <stdio.h>
#include "tm4c123gh6pm.h"
#include "DIO.h"

int x =0;
void start_it();
void GPIO_Portf_handler(){
  DIO_WritePin(PORTF,P1,0);
  DIO_WritePin(PORTF,P2,0);
  DIO_WritePin(PORTF,P3,0);
  if(GPIO_PORTF_MIS_R & 0X1){
    Set_Bit(GPIO_PORTF_ICR_R,P0);
    if(x==3||x==0)
      x=1;
    else if(x==1)
      x=2;
    else
      x=3;
  }
  else if(GPIO_PORTF_MIS_R & (1<<4)){
    Set_Bit(GPIO_PORTF_ICR_R,P4);
    x=0;
  } 
}
int main()
{
  start_it();
  while(1){
    switch(x){
    case 0:
      toggle_pin(PORTF,P1);
      DIO_WritePin(PORTF,P2,0);
      DIO_WritePin(PORTF,P3,0);
      delay(500);
      break;
     case 1:
      toggle_pin(PORTF,P2);
      DIO_WritePin(PORTF,P1,0);
      DIO_WritePin(PORTF,P3,0);
      delay(500);
      break;
     case 2:
      toggle_pin(PORTF,P3);
      DIO_WritePin(PORTF,P1,0);
      DIO_WritePin(PORTF,P2,0);
      delay(500);
      break;
    case 3:
      toggle_pin(PORTF,P2);
      toggle_pin(PORTF,P3);
      DIO_WritePin(PORTF,P1,0);
      delay(500);
      break;
    }
  }
    return 0;
}
void start_it(){
  DIO_Init(PORTF,P0,INPUT_PIN);
  DIO_Init(PORTF,P1,OUTPUT_PIN);
  DIO_Init(PORTF,P2,OUTPUT_PIN);
  DIO_Init(PORTF,P3,OUTPUT_PIN);
  DIO_Init(PORTF,P4,INPUT_PIN);
  DIO_InterruptInit(PORTF,P0);
  DIO_InterruptInit(PORTF,P4);
  DIO_WritePin(PORTF,P2,0);
  DIO_WritePin(PORTF,P3,0);
  DIO_WritePin(PORTF,P1,1);
  return;
}