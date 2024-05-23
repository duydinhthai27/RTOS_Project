/*
 * software_timer.h
 *
 *  Created on: May 23, 2024
 *      Author: Duy Dinh
 */


#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

void setTimer(int index, int value);
int isTimerExpired(int index);

void timerRun();


#endif /* SOFTWARE_TIMER_H_ */


