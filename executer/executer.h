#ifndef EXECUTER_H_
#define EXECUTER_H_

#include "../layers.h"

#define CMD_DEBUG "debug"

#define RESPONSE_SIZE 50

#define STATUS_CODE 0x00
#define STATUS_OK   0x00

void execute(l2_t * l2, l1_t * l1, uint8_t * response);

static int min(int a, int b);

#endif /* EXECUTER_H_ */
