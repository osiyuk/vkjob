/* main
 *   open file
 *   read string from stdin
 *   if EOF
 *     exit
 *   write string to file
 *   if string is exit
 *     exit
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>

#define APPEND_ONLY (O_WRONLY | O_APPEND | O_CREAT)
#define MAGIC * (unsigned *)

unsigned EXIT;


int main(int argc, char *argv[])
{
  int fd;
  ssize_t err, len;
  char * string;
  size_t length;
  
  EXIT = MAGIC "exit";
  printf("MAGIC EXIT 0x%x\n", EXIT);
  
  if (argc < 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    return 1;
  }
  
  fd = open(argv[1], APPEND_ONLY, 0644);
  if (fd == -1) goto error;
  
  while (1) {
    len = getline(&string, &length, stdin);
    if (len == EOF) break;
    
    if (MAGIC string == EXIT) break;
    
    err = write(fd, string, len);
    if (err != len) goto error;
  }
  
  close(fd);
  return 0;
  
error:
  perror(NULL);
  return 2;
}

