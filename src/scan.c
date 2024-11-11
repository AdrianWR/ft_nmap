#include "nmap.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>

static const char *ip_address(struct in_addr ip) {
  static char buffer[INET_ADDRSTRLEN];
  // use inet_ntop to convert ip to string
  inet_ntop(AF_INET, &ip, buffer, INET_ADDRSTRLEN);

  return (buffer);
}

int scan_ip(t_ip ip, t_nmap nmap) {
  int ret;
  size_t i;

  struct in_addr src;

  // Convert local IP to struct in_addr
  if (inet_pton(AF_INET, nmap.local_ip, &src) != 1) {
    fprintf(stderr, "Error converting local IP to struct in_addr\n");
    return (-1);
  }

  for (i = 0; i < nmap.ports_len; i++) {
    ret = send_packet(src, ip, nmap.ports[i]);
    if (ret != 0) {
      printf("Error sending packet to %s:%d\n", ip_address(ip), nmap.ports[i]);
      return (ret);
    }
  }

  return (0);
}

int run_scans(t_nmap nmap) {
  int ret;
  size_t i;

  // Get local IP address
  if (get_local_ip(nmap.local_ip) != 0) {
    return (-1);
  }

  ret = 0;
  for (i = 0; i < nmap.hosts_len; i++) {
    ret = scan_ip(nmap.hosts[i], nmap);
    if (ret != 0) {
      return (ret);
    }
  }

  return (0);
}
