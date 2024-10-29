#ifndef ERROR_H
#define ERROR_H

enum e_error {
  ERR_NONE = 0,
  ERR_PARSE_OPT,
  ERR_PORT_RANGE,
  ERR_THREAD_RANGE,
  ERR_SCAN_TYPE,
  ERR_MAX_PORTS,
  ERR_MAX_HOSTS,
  ERR_ADDRESS_LOOKUP,
  ERR_ADDRESS_FILE,
  ERR_NO_HOSTS,
};

typedef enum e_error t_error;

const char *nmap_strerror(t_error err);
int print_err(t_error err);

#endif
