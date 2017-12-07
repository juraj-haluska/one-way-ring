#include "frame.h"
#include <stdio.h>

void initFrame(frame_t * frame) {
  frame->header.addr = 0x00;
  frame->header.cmd = 0x00;
  frame->header.dataLength = 0;
  frame->header.hops = 0;
  frame->data = NULL;
}