/*
 * Keypad.c
 *
 *  Created on: Sep 10, 2022
 *      Author: ANOOS
 */

#include "../../../INCLUDE/HAL/KEYPAD/Keypad.h"
#include "../../../INCLUDE/MCAL/DIO/DIO.h"
#include"../../../SERVICES/std_types.h"
#include "util/delay.h"

u8 KeyPadValues[4][4]={
		{7,8,9,'%'},
		{4,5,6,'*'},
		{1,2,3,'-'},
		{'o',0,'=','+'}
};


u8 Keypad_voidGetPressedKey(void)
{

u8 KeyPadResult=0xff;



for(u8 col=0;col<4;col++)
 {
	DIO_enuSetPinValue(DIO_u8_PORTD,col,DIO_u8_LOW); //to activate  col
  for(u8 row=0 ;row<4;row++)
  {

	  if(DIO_u8GetPinValue(DIO_u8_PORTD,row+4)==0)
	  {


		  while(DIO_u8GetPinValue(DIO_u8_PORTD,row+4)==0); // to save value after press

	         _delay_ms(10);

	         KeyPadResult=KeyPadValues[col][row];

	  }


  }
  DIO_enuSetPinValue(DIO_u8_PORTD,col,DIO_u8_HIGH); //to close colmon

 }
return KeyPadResult;
}
////////////////////////////////////////////////
void Keypad_voidSetKeyPadDir(){


	DIO_enuSetPortDirection(DIO_u8_PORTD,0x0f);
	DIO_enuSetPortValue(DIO_u8_PORTD,0xff); // F for 1111 of coulms and F for pull up



}
