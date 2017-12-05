typedef struct {
  char hops;
  char addr;
  char dataLength;
  char * dataPtr;
} l1_t;

typedef struct {
  char cmdLength;
  char * cmdPtr;
  char dataLength;
  char * dataPtr;
} l2_t;