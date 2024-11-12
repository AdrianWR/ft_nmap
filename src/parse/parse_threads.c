#include "error.h"
#include "nmap.h"
#include <stdlib.h>

/*
 ** Parse the number of threads from the argument.
 ** If the argument is not a number or the number is
 ** greater than 250, return an error.
 */
int parse_threads(unsigned short *threads, char *arg) {
  if (!matches_regex(THREADS_REGEX, arg))
    return (ERR_PARSE_OPT);

  *threads = atoi(arg);
  if (*threads > MAX_THREADS || *threads <= 0)
    return (ERR_THREAD_RANGE);

  return (0);
}
