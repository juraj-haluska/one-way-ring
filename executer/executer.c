#include "executer.h"
#include <string.h>
#include <stdio.h>
#include "../frame/frame.h"

void execute(uint8_t * responseData, int responseCapacity, frame_t * frame) {
  memset(responseData, '\0', responseCapacity);

  // address of the last byte in the buffer
  const uint8_t * bufferEnd = responseData + responseCapacity - 1;

  uint8_t cmd = frame->header.cmd;
  frame->header.cmd = CMDC_RESPONSE;
  frame->header.dataLength = 0;
  frame->data = responseData;

  if (cmd == CMDC_UNDEFINED) {
    frame->header.dataLength += append(&responseData, bufferEnd, RESP_UNDEFINED);
  } else if (cmd == CMDC_DEBUG) {
    frame->header.dataLength += append(&responseData, bufferEnd, RESP_OK);
  } 
}

static int min(int a, int b) {
  if (a > b) return b;
  return a;
}

static int append(uint8_t ** actual, const uint8_t * last, char * text) {
  int space = last - (*actual);
  int needed = strlen(text);
  if (needed <= space) {
    strcpy(*actual, text);
    (*actual) += needed;
    return needed;
  }
  return 0;
}