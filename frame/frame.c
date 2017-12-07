#include "frame.h"
#include <stdio.h>
#include <string.h>

void initFrame(frame_t * frame) {
  frame->header.addr = 0x00;
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