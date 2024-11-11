#include "nmap.h"
#include <arpa/inet.h>
#include <memory.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct pseudo_header {
  unsigned int source_addr;
  unsigned int dest_addr;
  unsigned char plc;
  unsigned char prt;
  unsigned short tcp_len;
  struct tcphdr tcp;
} t_psdhdr;

int send_packet(struct in_addr src, struct in_addr dest, t_port port) {
  int sockfd;
  t_psdhdr psh;
  struct sockaddr_in ip_dest;
  const char *packet;

  packet = setup_packet(src, dest, port);

  sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
  if (sockfd < 0) {
    perror("socket");
    return (1);
  }

  ip_dest.sin_family = AF_INET;
  ip_dest.sin_addr.s_addr = dest.s_addr;

  psh.source_addr = src.s_addr;
  psh.dest_addr = dest.s_addr;
  psh.plc = 0;
  psh.prt = IPPROTO_TCP;
  psh.tcp_len = htons(sizeof(struct tcphdr));

  memcpy(&psh.tcp, packet + sizeof(struct iphdr), sizeof(struct tcphdr));
  printf("Sending packet to %s:%d\n", inet_ntoa(ip_dest.sin_addr), port);

  if (sendto(sockfd, packet, sizeof(struct iphdr) + sizeof(struct tcphdr), 0,
             (struct sockaddr *)&ip_dest, sizeof(ip_dest)) < 0) {
    perror("sendto");
    return (1);
  }

  close(sockfd);
  return (0);
}
