#include "nmap.h"
#include <arpa/inet.h>
#include <memory.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

/**
 ** Get the local IP address of the machine
 ** by sending a UDP packet to a DNS server.
 ** @param ip pointer to the struct in_addr to store the IP address
 ** @return error code
 */
int get_local_ip(char *buffer) {
  int sockfd;
  struct sockaddr_in server_addr, local_addr;
  socklen_t addr_len;

  addr_len = sizeof(local_addr);

  // Create a datagram socket
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) {
    perror("socket");
    return (-1);
  }

  // Connect to a DNS server
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(DNS_PORT);
  inet_pton(AF_INET, DNS_SERVER, &server_addr.sin_addr);

  if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
      0) {
    perror("connect");
    close(sockfd);
    return (-1);
  }

  // Get the local IP address
  if (getsockname(sockfd, (struct sockaddr *)&local_addr, &addr_len) < 0) {
    perror("getsockname");
    close(sockfd);
    return (-1);
  }

  if (inet_ntop(AF_INET, &local_addr.sin_addr, buffer, INET_ADDRSTRLEN) ==
      NULL) {
    perror("inet_ntop");
    close(sockfd);
    return (-1);
  }

  // Close the sock
  close(sockfd);
  return (0);
}
