#ifndef MAIN_H_
#define MAIN_H_

// #define ADDR_SIZE  8

typedef struct {
  void (*handler) (char * buffer, int buffLength);
  FILE * source;
} thData_t;

void urx(char * buffer, int buffLength);
void utx(frame_t frame);
void btx(frame_t frame);
void brx(char * buffer, int buffLength);

// thread
void * reader(void * params);

#endif /* MAIN_H_ */
