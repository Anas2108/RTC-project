/*
 * TIMER_prv.h
 *
 *  Created on: Oct 2, 2022
 *      Author: ANOOS
 */

#ifndef INCLUDE_MCAL_TIMER_TIMER_PRV_H_
#define INCLUDE_MCAL_TIMER_TIMER_PRV_H_

#define TCCR1A *((volatile u8*) 0x4F)
#define TCCR1B *((volatile u8*) 0x4E)
#define TCNT1 *((volatile u16*) 0x4C)
#define OCR1A *((volatile u16*) 0x4A)
#define OCR1B *((volatile u16*) 0x48)
#define ICR1 *((volatile u16*) 0x46)
#define TIMSK *((volatile u8*) 0x59)
#define TIFR *((volatile u8*) 0x58)

/*FOR TIMER 0*/
#define TCCR0 *((volatile u8*) 0x53)
#define TCNT0 *((volatile u8*)0x52)
#define OCR0 *((volatile u8*)0x5C)

#endif /* INCLUDE_MCAL_TIMER_TIMER_PRV_H_ */
