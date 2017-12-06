#ifndef PARSER_H_
#define PARSER_H_

#include "../layers.h"

#define SEGMENTS 3

// public functions
int parseText(uint8_t * data, uint8_t dataLength, l1_t * l1);
void parseL1(l1_t * t1, l2_t * l2);

// private functions
static int raise(int raiser, int exponent);

#endif /* PARSER_H_ */
