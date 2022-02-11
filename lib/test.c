#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "buffer.h"

void mlib_buffer_tests() {
  struct mlib_buffer* buf = mlib_buffer_with_capacity(4);
  
  assert(!mlib_buffer_append(buf, "World"));
  assert(!mlib_buffer_prepend(buf, "Hello "));
  
  struct mlib_buffer* sliced = mlib_buffer_slice(buf, 3, 7);
  assert(sliced);
  
  char* str = mlib_buffer_string(sliced);
  printf("'%s'\n", str);
  free(str);

  mlib_buffer_free(buf);
}

int main() {
  printf("test.c\n");
  
  printf("mlib_buffer_tests\n");
  mlib_buffer_tests();
  
  return 0;
}