#ifndef PARSER_H_
#define PARSER_H_

#include "../layers.h"

#define SEGMENTS 3

int parseText(char * data, int dataLength, l1_t * l1);

static int raise(int raiser, int exponent);

#endif /* PARSER_H_ */
