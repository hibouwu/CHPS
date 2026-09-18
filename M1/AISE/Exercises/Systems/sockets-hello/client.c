#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char ** argv) {
  if(argc < 3) {
    fprintf(stderr, "Usage: %s <port> <output_file>\n", argv[0]);
    return 1;
  }

  const char *output_path = argv[2];

  struct addrinfo hints, * result = NULL;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  const char *host = "localhost";

  int gairet = getaddrinfo(host, argv[1], &hints, &result);
  if(gairet != 0) {
    fprintf(stderr, "unable to retrieve address information: %s\n", gai_strerror(gairet));
    return 1;
  }

  int server = -1;
  int connected = 0;
  for(struct addrinfo * i = result; i != NULL; i = i->ai_next) {
    if((server = socket(i->ai_family, i->ai_socktype, i->ai_protocol)) < 0) {
      continue;
    }
    if(connect(server, i->ai_addr, i->ai_addrlen) < 0) {
      close(server);
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

  FILE *out = fopen(output_path, "wb");
  if(!out) {
    perror("unable to open output file");
    close(server);
    freeaddrinfo(result);
    return 1;
  }

  char buf[4096];
  ssize_t n;
  while((n = read(server, buf, sizeof(buf))) > 0) {
    if(fwrite(buf, 1, (size_t)n, out) != (size_t)n) {
      perror("failed to write output file");
      break;
    }
  }
  fclose(out);

  close(server);
  freeaddrinfo(result);

  return 0;
}
