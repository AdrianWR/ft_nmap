#include "nmap.h"
#include <arpa/inet.h>
#include <memory.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

// Compute checksum of IP header
// Refer to https://www.ietf.org/rfc/rfc793.txt for reference
unsigned short ft_checksum(unsigned short *ptr, int nbytes) {
  register long sum;
  unsigned short oddbyte;
  register unsigned short answer;

  sum = 0;
  while (nbytes > 1) {
    sum += *ptr++;
    nbytes -= 2;
  }

  if (nbytes == 1) {
    oddbyte = 0;
    *((unsigned char *)&oddbyte) = *(unsigned char *)ptr;
    sum += oddbyte;
  }

  sum = (sum >> 16) + (sum & 0xffff);
  sum += (sum >> 16);
  answer = (unsigned short)~sum;

  return (answer);
}

const char *setup_packet(struct in_addr src, struct in_addr dest,
                         in_port_t port) {
  static char packet[PACKET_SIZE];

  // Clear packet buffer
  memset(packet, 0, PACKET_SIZE);

  // Set IP header
  struct iphdr *iph = (struct iphdr *)packet;
  iph->ihl = 5;
  iph->version = 4;
  iph->tos = 0;
  iph->tot_len = sizeof(struct iphdr) + sizeof(struct tcphdr);
  // iph->id = htons(36521);
  iph->frag_off = 0;
  iph->ttl = 64;
  iph->protocol = IPPROTO_TCP;
  iph->check = 0;
  iph->saddr = src.s_addr;
  iph->daddr = dest.s_addr;
  iph->check = ft_checksum((uint16_t *)packet, iph->tot_len);

  // Set TCP header
  struct tcphdr *tcph = (struct tcphdr *)(packet + sizeof(struct iphdr));
  tcph->source = htons(46300);
  tcph->dest = htons(port);
  tcph->seq = htonl(1105024978);
  tcph->ack_seq = 0;
  tcph->doff = (sizeof(struct tcphdr) / 4);
  tcph->fin = 0;
  tcph->syn = 1; // Set SYN flag
  tcph->rst = 0;
  tcph->psh = 0;
  tcph->ack = 0;
  tcph->urg = 0;
  tcph->window = htons(14600); /* maximum allowed window size */
  tcph->check = 0; /* if you set a checksum to zero, your kernel's IP stack
                     should fill in the correct checksum during transmission */
  tcph->urg_ptr = 0;

  return (packet);
}
