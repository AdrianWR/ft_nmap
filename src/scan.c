#include "nmap.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>

static const char *ip_address(t_ip ip) {
  static char buffer[INET_ADDRSTRLEN];
  // use inet_ntop to convert ip to string
  inet_ntop(AF_INET, &ip, buffer, INET_ADDRSTRLEN);

  return (buffer);
}

int scan_ip(t_ip ip, t_nmap nmap) {
  size_t i;

  printf("Scanning IP: %s\n", ip_address(ip));
  for (i = 0; i < nmap.ports_len; i++) {
    printf("Scanning port: %d\n", nmap.ports[i]);
  }

  return (0);
}

int run_scans(t_nmap nmap) {
  int ret;
  size_t i;

  ret = 0;
  for (i = 0; i < nmap.hosts_len; i++) {
    ret = scan_ip(nmap.hosts[i], nmap);
    if (ret != 0) {
      return (ret);
    }
  }

  return (0);
}
