/*
 * TIMER.h
 *
 *  Created on: Oct 2, 2022
 *      Author: ANOOS
 */

#ifndef INCLUDE_MCAL_TIMER_TIMER_H_
#define INCLUDE_MCAL_TIMER_TIMER_H_

#include "../../../SERVICES/STD_TYPES.h"
/*TIMER CHANNALS*/

#define TIMER_CHANNEL_A 0
#define TIMER_CHANNEL_B 1

/*WAVE FORM GENERATION MODE */

// normal
#define TIMER_NORMAL_MODE 0

// CTC
#define TIMER_CTC_MODE 1

//PWM

  //PHASE CORRECT
#define TIMER_PWM_PHASE_CORRECT_ICR_MODE 2
  //FAST
#define TIMER_FAST_PWM_ICR_MODE 3

/*COMPARE OUTPUT MODE*/

//NON PWM
#define TIMER_COM_NORMAL_OPERATION 0
#define TIMER_COM_TOGGLE 1
#define TIMER_COM_CLEAR 2
#define TIMER_COM_SET 3

// PWM
#define TIMER_COM_NORMAL_OPERATION 0
#define TIMER_NON_INVERTING 1
#define TIMER_INVERTING 2

/*PRESCALLING*/

#define TIMER_NO_CLK 0
#define TIMER_CLK_DEVIDED_BY_1 1
#define TIMER_CLK_DEVIDED_BY_8 2
#define TIMER_CLK_DEVIDED_BY_64 3
#define TIMER_CLK_DEVIDED_BY_256 4
#define TIMER_CLK_DEVIDED_BY_1024 5

//overflow enable
#define TIMER_OVERFLOW_ENABEL 0
#define TIMER_OVERFLOW_DISABEL 1


/*INIT struct */

typedef struct{

	u8 channel;
	u8 WGM;
	u8 COM;
	u8 prescale;
	u8 overflowINT;

}str_timer;

void TIMER_voidInit(str_timer *Add_ptrTimer ) ;

//void ITMER_voidPWMEnable()



#endif /* INCLUDE_MCAL_TIMER_TIMER_H_ */
