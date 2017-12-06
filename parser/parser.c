#include <string.h>
#include "../layers.h"
#include <stdio.h>  // because of NULL
#include "parser.h"
#include <stdlib.h>
#include <inttypes.h>

int parseText(uint8_t * data, uint8_t dataLength, l1_t * l1) {
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
    int addr = 0;
    for (int i = 0; i < positions[0]; i++) {
      // chceck invalid characters, only 0 - 9 are valid
      if (data[i] < '0' || data[i] > '9') {
        return -1;
      }
      addr += (raise(10, positions[0] - 1 - i)) * (data[i] - '0');
    }

    int offset = raise(2, sizeof(uint8_t) * 8);
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

void parseL1(l1_t * l1, l2_t * l2) {
  // find ':' character
  int i;
  for (i = 0; i < l1->dataLength; i++) {
    if ((l1->dataPtr)[i] == ':') break;
  }
  
  l2->cmdLength = i;
  if (i == 0) {
    l2->cmdPtr = NULL;
  } else {
    l2->cmdPtr = l1->dataPtr;
  }
  l2->dataLength = l1->dataLength - l2->cmdLength - 1;
  if (l2->dataLength <= 0) {
    l2->dataPtr = NULL;
  } else {
    l2->dataPtr = &(l1->dataPtr)[i + 1];
  }
}

static int raise(int raiser, int exponent) {
  int value = 1;;
  for (int i = 0; i < exponent; i++) {
    value *= raiser; 
  }
  return value;
}