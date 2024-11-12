#include "error.h"
#include "get_next_line.h"
#include "nmap.h"
#include <fcntl.h>
#include <unistd.h>

/* Addresses inserted in the parsed file must be
 * inserted line by line. If the
 * format is invalid, return an error.
 * If the file is not found, return an error.
 * If the file is empty, return an error.
 * If the file contains more than MAX_HOSTS addresses,
 * return an error. If the file contains an invalid address,
 * return an error.
 */

int parse_address_file(t_ip hosts[], size_t *hosts_len, char *arg) {
  int fd;
  char *line;
  int ret;
  int i;

  fd = open(arg, O_RDONLY);
  if (fd == -1) {
    return (ERR_ADDRESS_FILE);
  }

  i = 0;
  while ((ret = get_next_line(fd, &line)) > 0) {
    if (i >= MAX_HOSTS) {
      return (ERR_MAX_HOSTS);
    }
    if ((ret = parse_address(&hosts[i], line))) {
      return (ret);
    }
    i++;
    (*hosts_len)++;
    free(line);
  }

  if (ret == GNL_FAILURE) {
    return (ERR_ADDRESS_FILE);
  }

  close(fd);
  return (0);
}
