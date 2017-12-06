#include <string.h>
#include "../layers.h"
#include <stdio.h>  // because of NULL
#include "parser.h"
#include <stdlib.h>
#include "../simulation/main.h"

int parseText(char * data, int dataLength, l1_t * l1) {
  int count = 0;
  int positions [SEGMENTS - 1];

  for (int i = 0; (i < dataLength) && (count < (SEGMENTS - 1)); i++) {
    if (data[i] == ':') {
      positions[count] = i;
      count++;
    }
  }

  if (count == 0) {
    return -1;
  }

  if (count == 1) {
    l1->addr = 0x00;
    l1->dataPtr = data;
    l1->dataLength = dataLength;
    l1->hops = 0;
    return 0;
  }

  if (count == 2) {
    data[positions[0]] = '\0';
    
    int addr = 0;
    for (int i = 0; i < positions[0]; i++) {
      printf("expo: %d", positions[0] - 1 - i);
      printf("value: %d", raise(10, positions[0] - 1 - i));
      printf("mult: %d", (data[i] - '0'));
      addr += (raise(10, positions[0] - 1 - i)) * (data[i] - '0');
    }

    int offset = raise(2, ADDR_SIZE);
    if (addr >= offset) {
      return -1;
    }

    l1->addr = addr;
    l1->dataPtr = &data[positions[0] + 1];
    l1->dataLength = dataLength - (l1->dataPtr - data);
    l1->hops = 0;
    return 0;
  }
}

static int raise(int raiser, int exponent) {
  int value = 1;;
  for (int i = 0; i < exponent; i++) {
    value *= raiser; 
  }
  return value;
}