#include "minunit.h"
#include "nmap.h"
#include <memory.h>
#include <stdint.h>
#include <stdio.h>

int tests_run = 0;

static void *test_parse_ports() {
  t_port ports[MAX_PORTS];
  int ret;

  memset(ports, 0, sizeof(ports));

  char arg[] = "1,3,10";
  ret = parse_ports(ports, arg);
  mu_assert("error, ret != 0", ret == 0);
  mu_assert("error, ports[0] != 1", ports[0] == 1);
  mu_assert("error, ports[1] != 3", ports[1] == 3);
  mu_assert("error, ports[2] != 10", ports[2] == 10);
  memset(ports, 0, sizeof(ports));

  char arg2[] = "1-3,5-7";
  ret = parse_ports(ports, arg2);
  mu_assert("error, ret != 0", ret == 0);
  mu_assert("error, ports[0] != 1", ports[0] == 1);
  mu_assert("error, ports[1] != 2", ports[1] == 2);
  mu_assert("error, ports[2] != 3", ports[2] == 3);
  mu_assert("error, ports[3] != 5", ports[3] == 5);
  mu_assert("error, ports[4] != 6", ports[4] == 6);
  mu_assert("error, ports[5] != 7", ports[5] == 7);
  memset(ports, 0, sizeof(ports));

  char arg3[] = "-21";
  ret = parse_ports(ports, arg3);
  mu_assert("error, ret == 0", ret != 0);

  char arg4[] = "21-";
  ret = parse_ports(ports, arg4);
  mu_assert("error, ret == 0", ret != 0);

  char arg5[] = "21-20";
  ret = parse_ports(ports, arg5);
  mu_assert("error, ret == 0", ret != 0);

  char arg6[] = "21-65536";
  ret = parse_ports(ports, arg6);
  mu_assert("error, ret == 0", ret != 0);

  return 0;
}

static void *test_parse_threads() {
  unsigned short threads;
  int ret;

  ret = parse_threads(&threads, "10");
  mu_assert("error, ret != 0", ret == 0);
  mu_assert("error, threads != 10", threads == 10);

  char arg2[] = "0";
  ret = parse_threads(&threads, arg2);
  mu_assert("error, ret == 0", ret != 0);

  char arg3[] = "251";
  ret = parse_threads(&threads, arg3);
  mu_assert("error, ret == 0", 1 != 0);

  return 0;
}

static void *test_parse_scan() {
  int ret;
  t_scan scan;

  scan = 0;
  ret = parse_scan(&scan, "SYN");
  mu_assert("error, ret != 0", ret == 0);
  mu_assert("error, scan != SYN", scan == SYN);

  scan = 0;
  ret = parse_scan(&scan, "NULL");
  mu_assert("error, ret != 0", ret == 0);
  mu_assert("error, scan != NULL_SCAN", scan == NULL_SCAN);

  scan = 0;
  ret = parse_scan(&scan, "");
  mu_assert("error, ret != 0", ret == 0);
  mu_assert("error, scan != ALL", scan == ALL);

  scan = 0;
  ret = parse_scan(&scan, "dummy");
  mu_assert("error, ret == 0", ret != 0);

  return 0;
}

static void *test_parse_address() {
  t_ip hosts[MAX_HOSTS];
  int ret;

  char arg[] = "127.0.0.1";
  memset(hosts, 0, sizeof(hosts));
  ret = parse_address(hosts, arg);
  mu_assert("error, ret != 0", ret == 0);
  mu_assert("error, hosts[0] != 16777343", hosts[0] == 16777343);

  char arg2[] = "8.8.8.8";
  memset(hosts, 0, sizeof(hosts));
  ret = parse_address(hosts, arg2);
  mu_assert("error, ret != 0", ret == 0);
  mu_assert("error, hosts[0] != 134744072", hosts[0] == 134744072);

  char arg3[] = "google.com";
  memset(hosts, 0, sizeof(hosts));
  ret = parse_address(hosts, arg3);
  mu_assert("error, ret != 0", ret == 0);

  char arg4[] = "dummy";
  memset(hosts, 0, sizeof(hosts));
  ret = parse_address(hosts, arg4);
  mu_assert("error, ret == 0", ret != 0);

  return (0);
}

static char *all_tests() {
  mu_run_test(test_parse_ports);
  mu_run_test(test_parse_threads);
  mu_run_test(test_parse_scan);
  mu_run_test(test_parse_address);
  return 0;
}

int main() {
  char *result = all_tests();
  if (result != 0) {
    printf("%s\n", result);
  } else {
    printf("ALL TESTS PASSED\n");
  }
  printf("Tests run: %d\n", tests_run);

  return result != 0;
}
