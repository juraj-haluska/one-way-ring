#include "executer.h"
#include <string.h>

void execute(l2_t * l2, l1_t * l1, uint8_t * response) {
  response[0]= l1->hops;
  response[1] = l1->addr;
  response[2] = 0;
  if (strncmp(l2->cmdPtr, CMD_DEBUG, min(l2->cmdLength, strlen(CMD_DEBUG))) == 0) {
    response[3] = 0x1;
    response[4] = STATUS_CODE;
    response[5] = STATUS_OK;
    response[2] = 3;
    return;
  }
}

static int min(int a, int b) {
  if (a > b) return b;
  return a;
}