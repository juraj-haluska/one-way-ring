#ifndef EXECUTER_H_
#define EXECUTER_H_

#include "../layers.h"

// commands
#define CMD_DEBUG "debug"
#define CMD_LED1 "led1"

// responses
#define RESP_CODE "RESPONSE"
#define RESP_OK "everything is just fine"
#define RESP_UNKNOWN "unknown command"
#define RESP_LED1 "led1 command executed"


int execute(l2_t * l2, uint8_t * buffer, int bufferSize);

static int min(int a, int b);
static int append(uint8_t ** actual, const uint8_t * last, char * text);

#endif /* EXECUTER_H_ */
