#include "error.h"
#include "nmap.h"
#include <argp.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

const char *argp_program_version = "ft_nmap 1.0";

const char *argp_program_bug_address = "<aroque@student.42sp.org.br>";

static char doc[] =
    "nmap -- Network exploration tool and security / port scanner";

static char args_doc[] = "";

static struct argp_option options[] = {
    {"ports", OPT_PORT_KEY, "NUMBER/RANGE", 0,
     "Ports to scan (eg: 1-10 or 1,2,3 or 1,5-15)", 0},
    {"ip", OPT_ADDRESS_KEY, "IP_ADDRESS", 0,
     "Ip addresses to scan in dot format", 0},
    {"file", OPT_FILE_KEY, "FILE", 0,
     "File name containing IP addresses to scan", 0},
    {"speedup", OPT_SPEEDUP_KEY, "NUMBER", 0,
     "[250 max] Number of parallel threads to use", 0},
    {"scan", OPT_SCAN_KEY, "TYPE", 0, "SYN/NULL/FIN/XMAS/ACK/UDP", 0},
    {0}};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
  t_arguments *args = state->input;

  switch (key) {
  case OPT_PORT_KEY:
    args->ports = arg;
    break;
  case OPT_ADDRESS_KEY:
    args->address = arg;
    break;
  case OPT_FILE_KEY:
    args->address_file = arg;
    break;
  case OPT_SPEEDUP_KEY:
    args->threads = arg;
    break;
  case OPT_SCAN_KEY:
    args->scan = arg;
    break;
  default:
    return (ARGP_ERR_UNKNOWN);
  }
  return (0);
}

static struct argp argp = {options, parse_opt, args_doc, doc, 0, 0, 0};

int main(int argc, char *argv[]) {
  int ret;
  t_nmap nmap;
  t_arguments cmd_args;

  ret = 0;
  memset(&cmd_args, 0, sizeof(t_arguments));
  if ((argp_parse(&argp, argc, argv, 0, 0, &cmd_args) != 0)) {
    fprintf(stderr, "Error parsing arguments.\n");
    return (EXIT_FAILURE);
  }

  // Default values
  memset(&nmap, 0, sizeof(t_nmap));
  nmap.threads = 1;
  nmap.scan = ALL;
  for (int i = PORT_MIN; i < DEFAULT_PORT_MAX; i++)
    nmap.ports[i] = i + 1;

  ret = parse_options(&nmap, &cmd_args);
  if (ret != 0) {
    print_err(ret);
    return (EXIT_FAILURE);
  }

  ret = run_scans(nmap);
  if (ret != 0) {
    return (EXIT_FAILURE);
  }

  return (EXIT_SUCCESS);
}
