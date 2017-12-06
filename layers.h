#ifndef LAYERS_H_
#define LAYERS_H_

#include <inttypes.h>

typedef struct {
  uint8_t hops;
  uint8_t addr;
  uint8_t dataLength;
  uint8_t * dataPtr;
} l1_t;

typedef struct {
  uint8_t cmdLength;
  uint8_t * cmdPtr;
  uint8_t dataLength;
  uint8_t * dataPtr;
} l2_t;

#endif /* LAYERS_H_ */
