#include "executer.h"
#include <string.h>
#include <stdio.h>

#define compareCmd(l2, cmd) (strncmp(l2->cmdPtr, cmd, min(l2->cmdLength, strlen(cmd))) == 0)

int execute(l2_t * l2, uint8_t * buffer, int bufferSize) {
  // address of the last byte in the buffer
  const uint8_t * bufferEnd = buffer + bufferSize - 1;
  int written = 0;
  // add response message to buffer
  written += append(&buffer, bufferEnd, RESP_CODE);

  if (l2->cmdLength == 0) {
    written += append(&buffer, bufferEnd, RESP_UNKNOWN);
    return written;
  } else if (compareCmd(l2, CMD_DEBUG)) {
    written += append(&buffer, bufferEnd, RESP_OK);
    return written;
  } else if (compareCmd(l2, CMD_LED1)) {
    written += append(&buffer, bufferEnd, RESP_LED1);
    return written;
  }

  written += append(&buffer, bufferEnd, RESP_UNKNOWN);
  return written;
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