

#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define SIZE    100

// Header format
typedef struct
{
    int	seq_ack;
    int len; // for ACK packets len = 0
    int checksum;
} HEADER;


// Packet format
typedef struct
{
    HEADER	header;
    char	data[SIZE]; // data in the packet
} PACKET;


