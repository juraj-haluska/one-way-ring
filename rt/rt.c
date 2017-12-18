#include "rt.h"
#include "../address.h"

uint8_t rt_table[RT_SIZE];

void rtInit() {
  for (int i = 0; i < RT_SIZE; i++) {
    rt_table[i] = DEF_ADDR;
  }
}

int rtAdd(uint8_t addr) {
  for (int i = 0; i < RT_SIZE; i++) {
    if (rt_table[i] == DEF_ADDR) {
      rt_table[i] = addr;
      return 0;
    }
  }
  return -1;
}

int rtCheckout(uint8_t addr) {
  for (int i = 0; i < RT_SIZE; i++) {
    if (rt_table[i] == addr) {
      rt_table[i] = DEF_ADDR;
      return 0;
    }
  }
  return -1;
}
