#include "error.h"
#include <stdio.h>
#include <stdlib.h>

const char *nmap_strerror(t_error err) {
  switch (err) {
  case ERR_PARSE_OPT:
    return ("Error parsing option.");
  case ERR_PORT_RANGE:
    return ("Invalid port range.");
  case ERR_THREAD_RANGE:
    return ("Invalid number of threads.");
  case ERR_SCAN_TYPE:
    return ("Invalid scan type.");
  case ERR_MAX_PORTS:
    return ("Too many ports.");
  case ERR_MAX_HOSTS:
    return ("Too many hosts.");
  case ERR_ADDRESS_LOOKUP:
    return ("Address lookup failed.");
  case ERR_ADDRESS_FILE:
    return ("Error opening address file.");
  case ERR_NO_HOSTS:
    return ("No hosts specified.");
  default:
    return (NULL);
  }
}

int print_err(t_error err) {
  const char *str;

  str = nmap_strerror(err);
  if (str) {
    return fprintf(stderr, "Error: %s\n", str);
  }

  return (fprintf(stderr, "Unknown error.\n"));
}
