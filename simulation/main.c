#include <stdio.h>
#include "../parser/parser.h"
#include "../layers.h"
#include <string.h>

char test [] = "41::";
char test1 [] = "helloworld";
void urx(char * data, int dataLength);

int main() {
  urx(test, strlen(test));
  return 0;
}

void urx(char * data, int dataLength) {
  l1_t l1;
  
  int parserResult = parseText((uint8_t *) data, (uint8_t) dataLength, &l1);
  // parsing successful
  if (parserResult == 0) {
    printf("parser result:\r\n");
    printf("\taddr:%d\r\n", l1.addr);
    printf("\tlength:%d\r\n", l1.dataLength);
    printf("\tfirst:%c\r\n", *l1.dataPtr);
    printf("\thops:%d\r\n", l1.hops);
    l2_t l2;
    parseL1(&l1, &l2);
    printf("l1 parser result:\r\n");
    printf("\tcmdlength:%d\r\n", l2.cmdLength);
    printf("\tcmd:%c\r\n", (l2.cmdPtr == NULL)?'N':*l2.cmdPtr);
    printf("\tdatalength:%d\r\n", l2.dataLength);
    printf("\tdata:%c\r\n", (l2.dataPtr == NULL)?'N':*l2.dataPtr);

  }
}