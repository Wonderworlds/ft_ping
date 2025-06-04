#include "ft_ping.h"

void usage()
{
    printf("Usage\n");
    printf("\tft_ping [options] <destination>\n");
    printf("\n");
    printf("Options:\n");
    printf("\t<destination>      dns name or ip address\n");
    printf("\t-c <count>         stop after <count> replies\n");
    printf("\t-?                 print help and exit\n");
    printf("\t-i <interval>      seconds between sending each packet\n");
    printf("\t-t <ttl>           define time to live\n");
    printf("\t-v                 verbose output\n");
    printf("\n");
    printf("For more details see ping(8).\n");
}

int _error(const char *msg)
{
    fprintf(stderr, "Error: %s\n", msg);
    usage();
    return 1;
}

int validate_args(int argc, char **argv, t_ping *ping)
{
    int index = 1, value = 0, j = 0;
    size_t len;

    if (argc < 2)
        return _error("No arguments provided");

    while (index < argc)
    {
        if (argv[index][0] != '-')
        {
            if (ping->destination == NULL)
                ping->destination = argv[index];
            else
            {
                fprintf(stderr, "Error: Multiple destination arguments provided.\n");
                return 1;
            }
        }
        else
        {
            j = 1;
            len = strlen(argv[index]);
            if (len > 2)
            {
                while (argv[index][j] != '\0')
                {
                    switch (argv[index][j])
                    {
                    case '?':
                    {
                        usage();
                        return -1;
                    }
                    case 'v':
                    {
                        ping->verbose = 1;
                        break;
                    }

                    default:
                    {
                        fprintf(stderr, "Error: Invalid option '%c'.\n", argv[index][j]);
                        return 1;
                    }
                    }

                    j++;
                }
            }
            else if (len == 2)
            {
                switch (argv[index][j])
                {
                case '?':
                {
                    usage();
                    return -1;
                }
                case 'v':
                {
                    ping->verbose = 1;
                    break;
                }
                case 'c':
                {
                    value = atoi(argv[++index]);
                    ping->count = value;
                    break;
                }
                case 'i':
                {
                    value = atoi(argv[++index]);
                    ping->interval = value;
                    break;
                }
                case 't':
                {
                    value = atoi(argv[++index]);
                    ping->ttl = value;
                    break;
                }

                default:
                {
                    fprintf(stderr, "Error: Invalid option '%c'.\n", argv[index][j]);
                    return 1;
                }
                }
            }
            else
            {
                fprintf(stderr, "Error: Invalid option '%s'.\n", argv[index]);
                break;
            }
        }
        index++;
    }

    if (ping->destination == NULL)
    {
        fprintf(stderr, "ft_ping: usage error: Destination address required\n");
        return 1;
    }

    if (index == argc)
        return 0;

    return 1;
}

void print_ping_info(const t_ping *ping)
{
    printf("Ping Information:\n");
    printf("Destination: %s\n", ping->destination ? ping->destination : "NULL");
    printf("Count: %d\n", ping->count);
    printf("Interval: %d seconds\n", ping->interval);
    printf("TTL: %d\n", ping->ttl);
    printf("Verbose: %s\n", ping->verbose ? "Enabled" : "Disabled");
}

int main(int argc, char **argv)
{
    t_ping ping = {-1, 1, 64, 0, NULL};
    int validate_result;

    validate_result = validate_args(argc, argv, &ping);
    if (validate_result == 1)
    {
        return 1;
    }
    else if (validate_result == -1)
    {
        return 0; // Help was printed, exit gracefully
    }
    print_ping_info(&ping);

    return 0;
}