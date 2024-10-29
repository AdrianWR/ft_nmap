#include <regex.h>
#include <stdbool.h>
#include <stdlib.h>

bool matches_regex(char *pattern, char *string) {
  regex_t regex;
  int ret;

  if (regcomp(&regex, pattern, REG_EXTENDED)) {
    return (false);
  }
  ret = regexec(&regex, string, 0, NULL, 0);
  regfree(&regex);
  return (ret == 0);
}
