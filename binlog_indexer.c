/* main
 *   open file
 *   read string from file
 *   create index verbose
 *     compute crc32 of string
 *     print crc32, string
 *   exit
 */

#include <stdio.h>
#include <stdint.h>

#include "ngx_crc32.h"
#define hash_function ngx_crc32_long

#define APPEND_ONLY (O_WRONLY | O_APPEND | O_CREAT)
#define MAGIC * (unsigned *)

unsigned EXIT;
char * string;
size_t length;

void create_index_verbose(const char * filename)
{
  FILE * stream;
  ssize_t len;
  uint32_t hash;
  
  stream = fopen(filename, "r");
  if (stream == NULL) goto error;
  
  while (1) {
    len = getline(&string, &length, stream);
    if (len == EOF) break;
    
    hash = hash_function( (u_char *) string, len);
    if (len > 65)
         printf("%08x : %.65s\n", hash, string);
    else printf("%08x : %s", hash, string);
  }
  
  fclose(stream);
  return;
  
error:
  perror("fopen");
}

int main(int argc, char *argv[])
{
  EXIT = MAGIC "exit";
  
  if (argc < 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    return 1;
  }
  
  create_index_verbose(argv[1]);
  
  /*
  while (1) {
    len = getline(&string, &length, stdin);
    if (len == EOF) break;
    
    if (MAGIC string == EXIT) break;
    
    err = write(fd, string, len);
    if (err != len) goto error;
  }
  */
  
  return 0;
}

