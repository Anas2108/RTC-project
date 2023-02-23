/*
 * main1.c
 *
 *  Created on: Feb 5, 2023
 *      Author: ANOOS
 */

#include "../../INCLUDE/MCAL/DIO/Dio.h"
#include "../../INCLUDE/MCAL/GIE/GIE.h"
#include "../../INCLUDE/MCAL/EXTI/EXTI.h"
#include "../../INCLUDE/MCAL/TIMER/TIMER.h"
#include "../../INCLUDE/MCAL/DIO/Dio_prv.h"
#include "../../INCLUDE/MCAL/GIE/GIE_prv.h"
#include "../../INCLUDE/MCAL/TIMER/TIMER_prv.h"
#include "../../INCLUDE/HAL/SEGMENT/Segment.h"
#include "../../INCLUDE/HAL/SWITCH/Switch.h"
#include "../../SERVICES/bit_utilies.h"
#include "../../INCLUDE/HAL/LCD/Lcd.h"
#include <avr/interrupt.h>
#include "util/delay.h"


#define DELAY_TO_PARALLEL_SEVSG   0.5
#define KEY_NOT_PRESSED 0xff
#define CLEAR_THE_SCREEN 1

 static u8 sec1=0;
 static u8 sec2=0;
 static u8 min1=0;
 static u8 min2=0;
 static u8 hrs1=0;
 static u8 hrs2=0;

 u8 seven_segmentArray[10]={0x3F, 0x6, 0x5B, 0x4F, 0x66, 0x6D,0x7D, 0x27, 0x7F,0x6F};




 segment_str segments={

 	.portId= DIO_u8_PORTC,

 	.segmentType=SEGMENT_COMMON_CATHOD

 	};

 Lcd_tstrucCfg Lcd1={
 			.DataPortId=DIO_u8_PORTB,
 			.CtrlPortId=DIO_u8_PORTA,
 			.RS_Pin=7,
 			//.RW_Pin=1,
 			.EN_Pin=6
 	};




/************************** Timer1 INT **************************/

ISR(TIMER1_OVF_vect){
	TCNT1 = 34286;   // for 1 sec at 8 MHz
	sec1++;
	if (sec1>9)
	{
		sec1=0;
	  sec2+=1;

	}

	if (sec2>5)
		{
		 sec1=0;
		 sec2=0;
		 min1+=1;

		}
	if (min1>9)
		{
		sec1=0;
		sec2=0;
		min1=0;
		min2+=1;


		}

	if (min2>5)
			{
			sec1=0;
			sec2=0;
			min1=0;
			min2=0;
			hrs1+=1;


			}
	if (hrs1>9)
				{
			sec1=0;
			sec2=0;
			min1=0;
			min2=0;
			hrs1=0;
			hrs2+=1;


				}
	if (hrs2>1)

  {
		if(hrs1>3){
				sec1=0;
				sec2=0;
				min1=0;
				min2=0;
				hrs1=0;
				hrs2=0;
		}

	}


}

/************************* External INT *************************/

ISR(INT0_vect){
			  sec1=0;
			  sec2=0;
			  min1=0;   // to reset the timer
			  min2=0;
			  hrs1=0;
			  hrs2=0;

}


ISR(INT1_vect){
	CLR_BIT(TCCR1B,2); CLR_BIT(TCCR1B,1); CLR_BIT(TCCR1B,0); //to stop timer
}


ISR(INT2_vect){
	 SET_BIT(TCCR1B,2); CLR_BIT(TCCR1B,1); CLR_BIT(TCCR1B,0); //to start
}



/***************************** FUNCTIONS ****************************/

void segDataDisplay(void); // to display the values of 7-SEG

void segClearAllDigits(void);









