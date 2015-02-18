#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

#define READ_CHUNKS 100

int main(void){
  int readme;
  int writeme;
  int actually_read;
  char buffer[READ_CHUNKS];

  readme = open("readme.txt", O_RDONLY);

  if (readme > 0) {
    writeme = open("writeme.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    if (writeme > 0) {
      while(1) {
        actually_read = read(readme, buffer, READ_CHUNKS);
        if (actually_read==0)
          break;
        write(writeme, buffer, actually_read);
      }

      close(writeme);

    } else {
      printf("Write file open error %s\n", strerror(errno));
    }

    close(readme);

  } else {
    printf("Read file open error %s\n", strerror(errno));
  }
}
