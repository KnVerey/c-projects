#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define READ_CHUNKS 100

int main(void){
  int sockfd;
  struct addrinfo hints, *res;
  int readme;
  int actually_read;
  char buffer[READ_CHUNKS];

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  getaddrinfo("0.0.0.0", "1234", &hints, &res);

  readme = open("readme.txt", O_RDONLY);

  if (readme >= 0) {
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    if (sockfd > 0) {
      connect(sockfd, res->ai_addr, res->ai_addrlen);

      while(1) {
        actually_read = read(readme, buffer, READ_CHUNKS);
        if (actually_read==0)
          break;
        send(sockfd, buffer, actually_read, 0);
      }

      close(sockfd);

    } else {
      printf("Socket creation error %s\n", strerror(errno));
    }

    close(readme);
  } else {
    printf("Read file open error %s\n", strerror(errno));
  }

  freeaddrinfo(res);
}
