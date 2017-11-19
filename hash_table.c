#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "index_interface.h"
#include "ngx_crc32.h"

#define INITIAL (1 << 20)
#define LAST_SLOT { 0, 0 }

size_t memory_consumed;

enum {
  FOUND = 1,
  NOT_FOUND = 0
};

typedef struct {
  uint32_t hash;
  int strlen;
} slot_t;

slot_t * index;
size_t size;
size_t position;
slot_t last_slot = LAST_SLOT;
#define cast(x) (uint64_t *) x
#define is_not_last(x) *cast(x) != *cast(&last_slot)


static void index_append(slot_t * slot)
{
  if (index == NULL) {
    index = malloc(INITIAL);
    memory_consumed += INITIAL;
    
    size = INITIAL / sizeof(slot_t);
    position = 0;
  }
  if (position == size - 1) {
    size *= 2;
    index = realloc(index, size); // here is bug !
    memory_consumed += size;
  }
  if (index == NULL) {
    perror("hash table");
    printf("Memory failure, %u", memory_consumed);
    exit(5);
  }
  
  index[position] = *slot;
  ++position;
  index[position] = last_slot;
}

void index_insert(const char * string, int len)
{
  slot_t entry;
  entry.hash = ngx_crc32_long( (u_char *) string, len);
  entry.strlen = len;
  
  index_append(&entry);
}

char index_search(const char * string, int len)
{
  slot_t * slot = index;
  uint32_t hash;
  
  hash = ngx_crc32_long( (u_char *) string, len);
  
  while (is_not_last(slot)) {
    
    if (hash != slot->hash) {
      slot++;
      continue;
    }
    
    if (len != slot->strlen) {
      puts("Hash collision detected;");
      printf("hash: %08x len: %d\n",
        slot->hash, slot->strlen);
      printf("collision: %d %s", len, string);
      exit(6);
    }
    
    return FOUND;
  }
  
  return NOT_FOUND;
}

