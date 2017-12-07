#include <stdio.h>
#include "../parser/parser.h"
#include "../layers.h"
#include <string.h>
#include "../utils/utils.h"
#include "../executer/executer.h"
#include "main.h"

#define MYADDR 41

char test [] = "41:debug:ghgh";
char test1 [] = "helloworld";

int main() {
  urx(test, strlen(test));
  return 0;
}

void urx(char * buffer, int buffLength) {
  l1_t l1;
  
  int parserResult = parseText((uint8_t *) buffer, (uint8_t) buffLength, &l1);
  // parsing successful
  if (parserResult == 0) {
    l2_t l2;
    parseL1(&l1, &l2);

    if (!checkAddress(MYADDR, l1.addr)) {
        // rt_add ...
        printf("unknown address\r\n");

      return;
    }
    uint8_t buffer[100];
    memset(buffer, '\0', 100);
    execute(&l2, buffer, 100 - 1);
    printf("response: %s\r\n", buffer);
    // humanize ...
  }
}

void utx(char * buffer, int buffLength) {

}