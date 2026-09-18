#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char ** argv) {
  if(argc < 3) {
    fprintf(stderr, "Error: missing port number or service descriptor!\n");
    return 1;
  }

  struct addrinfo hints, * result = NULL;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  if(getaddrinfo(NULL, argv[1], &hints, &result) < 0) {
    perror("unable to retrieve address information");
    return 1;
  }

  int server = -1;
  int connected = 0;
  for(struct addrinfo * i = result; i != NULL; i = i->ai_next) {
    if((server = socket(i->ai_family, i->ai_socktype, i->ai_protocol)) < 0) {
      continue;
    }
    if(connect(server, i->ai_addr, i->ai_addrlen) < 0) {
      continue;
    } else {
      connected = 1;
      break;
    }
  }

  if(!connected) {
    fprintf(stderr, "unable to connect to the server on port %s", argv[1]);
    return 1;
  }

  int file = open(argv[2], O_WRONLY | O_CREAT, 0644);
  if(file < 0) {
    perror("unable to open local file");
    return 1;
  }
  
  char buffer[128];
  ssize_t reading, writing;
  do {
    memset(buffer, '\0', 128);
    reading = read(server, buffer, 128);
    if(reading < 0) {
      perror("unable to receive file from server");
      return 1;
    }
    writing = write(file, buffer, reading);
    if(writing < 0) {
      perror("unable to write to local file");
      return 1;
    }
  } while(reading > 0);

  close(file);
  close(server);

  printf("File received.\n");
  
  freeaddrinfo(result);
  
  return 0;
}
