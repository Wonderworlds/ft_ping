#ifndef FT_PING_H
#define FT_PING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_ping
{
    int count;         // Number of packets to send
    int interval;      // Interval between packets in seconds
    int ttl;           // Time to live for packets
    int verbose;       // Verbose output flag
    char *destination; // Destination IP or DNS name
} t_ping;

#endif