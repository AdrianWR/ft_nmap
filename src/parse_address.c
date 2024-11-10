#include "error.h"
#include "nmap.h"
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

int address_lookup(struct sockaddr_in *addr_in, const char *host) {
  int err;
  struct addrinfo hints;
  struct addrinfo *res;
  int ai_family;

  hints.ai_family = AF_INET;
  hints.ai_socktype = 0;
  hints.ai_protocol = 0;
  hints.ai_flags = AI_CANONNAME;

  if ((err = getaddrinfo(host, NULL, &hints, &res))) {
    fprintf(stderr, "Network error: %s\n", gai_strerror(err));
    return (err);
  }

  *addr_in = *(struct sockaddr_in *)(res->ai_addr);
  ai_family = res->ai_family;
  freeaddrinfo(res);

  if (ai_family != AF_INET) {
    return (EAI_FAMILY);
  }

  return (0);
}

static int add_host(t_ip hosts[], t_ip host) {
  static int i;

  // TODO: Check if port already exists
  // Set data type to handle this
  if (i < MAX_HOSTS) {
    hosts[i] = host;
    i++;
    return (0);
  }

  return (ERR_MAX_HOSTS);
}

int parse_address(t_ip hosts[], char *arg) {
  int err;
  struct sockaddr_in addr_in;

  err = 0;
  if (!arg || !strlen(arg)) {
    return (ERR_PARSE_OPT);
  }

  if ((err = address_lookup(&addr_in, arg))) {
    return (ERR_ADDRESS_LOOKUP);
  }

  err = add_host(hosts, addr_in.sin_addr);

  return (err);
}
