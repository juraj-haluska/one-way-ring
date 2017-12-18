#include "main.h"
#include "ch.h"
#include "hal.h"
#include <string.h>
#include "frame/frame.h"
#include "rt/rt.h"
#include "parser/parser.h"
#include "executer/executer.h"
#include "commands.h"
#include "address.h"

// threads
static THD_WORKING_AREA(waThread1, 128);
static THD_WORKING_AREA(waThread2, 128);

static THD_FUNCTION(user, arg) {

  chRegSetThreadName("user");

  // buffer for this thread
  char buffer[BUFFSIZE];
  int iterator;

  while (true) {
    memset(buffer, 0, BUFFSIZE);
    iterator = 0;

    char ch;
    while(('\r' != (ch = sdGet(&SD1))) && iterator < (BUFFSIZE - 1)) {
      sdPut(&SD1, ch);
      buffer[iterator++] = ch;
    }
    buffer[iterator] = '\0';

    newLine(&SD1);
    urx(buffer, iterator);
  }
}

static THD_FUNCTION(board, arg) {

  chRegSetThreadName("board");

  // buffer for this thread
  char buffer[BUFFSIZE];
  int iterator;

  while (true) {
    memset(buffer, 0, BUFFSIZE);
    iterator = 0;

    char ch;
    while(('\r' != (ch = sdGet(&SD2))) && iterator < (BUFFSIZE - 1)) {
      buffer[iterator++] = ch;
    }
    buffer[iterator] = '\0';
    brx(buffer, iterator);
  }
}

int main(void) {

  //* PA2  - Alternate output  (USART2 TX).
  //* PA3  - Normal input      (USART2 RX).

  halInit();
  chSysInit();
  sdInit();
  rtInit();

  // Aktivacia serioveho portu 1. PA9(TX), PA10(RX)
  // prednastavena konfiguracia: 38400 b/s, 8, N, 1
  sdStart(&SD1, NULL);
  sdStart(&SD2, NULL);

  // start threads
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, user, NULL);
  chThdCreateStatic(waThread2, sizeof(waThread2), NORMALPRIO, board, NULL);
}


void newLine(SerialDriver * driver) {
  sdWrite(driver, NEW_LINE, strlen(NEW_LINE));
}

// receive events
void urx(char * buffer, int buffLength) {
  frame_t frame;

  parseText((uint8_t *) buffer, (uint8_t) buffLength, &frame);

  if (frame.header.addr == DEF_ADDR) {
    frame.header.addr = myAddr;
  }

  if (frame.header.addr == myAddr) {
    if (frame.header.cmd == CMDC_TRACE) {
      btx(frame);
    } else {
      // separate buffer is used because received data might be used
      // in execute function
      uint8_t responseBuffer[50];
      memset(responseBuffer, '\0', 50);
      execute(responseBuffer, 50 - 1, &frame);
      utx(frame);
    }
  } else if (rtAdd(frame.header.addr) == 0) {
    btx(frame);
  }
}

void brx(char * buffer, int buffLength) {
  frame_t frame;

  unbundle(buffer, buffLength, &frame);

  if (frame.header.addr == DEF_ADDR) {
    frame.header.addr = myAddr;
  }

  if (frame.header.addr == myAddr) {
    if (frame.header.cmd == TRACE) {
      char buff[10];
      char * ptr = itoa(frame.header.hops, buff, 10);
      sdWrite(&SD1, TRACE_RES, strlen(TRACE_RES));
      sdWrite(&SD1, ptr, strlen(ptr));
      newLine(&SD1);
      return;
    }
    uint8_t responseBuffer[50];
    memset(responseBuffer, '\0', 50);
    execute(responseBuffer, 50 - 1, &frame);
    btx(frame);
  } else if (rtCheckout(frame.header.addr) == 0) {
    utx(frame);
  } else {
    btx(frame);
  }
}

void utx(frame_t frame) {

  // device not found
  if (frame.header.cmd != CMDC_RESPONSE) {
    sdWrite(&SD1, NOT_FOUND, strlen(NOT_FOUND));
    newLine(&SD1);
    return;
  }

  // sprintf is not working well
  char str[10];
  str[0] = '*';
  itoa(frame.header.addr, str + 1, 10);
  int tmpLength = strlen(str);
  str[tmpLength] = ':';
  str[tmpLength + 1] = '\0';
  sdWrite(&SD1, str, strlen(str));

  // print data
  if (frame.header.dataLength != 0) {
    for (int i = 0; i < frame.header.dataLength; i++) {
      sdPut(&SD1, frame.data[i]);
    }
  }

  newLine(&SD1);
}

void btx(frame_t frame) {
  frame.header.hops++;
  for (int i = 0; i < sizeof(header_t); i++) {
    sdPut(&SD2, *((uint8_t *)(&frame) + i));
  }
  for (int i = 0; i < frame.header.dataLength; i++) {
    sdPut(&SD2, frame.data[i]);
  }
  sdPut(&SD2,'\r');
}
