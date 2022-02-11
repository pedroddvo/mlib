#ifndef _MLIB_BUFFER_H
#define _MLIB_BUFFER_H

#include <stdint.h>

#ifndef BUFFER_DEFAULT_CAPACITY
#define BUFFER_DEFAULT_CAPACITY 64
#endif

struct mlib_buffer {
  char* data;
  
  size_t length;
  size_t capacity;
};

// Generates a buffer with default capacity BUFFER_DEFAULT_CAPACITY
struct mlib_buffer*
mlib_buffer_new();

// Generates a buffer with specified capacity
struct mlib_buffer*
mlib_buffer_with_capacity(size_t capacity);

// Resizes the buffer
// Returns -1 on failure
int
mlib_buffer_resize(struct mlib_buffer* buf);

// Pushes a character into the string
// Returns -1 on failure
int
mlib_buffer_push(struct mlib_buffer* buf, char c);

// Appends a string with strlen
// Returns -1 on failure
int
mlib_buffer_append(struct mlib_buffer* buf, char* str_terminated);

// Appends a string with length
// Returns -1 on failure
int
mlib_buffer_append_n(struct mlib_buffer* buf, char* str, size_t len);

// Prepends a string with strlen
// Returns -1 on failure
int
mlib_buffer_prepend(struct mlib_buffer* buf, char* str_terminated);

// Prepends a string with length
// Returns -1 on failure
int
mlib_buffer_prepend_n(struct mlib_buffer* buf, char* str, size_t len);

// Slices a buffer into two from a range *inclusively*
// Returns NULL on failure
struct mlib_buffer*
mlib_buffer_slice(struct mlib_buffer* buf, size_t start, size_t end);

// Free the buffer
void
mlib_buffer_free(struct mlib_buffer* buf);

// Creates a malloced string from the buffer
char*
mlib_buffer_string(struct mlib_buffer* buf);

#endif