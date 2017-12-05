#include <string.h>
#include "../layers.h"

int parse(char * data, int dataLength, l1_t * l1) {
  char * segments [] = { NULL, NULL, NULL };
  int lengths [] = { 0, 0, 0 };
  int iter = 0;

  for (int i = 0; i < dataLength; i++) {
    if (data[i] == ':') {
      segments[segment] = &data[i];
    }
  }
}