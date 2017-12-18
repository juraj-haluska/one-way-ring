/*
 * main.h
 *
 *  Created on: 22.11.2017
 *      Author: Študent
 */
#include "hal.h"
#include "frame/frame.h"

#ifndef MAIN_H_
#define MAIN_H_

#define BUFFSIZE 50

// prototypes
void newLine(SerialDriver * driver);
void urx(char * buffer, int buffLength);
void utx(frame_t frame);
void btx(frame_t frame);
void brx(char * buffer, int buffLength);

#endif /* MAIN_H_ */
