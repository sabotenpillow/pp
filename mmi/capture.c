#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <linux/if_ether.h>
#include <linux/filter.h>
#include <netpacket/packet.h>
#include <net/if.h>

#define BUF_NUM 4096

int main(void) {
  int soc;
  struct ifreq ifr;
  struct sockaddr_ll sll;
  unsigned char buf[BUF_NUM];

  memset(&ifr, 0, sizeof(ifr));
  memset(&sll, 0, sizeof(sll));

  soc = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

  strncpy(ifr.ifr_name, "br0", IFNAMSIZ);
  ioctl(soc, SIOCGIFINDEX, &ifr);

  sll.sll_family = AF_PACKET;
  sll.sll_protocol = htons(ETH_P_ALL);
  sll.sll_ifindex = ifr.ifr_ifindex;
  bind(soc, (struct sockaddr *)&sll, sizeof(sll));

  while(1) {
    ssize_t len = recv(soc, buf, sizeof(buf), 0);
    struct ethhdr* ethhdr = (struct ethhdr*)buf;
    int proto = ntohs(ethhdr->h_proto);
    if(len <= 0) break;
    printf("%3ld %0x %s \n", len, proto,
        proto == ETH_P_ARP ? "arp" : proto == ETH_P_IP ? "ip" : "other");
  }
  return 0;
}


