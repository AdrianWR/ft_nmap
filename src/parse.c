#include "error.h"
#include "nmap.h"

int parse_options(t_nmap *nmap, t_arguments *args) {
  int ret;

  ret = 0;
  if (args->address_file) {
    ret = parse_address_file(nmap->hosts, args->address_file);
  } else if (args->address) {
    ret = parse_address(nmap->hosts, args->address);
  } else {
    ret = ERR_NO_HOSTS;
  }

  if (ret != 0) {
    return (ret);
  }

  if (args->ports) {
    ret = parse_ports(nmap->ports, args->ports);
    if (ret != 0) {
      return (ret);
    }
  }

  if (args->threads) {
    ret = parse_threads(&nmap->threads, args->threads);
    if (ret != 0) {
      return (ret);
    }
  }

  if (args->scan) {
    ret = parse_scan(&nmap->scan, args->scan);
    if (ret != 0) {
      return (ret);
    }
  }

  return (0);
}
