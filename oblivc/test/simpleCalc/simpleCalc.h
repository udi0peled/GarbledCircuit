#define N 1

typedef struct protocolIO { 
  unsigned int result[N];
  unsigned int value[N];
} protocolIO;

void calc_and(void* args);
void calc_add_char(void* args);
void calc_add_mod_char(void* args);
void calc_add_int(void* args);