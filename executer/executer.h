#ifndef EXECUTER_H_
#define EXECUTER_H_

#include <inttypes.h>
#include "../frame/frame.h"

// commands
#define CMDC_RESPONSE 0xFF
#define CMDC_DEBUG 0x01
#define CMDC_UNDEFINED 0x00

// responses
#define RESP_OK "everything is just fine"
#define RESP_UNDEFINED "undefined command"

void execute(uint8_t * responseData, int responseCapacity, frame_t * frame);

static int min(int a, int b);
static int append(uint8_t ** actual, const uint8_t * last, char * text);

#endif /* EXECUTER_H_ */
