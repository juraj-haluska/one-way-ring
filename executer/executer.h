#ifndef EXECUTER_H_
#define EXECUTER_H_

#include <inttypes.h>
#include "../frame/frame.h"

void execute(uint8_t * responseData, int responseCapacity, frame_t * frame);
int compare(frame_t * frame, char * str);

#endif /* EXECUTER_H_ */
