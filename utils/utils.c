#include "utils.h"
#include "../layers.h"

int containsAddress(l1_t * l1) {
  return l1->addr != 0x00;
}

int checkAddress(uint8_t myAddr, uint8_t addr) {
  return myAddr == addr;
}