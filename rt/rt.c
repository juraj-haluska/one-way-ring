#include "rt.h"

uint8_t rt_table[RT_SIZE];

void rtInit() {
  for (int i = 0; i < RT_SIZE; i++) {
    dropAddress(i);
  }
}

int rtAdd(uint8_t addr) {
  int emptySlot = getEmptySlot();
  if (emptySlot != -1) {
    insertAddress(addr, emptySlot);
    return 1;
  }
  return -1;
}

int rtCheckout(uint8_t addr) {
  int slot = findAddress(addr);
  if (slot != -1) {
    dropAddress(slot);
    return 1;
  }
  return -1;
}


// private functions
static int getEmptySlot() {
  for(int i = 0; i < RT_SIZE; i++) {
    if (rt_table[i] == 0x00) {
      return i;
    }
  }
  return -1;
}

static void insertAddress(uint8_t addr, int slot) {
  rt_table[slot] = addr;
}

static void dropAddress(int slot) {
  rt_table[slot] = 0x00;
}

static int findAddress(uint8_t addr) {
  for (int i = 0; i < RT_SIZE; i++) {
    if (addr == rt_table[i]) {
      return i;
    }
  }
  return -1;
}
