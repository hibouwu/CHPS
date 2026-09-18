#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char ** argv) {
  if(argc < 3) {
    fprintf(stderr, "Usage: %s <port> <fichier_a_partager>\n", argv[0]);
    return 1;
  }

  const char *file_path = argv[2];

  struct addrinfo hints, * result = NULL;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE; // bind on all interfaces

  int gairet = getaddrinfo(NULL, argv[1], &hints, &result);
  if(gairet != 0) {
    fprintf(stderr, "unable to retrieve address information: %s\n", gai_strerror(gairet));
    return 1;
  }

  int listener = -1;
  int bound = 0;
  for(struct addrinfo * i = result; i != NULL; i = i->ai_next) {
    if((listener = socket(i->ai_family, i->ai_socktype, i->ai_protocol)) < 0) {
      continue;
    }
    if(bind(listener, i->ai_addr, i->ai_addrlen) < 0) {
      close(listener);
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

  signal(SIGCHLD, SIG_IGN); // avoid zombie children

  printf("Server listening on port %s, serving file %s\n", argv[1], file_path);

  for(;;) {
    int client = accept(listener, NULL, NULL);
    if(client < 0) {
      perror("unable to accept client");
      continue;
    }

    pid_t pid = fork();
    if(pid < 0) {
      perror("fork failed");
      close(client);
      continue;
    }
    if(pid == 0) {
      // child process: send file then exit
      close(listener);
      FILE *fp = fopen(file_path, "rb");
      if(!fp) {
        perror("unable to open file to share");
        close(client);
        _exit(1);
      }
      char buf[4096];
      size_t nread;
      while((nread = fread(buf, 1, sizeof(buf), fp)) > 0) {
        size_t sent = 0;
        while(sent < nread) {
          ssize_t w = write(client, buf + sent, nread - sent);
          if(w < 0) {
            perror("unable to send file chunk");
            fclose(fp);
            close(client);
            _exit(1);
          }
          sent += (size_t)w;
        }
      }
      fclose(fp);
      close(client);
      _exit(0);
    } else {
      // parent: continue accepting
      close(client);
    }
  }
  // unreachable
  return 0;
}
