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
#include <signal.h>
#include <stdlib.h>
#include <pthread.h>

struct client_args {
  int client_fd;
  const char *filepath;
};

static void *send_file(void *arg) {
  struct client_args *cargs = (struct client_args *)arg;
  int client_socket = cargs->client_fd;
  const char *file_path = cargs->filepath;
  free(cargs);

  int file = open(file_path, O_RDONLY);
  if(file < 0) {
    perror("unable to open the file to share");
    close(client_socket);
    return NULL;
  }

  char buffer[4096];
  ssize_t reading;
  while((reading = read(file, buffer, sizeof(buffer))) > 0) {
    ssize_t sent = 0;
    while(sent < reading) {
      ssize_t writing = write(client_socket, buffer + sent, reading - sent);
      if(writing < 0) {
        perror("unable to send file to client");
        close(file);
        close(client_socket);
        return NULL;
      }
      sent += writing;
    }
  }
  if(reading < 0) {
    perror("error reading the file to share");
  }

  close(file);
  close(client_socket);
  return NULL;
}



int main(int argc, char ** argv) {
  if(argc < 3) {
    fprintf(stderr, "Error: missing port number and file name!\n");
    return 1;
  }

  struct addrinfo hints, * result = NULL;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  if(getaddrinfo(NULL, argv[1], &hints, &result) < 0) {
    perror("unable to retrieve address information");
    return 1;
  }

  int listener = -1;
  int bound = 0;
  for(struct addrinfo * i = result; i != NULL; i = i->ai_next) {
    if((listener = socket(i->ai_family, i->ai_socktype, i->ai_protocol)) < 0) {
      continue;
    }
    if(bind(listener, i->ai_addr, i->ai_addrlen) < 0) {
      continue;
    } else {
      bound = 1;
      break;
    }
  }

  if(!bound) {
    fprintf(stderr, "unable to bind the listening socket to port %s", argv[1]);
    return 1;
  }

  if(listen(listener, 10) < 0) {
    perror("unable to listen");
    return 1;
  }

  printf("Serving file '%s' on port %s (multi-client, threaded)\n", argv[2], argv[1]);

  for(;;) {
    int client = accept(listener, NULL, NULL);
    if(client < 0) {
      perror("unable to accept client");
      continue;
    }

    struct client_args *cargs = malloc(sizeof(struct client_args));
    if(!cargs) {
      perror("malloc failed");
      close(client);
      continue;
    }
    cargs->client_fd = client;
    cargs->filepath = argv[2];

    pthread_t tid;
    if(pthread_create(&tid, NULL, send_file, cargs) != 0) {
      perror("pthread_create failed");
      close(client);
      free(cargs);
      continue;
    }
    pthread_detach(tid);
  }
  
  freeaddrinfo(result);
  
  return 0;
}