int main(void)
{


	str_timer timer1 ={

		.WGM=TIMER_NORMAL_MODE,
		.overflowINT=TIMER_OVERFLOW_ENABEL,
		.channel=TIMER_CHANNEL_A,
		.COM=TIMER_COM_NORMAL_OPERATION,
		.prescale=TIMER_CLK_DEVIDED_BY_256
	};



		Switch_str sw0={

			.portId=DIO_u8_PORTD,
			.pinId=DIO_u8_PIN2

			};

		Switch_str sw1={

					.portId=DIO_u8_PORTD,
					.pinId=DIO_u8_PIN3

					};

		Switch_str sw2={

					.portId=DIO_u8_PORTB,
					.pinId=DIO_u8_PIN2

					};

SEGMENT_voidSetSegmentDir(&segments);

Keypad_voidSetKeyPadDir();

Lcd_vidInit(&Lcd1);

SWITCH_voidSetSwitchDir(&sw0);
SWITCH_voidSetSwitchDir(&sw1);
SWITCH_voidSetSwitchDir(&sw2);



GIE_voidGlobalInterruptEnable();

EXTI_voidEnable(EXTI_INT_0,EXTI_INT_0_FALLING_EDGE);
EXTI_voidEnable(EXTI_INT_1,EXTI_INT_0_FALLING_EDGE);
EXTI_voidEnable(EXTI_INT_2,EXTI_INT_0_FALLING_EDGE);

TIMER_voidInit(&timer1);

DIO_enuSetPortDirection(DIO_u8_PORTA,DIO_u8_PORT_OUTPUT);

TCNT1 = 34286;   // for 1 sec at 8 MHz and 256 prescale


//u8 mode;

u8 digit=0;
u8 clkDigits[6]={hrs2,hrs1,min2,min1,sec2,sec1};


u8 Set_Massage[]="Set the clock!";
u8 clock_Massage[]="The Clock mode";
u8 timer_Massage[]="The Timer mode";
u8 clock_selection_Massage[]="Clock:Press + ";
u8 timer_selection_Massage[]="Timer:Press - ";
u8 clock_DoneSet_Massage[]="Done!";
u8 exit_Massage[]="Press % to exit!";


Lcd_WriteString(&Lcd1,clock_selection_Massage);

Lcd_gotoPosition(&Lcd1,1,0);

Lcd_WriteString(&Lcd1,timer_selection_Massage);


while (1)
  {

	//Lcd_vidSendCommand(&Lcd1,CLEAR_THE_SCREEN);



u16 locVarPressedKey=Keypad_voidGetPressedKey();

 if(locVarPressedKey!=KEY_NOT_PRESSED)
  {
	 //Lcd_WriteString(&Lcd1,clock_selection_Massage);

	if(locVarPressedKey=='*')
	{
		CLR_BIT(TCCR1B,2); CLR_BIT(TCCR1B,1); CLR_BIT(TCCR1B,0); //to stop timer
		Lcd_vidSendCommand(&Lcd1,CLEAR_THE_SCREEN);
		Lcd_WriteString(&Lcd1,clock_Massage);
		Lcd_gotoPosition(&Lcd1,1,0);
		Lcd_WriteString(&Lcd1,Set_Massage);
		segClearAllDigits();

		while(digit<=5){



		do{
					locVarPressedKey=Keypad_voidGetPressedKey();

					segDataDisplay();
		  }while (locVarPressedKey==KEY_NOT_PRESSED);


		if(locVarPressedKey!=KEY_NOT_PRESSED &&(locVarPressedKey>='0'&&locVarPressedKey<='9'))
		  {
			clkDigits[digit]=locVarPressedKey;
			digit++;



		  }

		if(digit==6){
			TCNT1 = 34286;
						 SET_BIT(TCCR1B,2); CLR_BIT(TCCR1B,1); CLR_BIT(TCCR1B,0); //to start
		while(1)
		  {

			segDataDisplay();
			Lcd_WriteString(&Lcd1,clock_DoneSet_Massage);
			Lcd_gotoPosition(&Lcd1,1,0);
			Lcd_WriteString(&Lcd1,exit_Massage);
									Lcd_WriteString(&Lcd1,Set_Massage);
			if (Keypad_voidGetPressedKey()=='%')
			{
				Lcd_vidSendCommand(&Lcd1,CLEAR_THE_SCREEN);
						Lcd_WriteString(&Lcd1,clock_selection_Massage);
						Lcd_gotoPosition(&Lcd1,1,0);
						Lcd_WriteString(&Lcd1,timer_selection_Massage);
						break;

			}


		  }
		}

	}

	 }



	else if(locVarPressedKey=='%')
	{
		Lcd_vidSendCommand(&Lcd1,CLEAR_THE_SCREEN);
				Lcd_WriteString(&Lcd1,timer_Massage);

		segClearAllDigits();

		while(1)
		{
			segDataDisplay();

			if(Keypad_voidGetPressedKey()=='%'){
				Lcd_vidSendCommand(&Lcd1,CLEAR_THE_SCREEN);
						Lcd_WriteString(&Lcd1,clock_Massage);
						Lcd_gotoPosition(&Lcd1,1,0);
						Lcd_WriteString(&Lcd1,Set_Massage);

				break;
			}

		}

	}


  }



	//segDataDisplay();
 }
}

void segDataDisplay(void)

			{   DIO_enuSetPortValue(DIO_u8_PORTA,0b11111110);
				SEGMENT_voidSetSegmentVal(&segments,seven_segmentArray[sec1]);

				  _delay_ms(DELAY_TO_PARALLEL_SEVSG);

				 DIO_enuSetPortValue(DIO_u8_PORTA,0b11111101);
			     SEGMENT_voidSetSegmentVal(&segments,seven_segmentArray[sec2]);
			      _delay_ms(DELAY_TO_PARALLEL_SEVSG);

			     DIO_enuSetPortValue(DIO_u8_PORTA,0b11111011);
			     SEGMENT_voidSetSegmentVal(&segments,seven_segmentArray[min1]);
			     	 _delay_ms(DELAY_TO_PARALLEL_SEVSG);


			     DIO_enuSetPortValue(DIO_u8_PORTA,0b11110111);
			     SEGMENT_voidSetSegmentVal(&segments,seven_segmentArray[min2]);
			         _delay_ms(DELAY_TO_PARALLEL_SEVSG);


			         DIO_enuSetPortValue(DIO_u8_PORTA,0b11101111);
			       SEGMENT_voidSetSegmentVal(&segments,seven_segmentArray[hrs1]);
			      	  _delay_ms(DELAY_TO_PARALLEL_SEVSG);


			      	 DIO_enuSetPortValue(DIO_u8_PORTA,0b11011111);
			       SEGMENT_voidSetSegmentVal(&segments,seven_segmentArray[hrs2]);
			          _delay_ms(DELAY_TO_PARALLEL_SEVSG);


			}

void segClearAllDigits(void)
	{
		sec1=0;
		sec2=0;
		min1=0;
		min2=0;
		hrs1=0;
		hrs2=0;


	}
