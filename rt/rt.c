#include "rt.h"

char rt_table[RT_SIZE][ADDR_SIZE];

void rtInit() {
  for (int i = 0; i < RT_SIZE; i++) {
    for (int a = 0; a < ADDR_SIZE; a++) {
      rt_table[i][a] = '\0';
    }
  }
}

int rtAdd(char * addr) {
  int emptySlot = getEmptySlot();
  if (emptySlot != -1) {
    insertAddress(addr, emptySlot);
    return 1;
  }
  return -1;
}

int rtCheckout(char * addr) {
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
    if (rt_table[i][0] == '\0') {
      return i;
    }
  }
  return -1;
}

static void insertAddress(char * addr, int slot) {
  for (int i = 0; i < ADDR_SIZE; i++) {
    rt_table[slot][i] = addr[i];
  }
}

static void dropAddress(int slot) {
  for (int i = 0; i < ADDR_SIZE; i++) {
    rt_table[slot][i] = '\0';
  }
}

static int findAddress(char * addr) {
  for (int i = 0; i < RT_SIZE; i++) {
    int match = 0;
    for (int a = 0; a < ADDR_SIZE; a++) {
      if (rt_table[i][a] == addr[a]) {
        match++;
      }
    }
    if (match == ADDR_SIZE) {
      return i;
    }
  }
  return -1;
}
