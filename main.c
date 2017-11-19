/* main
 *   open file
 *   create index
 *   read string from stdin
 *   if string in index
 *     print yes
 *   else print no
 *   if string is exit
 *     exit
 */

#include <stdio.h>
#include "index_interface.h"

#define MAGIC * (unsigned *)

unsigned EXIT;
char * string;
size_t length;


int main(int argc, char *argv[])
{
  FILE * stream;
  ssize_t len, err;
  char inside_index;
  
  
  if (argc < 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    return 1;
  }
  
  stream = fopen(argv[1], "r");
  if (stream == NULL) {
    perror("fopen");
    return 2;
  }
  
  while (1) {
    len = getline(&string, &length, stream);
    if (len == EOF) break;
    
    index_insert(string, len);
  }
  
  err = fclose(stream);
  if (err == EOF) {
    perror("fclose");
    return 3;
  }
  
  
  EXIT = MAGIC "exit";
  
  while (1) {
    len = getline(&string, &length, stdin);
    if (len == EOF) break;
    
    if (MAGIC string == EXIT) break;
    
    inside_index = index_search(string, len);
    
    if (inside_index)
         puts("YES");
    else puts("NO");
  }
  
  return 0;
}

