// SCU COEN 146
//
// This program implements the server side of stop & wait protocol
// the server receives file contents from a client
//
//
// For the stop and wait protocol, the assumestions are:
//      -- packet corruption, and packet loss


#include	"tfv1.h"

// global variables
int state = 0; // we only have two states: 0 and 1
int sock;
struct sockaddr_in serverAddr;
socklen_t addr_size;


// list of functions
int main (int, char *[]);
int my_receive (PACKET *);
int calc_checksum (char *, int);



int main (int argc, char *argv[])
{
	FILE	*fp;
	int		n;
	PACKET	buf;


    if (argc != 2)
    {
        printf ("need the port number\n");
        return 1;
    }

    
    // STUDENT WORK
    

	// create socket
	if ((sock = socket (AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		printf ("socket error\n");
		return 1;
	}

	// bind
	if (bind (sock, (struct sockaddr *)&serverAddr, sizeof (serverAddr)) != 0)
	{
		printf ("bind error\n");
		return 1;
	}

    // NOTE: this program uses UDP socket, so there is no need to listen to incoming connections!
    
	// receive name of the file
    // my_receive() function ensures the received data chunks are not corrupted
	if ((n = my_receive (&buf)) <= 0)
	{
		printf ("could not get the name of the file\n");
		return 1;
	}
    printf ("File name has been received!\n");
    

	// open file
	if ((fp = fopen (buf.data, "wb")) == NULL)
	{
		printf ("error fopen\n");
		return 1;
	}

    
	printf ("Receiving file %s ... \n", buf.data);
    // my_receive() function ensures the received data chunks are not corrupted
	while ((n = my_receive (&buf)) > 0)
	{
		printf ("writing to file... n = %d\n", n);
        // STUDENT WORK
	}

	close (sock);
	fclose (fp);

	return 0;
}



// my_receive() function ensures the received data chunks are not corrupted
int my_receive (PACKET *recv_pck)
{
    int cs_in;
	int cs_calc;
	int	d;
	int r;
	int nbytes;

	HEADER			ack_packet;
	struct sockaddr	ret_addr;
	socklen_t		addr_size = sizeof (ret_addr);


	while (1)
	{
        // ssize_t recvfrom(int socket, void *restrict buffer, size_t length,
        //          int flags, struct sockaddr *restrict address, socklen_t *restrict address_len);
        // buffer: Points to the buffer where the message should be stored.
        // address: A null pointer, or points to a sockaddr structure in which the sending address is to be stored.
        // The length and format of the address depend on the address family of the socket.
        // address_len: Specifies the length of the sockaddr structure pointed to by the address argument.
		if ((nbytes = recvfrom (sock, recv_pck, sizeof(PACKET), 0, &ret_addr, &addr_size)) < 0)
			return -1;
	
        printf ("Received a UDP packet!\n");
        
		cs_in = recv_pck->header.checksum;
		recv_pck->header.checksum = 0;
        
        // recalculate checksum
        // STUDENT WORK
        
        // check if checksum matches, and the sequence number is correct too
        if (cs_in == cs_calc  &&  recv_pck->header.seq_ack == state)
		{
            printf ("Checksum passed! Sequence number matched!\n");

			// good packet
            // STUDENT WORK
            
            
            // simulating erroneous channel...corruption and loss
            // STUDENT WORK
            
			// now we are expecting the next packet
            // STUDENT WORK
            
			return recv_pck->header.len;
		}
		else
		{
            printf ("Checksum/sequence number check failed!\n");

			// bad packet
            // STUDENT WORK
            
            printf ("Resending ack for sequence number: %d...\n", ack_packet.seq_ack );

            
            // simulating erroneous channel...corruption and loss
            // STUDENT WORK

		}

	}

	return -1;
}



int calc_checksum (char *buf, int tbytes)
{
    int     i;
    char    cs = 0;
    char    *p;

    // STUDENT WORK
    
    return (int)cs;
}

