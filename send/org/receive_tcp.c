#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUF_SIZE 2048
#define WAIT_QUEUE_SIZE 10

int main(int argc, char *argv[]) {
  int sock;
  int acc_sock;
  struct sockaddr_in addr;
  struct sockaddr_in from_addr;
  socklen_t sin_size = sizeof(struct sockaddr_in);
  char buf[BUF_SIZE];
  // char *massages = "hogehoge";

  // 受信バッファの初期化
  memset(buf, 0, sizeof(buf));

  if ( (sock = socket(PF_INET, SOCK_STREAM, 0)) < 0 ) {
    perror("socket");
    exit(1);
  }

  // 待ち受けIP&ポート設定
  addr.sin_family = PF_INET;
  addr.sin_port = htons(22222);
  addr.sin_addr.s_addr = INADDR_ANY;

  if ( bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0 ) {
    perror("bind");
    exit(1);
  }

  if ( listen(sock, WAIT_QUEUE_SIZE) < 0 ) {
    perror("listen");
    exit(1);
  }

  if ( (acc_sock=accept(sock, (struct sockaddr *)&from_addr, &sin_size)) < 0 ) {
    perror("accept");
    exit(1);
  }

  if ( recv(acc_sock, buf, sizeof(buf), 0) < 0 ) {
    perror("recv");
    exit(1);
  }

  // if (send(sock, *messages, sizeof(*messages), 0) < 0) {
  //   perror("send");
  //   return -1;
  // }

  // write();
  // read();
  // setsockopt();
  // getsockopt();

  close(sock);
  close(acc_sock);

  printf("%s\n", buf);

  return 0;
}


