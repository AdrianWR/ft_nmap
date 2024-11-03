#include "error.h"
#include "nmap.h"
#include <regex.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static int add_port(t_port ports[], t_port port) {
  int i;

  for (i = 0; i < PORT_MAX; i++) {
    if (ports[i] == 0 || ports[i] == port) {
      ports[i] = port;
      return (0);
    }
  }
  return (ERR_MAX_PORTS);
}

static int parse_port_range(t_port ports[], char *token) {
  int err;
  t_port port;
  t_port range[2];
  char *saveptr;

  err = 0;
  range[0] = atoi(strtok_r(token, "-", &saveptr));
  range[1] = atoi(strtok_r(NULL, "-", &saveptr));

  if (range[0] < PORT_MIN || range[1] > PORT_MAX || range[0] > range[1]) {
    return (ERR_PORT_RANGE);
  }

  for (port = range[0]; port <= range[1]; port++) {
    if ((err = add_port(ports, port))) {
      break;
    }
  }
  return (err);
}

static int parse_single_port(t_port ports[], char *token) {
  t_port port;

  port = atoi(token);
  if (port < PORT_MIN || port > PORT_MAX) {
    return (ERR_PORT_RANGE);
  }
  return (add_port(ports, port));
}

int parse_ports(t_port ports[], char *arg) {
  char *token;
  char *saveptr;
  int err;

  // Clean default values
  memset(ports, 0, sizeof(t_port) * PORT_MAX);

  err = 0;
  token = strtok_r(arg, ",", &saveptr);

  while (token) {
    if (matches_regex(PORT_RANGE_REGEX, token)) {
      err = parse_port_range(ports, token);
    } else if (matches_regex(PORT_REGEX, token)) {
      err = parse_single_port(ports, token);
    } else {
      err = ERR_PARSE_OPT;
    }
    // Returns if err, continue otherwise
    token = err ? NULL : strtok_r(NULL, ",", &saveptr);
  }
  return (err);
}
