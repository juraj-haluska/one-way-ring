#ifndef FRAME_H_
#define FRAME_H_

#include <inttypes.h>

typedef struct {
  uint8_t hops;
  uint8_t addr;
  uint8_t cmd;
  uint8_t dataLength;
} header_t;

typedef struct {
  header_t header;
  uint8_t * data;
} frame_t;

void initFrame(frame_t * frame);

#endif /* FRAME_H_ */