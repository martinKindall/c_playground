/* Use: mycp from to */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define SIZE 8192

int main(int argc, char *argv[]) {
  int in, out;
  ssize_t n;
  char buf[SIZE];
  
  if (argc!=3) {
    fprintf(stderr, "Use: %s <from> <to>\n", argv[0]);
    exit(1);
  }
  
  if ((in= open(argv[1], O_RDONLY))==-1) {
    perror(argv[1]);
    exit(2);
  }
  
  if ((out= creat(argv[2], 0666))==-1) {
    perror(argv[2]);
    exit(3);
  }
  
  while ((n= read(in, buf, SIZE))>0) {
    if (write(out, buf, n)!=n) {
      perror(argv[2]);
      exit(4);
    }
  }
  
  if (n<0) {
    perror(argv[1]);
    exit(5);
  }
  
  close(in);
  close(out);
  
  return 0;
}