#include <stdio.h>
#include "../parser/parser.h"
#include "../frame/frame.h"
#include <string.h>
#include "../executer/executer.h"
#include "main.h"

#define MYADDR 41

char test [] = "415:debug:sdfsdfsd:fsdfdsfsdfsdf";

int main() {
  urx(test, strlen(test));
  return 0;
}

void urx(char * buffer, int buffLength) {
  frame_t frame;
  
  parseText((uint8_t *) buffer, (uint8_t) buffLength, &frame);
  printf("parsed data:\r\n");
  printf(" hops:\t%d\r\n", frame.header.hops);
  printf(" addr:\t%d\r\n", frame.header.addr);
  printf(" cmd:\t%d\r\n", frame.header.cmd);
  printf(" dataLength:\t%d\r\n", frame.header.dataLength);
  printf(" data:\t%s\r\n", frame.data);

  uint8_t responseBuffer[100];
  execute(responseBuffer, 99, &frame);

  printf("response data:\r\n");
  printf(" hops:\t%d\r\n", frame.header.hops);
  printf(" addr:\t%d\r\n", frame.header.addr);
  printf(" cmd:\t%d\r\n", frame.header.cmd);
  printf(" dataLength:\t%d\r\n", frame.header.dataLength);
  printf(" data:\t%s\r\n", frame.data);
}

void utx(char * buffer, int buffLength) {

}