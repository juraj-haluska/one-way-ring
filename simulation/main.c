#include <stdio.h>
#include "../parser/parser.h"
#include "../layers.h"
#include <string.h>

char test [] = "0:print:helloworld";
char test1 [] = "helloworld";
void urx(char * data, int dataLength);

int main() {
  urx(test1, strlen(test1));
  return 0;
}

void urx(char * data, int dataLength) {
  l1_t l1;
  
  int parserResult = parseText(data, dataLength, &l1);
  // parsing successful
  if (parserResult == 0) {
    printf("parser result:\r\n");
    printf("\taddr:%d\r\n", l1.addr);
    printf("\tlength:%d\r\n", l1.dataLength);
    printf("\tfirst:%c\r\n", *l1.dataPtr);
    printf("\thops:%d\r\n", l1.hops);
  }
}