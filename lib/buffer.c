#include "buffer.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct mlib_buffer*
mlib_buffer_new() {
  return mlib_buffer_with_capacity(4);
}


struct mlib_buffer*
mlib_buffer_with_capacity(size_t capacity) {
  struct mlib_buffer* self = malloc(sizeof(struct mlib_buffer));
  self->capacity = capacity;
  self->length = 0;
  
  // sizeof(char) = 1
  self->data = malloc(self->capacity);
  return self;
}

int
mlib_buffer_resize(struct mlib_buffer* buf) {
  buf->capacity *= 2;
  buf->data = realloc(buf->data, buf->capacity);
  if (!buf->data) return -1;
  
  return 0;
}

int
mlib_buffer_push(struct mlib_buffer* buf, char c) {
  if (buf->length > buf->capacity)
    if (-1 == mlib_buffer_resize(buf)) return -1;
  buf->data[buf->length++] = c;
  return 0;
}

static int resize_it(struct mlib_buffer* buf) {
  while (buf->length > buf->capacity)
    if (-1 == mlib_buffer_resize(buf)) return -1;

  return 0;
}

int
mlib_buffer_append(struct mlib_buffer* buf, char* str_terminated) {
  return mlib_buffer_append_n(buf, str_terminated, strlen(str_terminated));
}

int
mlib_buffer_append_n(struct mlib_buffer* buf, char* str, size_t len) {
  // create enough space for both strings
  buf->length += len;
  if (-1 == resize_it(buf)) return -1;
  
  for (size_t i = 0; i < len; i++)
    buf->data[buf->length-len+i] = str[i];
  
  
  return 0;
}

int
mlib_buffer_prepend(struct mlib_buffer* buf, char* str_terminated) {
  return mlib_buffer_prepend_n(buf, str_terminated, strlen(str_terminated));
}

int
mlib_buffer_prepend_n(struct mlib_buffer* buf, char* str, size_t len) {
  // create enough space for both strings
  buf->length += len;
  if (-1 == resize_it(buf)) return -1;
  
  memcpy(buf->data+len, buf->data, len);
  
  for (size_t i = 0; i < len; i++)
    buf->data[i] = str[i];
  
  return 0;
}

struct mlib_buffer*
mlib_buffer_slice(struct mlib_buffer* buf, size_t start, size_t end) {
  struct mlib_buffer* new_buf = malloc(sizeof(struct mlib_buffer));
  new_buf->length   = end-start;
  new_buf->capacity = 4;
  
  if (-1 == resize_it(new_buf)) return NULL;
  
  memcpy(new_buf->data, buf->data+start, end-start);
  return new_buf;
}

char*
mlib_buffer_string(struct mlib_buffer* buf) {
  char* result = malloc(buf->length);
  memcpy(result, buf->data, buf->length);
  result[buf->length] = '\0';
  return result;
}


void
mlib_buffer_free(struct mlib_buffer* buf) {
  free(buf->data);
  free(buf);
}