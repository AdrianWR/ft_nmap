#ifndef NMAP_H
#define NMAP_H

#include <netinet/in.h>
#include <stdbool.h>
#include <stdint.h>

#define OPT_PORT_KEY 500
#define OPT_ADDRESS_KEY 501
#define OPT_FILE_KEY 502
#define OPT_SPEEDUP_KEY 503
#define OPT_SCAN_KEY 504

#define PORT_RANGE_REGEX "^[0-9]+-[0-9]+$"
#define PORT_REGEX "^[0-9]+$"
#define THREADS_REGEX "^[0-9]+$"
#define IP_REGEX "^[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+$"
#define FQDN_REGEX "^[a-zA-Z0-9.-]+$"
#define SCAN_REGEX "^(SYN|NULL|ACK|FIN|XMAS|UDP)$"

#define PORT_MIN 0
#define PORT_MAX 65535
#define DEFAULT_PORT_MAX 1024

#define MAX_HOSTS 1024
#define MAX_THREADS 250

#define SCANS_LEN 6

typedef in_addr_t t_ip;
typedef in_port_t t_port;

typedef enum e_scan {
  UNDEFINED = 0,
  SYN = 1 << 0,
  NULL_SCAN = 1 << 1,
  FIN = 1 << 2,
  XMAS = 1 << 3,
  ACK = 1 << 4,
  UDP = 1 << 5,
  ALL = SYN | NULL_SCAN | FIN | XMAS | ACK | UDP,
} t_scan;

extern const char *scans[SCANS_LEN]; // Defined in parse_scan.c

typedef struct arguments {
  char *ports;
  char *address;
  char *address_file;
  char *threads;
  char *scan;
} t_arguments;

typedef struct s_nmap {
  t_ip hosts[MAX_HOSTS];
  t_port ports[PORT_MAX];
  unsigned short threads;
  t_scan scan;
} t_nmap;

int parse_options(t_nmap *nmap, t_arguments *args);
int parse_ports(t_port ports[], char *arg);
int parse_threads(unsigned short *threads, char *arg);
int parse_address(t_ip hosts[], char *arg);
int parse_address_file(t_ip hosts[], char *arg);
int parse_scan(t_scan *scan, char *arg);

bool matches_regex(char *pattern, char *string);

#endif
