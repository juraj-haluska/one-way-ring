#ifndef PARSER_H_
#define PARSER_H_

#include <inttypes.h>
#include "../frame/frame.h"

#define SEGMENTS 3

// public functions
void parseText(uint8_t * data, uint8_t dataLength, frame_t * frame);

// private functions
static int raise(int raiser, int exponent);
static uint8_t parseCommand(uint8_t * command, int commandLength);
static int min(int a, int b);

#endif /* PARSER_H_ */
