#include "error.h"
#include "nmap.h"
#include <string.h>

const char *scans[SCANS_LEN] = {
    "SYN", "NULL", "ACK", "FIN", "XMAS", "UDP",
};

/* Parse the scan type from the argument. If the argument is not a valid scan
 * type, return an error. */
int parse_scan(t_scan *scan, char *arg) {
  if (!arg || !strlen(arg)) {
    *scan = ALL; // Default scan type
    return (0);
  }

  for (unsigned int i = 0; i < SCANS_LEN; i++) {
    if (!strncmp(arg, scans[i], strlen(scans[i]))) {
      *scan = i + 1; // +1 because UNDEFINED is 0
      return (0);
    }
  }

  return (ERR_SCAN_TYPE);
}
