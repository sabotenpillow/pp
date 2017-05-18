#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MESSAGE_SIZE 20
#define BUF_SIZE 2048

int main(int argc, char *argv[]) {
  int sock;
  struct sockaddr_in addr;
  // char messages[] = "hogehoge";
  // char *messages = "hogehoge";
  char messages[MESSAGE_SIZE];
  char buf[BUF_SIZE];

  if (argc != 2) {
    puts("argument is lack or too much");
  }
  strcpy(messages, argv[1]);
  // printf("%s\n", messages);
  // printf("%d\n", sizeof(*messages));

  if ( (sock = socket(PF_INET, SOCK_STREAM, 0)) < 0 ) {
    puts("Failed to create socket");
    exit(1);
  }

  addr.sin_family = PF_INET;
  addr.sin_port = htons(22222);
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  if ( connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1 ) {
    perror("connect");
    exit(1);
  }

  if ( send(sock, messages, sizeof(messages), 0) < 0 ) {
  // if ( send(sock, "i am send process", 17, 0) < 0 ) {
    perror("send");
    return -1;
  }

  if ( recv(sock, buf, sizeof(buf), 0) < 0 ) {
    perror("recv");
    exit(1);
  }

  // write();
  // read();

  // setsockopt();
  // getsockopt();

  close(sock);

  return 0;
}

