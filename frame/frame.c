#include "frame.h"
#include <stdio.h>
#include <string.h>

void initFrame(frame_t * frame) {
  frame->header.addr = DEF_ADDR;
  frame->header.cmd = 0x00;
  frame->header.dataLength = 0;
  frame->header.hops = 0;
  frame->data = NULL;
}

int bundle(uint8_t * buffer, int buffSize, frame_t * frame) {
  int headerOffset = sizeof(header_t);

  int i;
  for (i = 0; i < headerOffset; i++) {
    buffer[i] = (uint8_t) *(((uint8_t *) frame) + i);
  }

  for (int a = 0; i < buffSize && a < frame->header.dataLength; i++, a++) {
    buffer[i] = frame->data[a];
  }

  return i;
}

int unbundle(uint8_t * buffer, int dataLength, frame_t * frame) {
  if (dataLength < sizeof(header_t)) {
    return -1;
  }

  int i;
  for (i = 0; i < sizeof(header_t); i++) {
    *(((uint8_t *) frame) + i) = buffer[i];
  }

  if (frame->header.dataLength != (dataLength - sizeof(header_t))) {
    return -1;
  }

  frame->data = &buffer[i];
  return 0;
} 
