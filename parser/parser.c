#include <string.h>
#include "../frame/frame.h"
#include <stdio.h>  // because of NULL
#include "parser.h"
#include <inttypes.h>
#include "../commands.h"
#include "../executer/executer.h"

void parseText(uint8_t * data, uint8_t dataLength, frame_t * frame) {
  int count = 0;
  int positions[SEGMENTS - 1];

  initFrame(frame);

  for (int i = 0; (i < dataLength) && (count < (SEGMENTS - 1)); i++) {
    if (data[i] == ':') {
      data[i] = '\0';
      positions[count] = i;
      count++;
    }
  }

  if (count == 0) {
    // command
    frame->header.cmd = parseCommand(data, dataLength);
  }

  if (count == 1) {
    // command:data
    if (positions[0] > 0) {
      frame->header.cmd = parseCommand(data, positions[0]);
    }

    if ((positions[0] + 1) < dataLength) {
      frame->header.dataLength = dataLength - (positions[0] + 1);
      frame->data = &data[positions[0] + 1];
    }
  }

  if (count == 2) {
    // address:command:data
    int addr = 0;
    int invalid = 0;
    for (int i = 0; i < positions[0]; i++) {
      // chceck invalid characters, only 0 - 9 are valid
      if (data[i] < '0' || data[i] > '9') {
        invalid--;
      }
      addr += (raise(10, positions[0] - 1 - i)) * (data[i] - '0');
    }

    int offset = raise(2, sizeof(uint8_t) * 8);
    if (addr < offset && invalid >= 0) {
      frame->header.addr = addr;
    }

    if ((positions[1] - positions[0]) > 1) {
      frame->header.cmd = parseCommand(data + positions[0] + 1, positions[1] - positions[0] - 1);
    }

    if ((positions[1] + 1) < dataLength) {
      frame->header.dataLength = dataLength - (positions[1] + 1);
      frame->data = &data[positions[1] + 1];
    }
  }
}

static int raise(int raiser, int exponent) {
  int value = 1;;
  for (int i = 0; i < exponent; i++) {
    value *= raiser; 
  }
  return value;
}

static uint8_t parseCommand(uint8_t * command, int commandLength) {
  if (strncmp(command, DEBUG, min(commandLength, strlen(DEBUG))) == 0) {
    return CMDC_DEBUG;
  } else if (strncmp(command, LED1, min(commandLength, strlen(LED1))) == 0) {
    return CMDC_LED1;
  } else if (strncmp(command, LED2, min(commandLength, strlen(LED2))) == 0) {
    return CMDC_LED2;
  } else if (strncmp(command, PRINT, min(commandLength, strlen(PRINT))) == 0) {
    return CMDC_PRINT;
  } else if (strncmp(command, TRACE, min(commandLength, strlen(TRACE))) == 0) {
    return CMDC_TRACE;
  } else {
    return CMDC_UNDEFINED;
  }
}

static int min(int a, int b) {
  if (a > b) return b;
  return a;
}
