#include <sys/type.h>
#include <sys/socket.h>

int main(int argc, char *argv[]) {
  int sock;

  if ( (sock = socket(PF_PACKET, SOCK_RAW, 0)) == -1 ) {
    puts("Fail to create socket");
    return 1;
  }

  bind();
  write();
  read();

  // setsockopt();
  // getsockopt();
  // conect();
  // send();
  // recv();

  close(sock);

  return 0;
}

