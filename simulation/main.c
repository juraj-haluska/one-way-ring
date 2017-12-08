#include <stdio.h>
#include "../parser/parser.h"
#include "../frame/frame.h"
#include <string.h>
#include "../executer/executer.h"
#include "main.h"
#include "../rt/rt.h"
#include <pthread.h>

#define MYADDR 41
#define RECV_BUFF_SIZE 100

char test [] = "41:debug:sdfsdfsd:fsdfdsfsdfsdf";
FILE * debug;
FILE * in;
FILE * out;

int main(int argc, char ** args) {
  // debugging output
  debug = fopen("/dev/pts/0", "a");
  if (debug != NULL) {
    fprintf(debug, "debug success from %d\r\n", MYADDR);
  }

  in = fopen(args[1], "r");
  out = fopen(args[2], "w");
  if (in == NULL || out == NULL) {
    fprintf(debug, "%d: error opening pipes\r\n", MYADDR);
  } else {
    fprintf(debug, "%d: pipes opened!\r\n", MYADDR);
  }

  rtInit();

  pthread_attr_t thAttr;
	pthread_attr_init(&thAttr);

  pthread_t thUserReader;
  pthread_t thBoardReader;

  thData_t thUserReaderData;
    thUserReaderData.handler = &urx;
    thUserReaderData.source = stdin;

  thData_t thBoardReaderData;
  thBoardReaderData.handler = &brx;
  thBoardReaderData.source = in;

  if (pthread_create(&thUserReader, &thAttr,(void *) &reader, &thUserReaderData) != 0) {
    printf(stdout, "%d: error creating userReader thread\r\n", MYADDR);
  }
  if (pthread_create(&thBoardReader, &thAttr,(void *) &reader, &thBoardReaderData) != 0) {
    printf(stdout, "%d: error creating boardReader thread\r\n", MYADDR);
  }

  pthread_join(thUserReader, NULL);
  pthread_join(thBoardReader, NULL);

  return 0;
}

void urx(char * buffer, int buffLength) {
  frame_t frame;
  
  parseText((uint8_t *) buffer, (uint8_t) buffLength, &frame);

  if (frame.header.addr == MYADDR) {
      if (debug != NULL) {
        fprintf(debug, "%d:excuting straight\r\n", MYADDR);
      }
      // separate buffer is used because received data might be used
      // in execute function
      uint8_t responseBuffer[100];
      execute(responseBuffer, 99, &frame);
      utx(frame);
  } else if (rtAdd(frame.header.addr)) {
    if (debug != NULL) {
      fprintf(debug, "%d:routing\r\n", MYADDR);
    }
    btx(frame);
  }
}

void utx(frame_t frame) {
  printf("%d:%s\r\n", frame.header.addr, frame.data);
}

void btx(frame_t frame) {
  frame.header.hops++;
  for (int i = 0; i < sizeof(header_t); i++) {
    putc(*((uint8_t *)(&frame) + i), out);
  }
  for (int i = 0; i < frame.header.dataLength; i++) {
    putc(frame.data[i], out);
  }
  putc(';', out);
}

void brx(char * buffer, int buffLength) {
  frame_t frame;

  unbundle(buffer, buffLength, &frame);

  if (frame.header.addr == MYADDR) {
    if (debug != NULL) {
      fprintf(debug, "%d:excuting\r\n", MYADDR);
    }
    uint8_t responseBuffer[100];
    execute(responseBuffer, 99, &frame);
    btx(frame);
  } else if (rtCheckout(frame.header.addr)) {
    utx(frame);
  } else {
    if (debug != NULL) {
      fprintf(debug, "%d:passing\r\n", MYADDR);
    }
    btx(frame);
  }
}

/* threads */
void * reader(void * params) {
  printf("kurva\r\n");
  fprintf(debug, "started\r\n");
  thData_t * thData = (thData_t *) params;

  char recvBuffer[RECV_BUFF_SIZE];

  fprintf(debug, "started\r\n");

  while (1) {

    memset(recvBuffer, '\0', RECV_BUFF_SIZE);
    char ch = '\0';
    int i = 0;
    
    while (';' != (ch = getc(thData->source))) {
      fprintf(debug, "char: %c\r\n", ch);
      recvBuffer[i] = ch;
      i++;
    }

    fprintf(debug, "complete\r\n");
    thData->handler(recvBuffer, i);
  }

  return NULL;
}