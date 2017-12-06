#include <stdio.h>
#include "../parser/parser.h"
#include "../layers.h"
#include <string.h>

char test [] = "256:print:helloworld";
char test1 [] = "helloworld";
void urx(char * data, int dataLength);

int main() {
  urx(test, strlen(test));
  return 0;
}

void urx(char * data, int dataLength) {
  l1_t l1;
  printf("uint8_t size: %d \r\n", sizeof(uint8_t));
  
  int parserResult = parseText((uint8_t *) data, (uint8_t) dataLength, &l1);
  // parsing successful
  if (parserResult == 0) {
    printf("parser result:\r\n");
    printf("\taddr:%d\r\n", l1.addr);
    printf("\tlength:%d\r\n", l1.dataLength);
    printf("\tfirst:%c\r\n", *l1.dataPtr);
    printf("\thops:%d\r\n", l1.hops);
  }
}