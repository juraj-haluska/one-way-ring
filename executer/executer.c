#include "executer.h"
#include "../commands.h"
#include <string.h>
#include <stdio.h>
#include "../frame/frame.h"
#include "hal.h"

extern SerialDriver SD1;

void execute(uint8_t * responseData, int responseCapacity, frame_t * frame) {
  // assuming responseData is full of null-terminating chars

  uint8_t cmd = frame->header.cmd;
  uint8_t responseLength = 0;

  if (cmd == CMDC_UNDEFINED) {
    strcpy(responseData, RESP_UNDEFINED);
  } else if (cmd == CMDC_DEBUG) {
    strcpy(responseData, RESP_OK);
  } else if (cmd == CMDC_LED1) {
    if (compare(frame, D_ON) == 0) {
      // turn led on
      palSetPad(GPIOC, GPIOC_LED3);
      strcpy(responseData, RESP_OK);
    } else if (compare(frame, D_OFF) == 0) {
      // turn led off
      palClearPad(GPIOC, GPIOC_LED3);
      strcpy(responseData, RESP_OK);
    } else {
      strcpy(responseData, RESP_MISSING);
    }
  } else if (cmd == CMDC_LED2) {
    if (compare(frame, D_ON) == 0) {
      // turn led on
      palSetPad(GPIOC, GPIOC_LED4);
      strcpy(responseData, RESP_OK);
    } else if (compare(frame, D_OFF) == 0) {
      // turn led off
      palClearPad(GPIOC, GPIOC_LED4);
      strcpy(responseData, RESP_OK);
    } else {
      strcpy(responseData, RESP_MISSING);
    }
  } else if (cmd == CMDC_PRINT) {
    sdWrite(&SD1, frame->data, frame->header.dataLength);
    sdWrite(&SD1, NEW_LINE, strlen(NEW_LINE));
    strcpy(responseData, RESP_OK);
  }

  frame->header.cmd = CMDC_RESPONSE;
  frame->header.dataLength = strlen(responseData);
  frame->data = responseData;
}

int compare(frame_t * frame, char * str) {
  if (frame->header.dataLength == strlen(str)) {
    if (strcmp(frame->data, str) == 0) {
      return 0;
    }
  }

  return -1;
}
