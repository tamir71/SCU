// SCU COEN 146
//
// This program implements the client side of stop & wait protocol
// the client transfers a file to the server
//
//
// For the stop and wait protocolL, the assumptions are:
//      -- packet corruption, and packet loss


#include	"tfv1.h"

// global variables
int state = 0; // only two states: 0 and 1
int sock;
struct sockaddr_in serverAddr;
socklen_t addr_size;


// list of functions
int main (int, char *[]);

// to reliably send a chunk of data
void my_send (char *, int);

// part of the my_send() function
void recv_ack (PACKET *, int);

// computes checksum using XOR of bytes
int calc_checksum (char *, int);



int main (int argc, char *argv[])
{
    char	buff[SIZE];
    FILE	*fp; // file to be sent to the server
    int		r;
    
    if (argc != 5)
    {
        printf ("usage:usage: ./client port IP source_file dest_file\n");
        return 1;
    }
    
    
    // configure address
    // STUDENT WORK
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(atoi(argv[1]));
    serverAddr.sin_family = PF_INET;
    
    
    // create UDP socket
    if ((sock = socket (PF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf ("socket error\n");
        return 1;
    }
    printf ("UDP socket has been created!\n");
    
    if ((fp = fopen (argv[3], "rb")) == NULL)
    {
        printf ("fopen error\n");
        return 1;
    }
    printf ("Source file opened successfully!\n");

    
    printf ("Sending file name...");
    // STUDENT WORK
    if(connect(sock, &serverAddr, sizeof(serverAddr)) < 0) { 
        printf("\n Error : Connect Failed \n"); 
        exit(0); 
    }

    my_send(argv[4],strlen(argv[4]));
    printf("Sent File name");
    
    printf ("Now sending source file contents...");
    // STUDENT WORK
    while((r = fread(&buff,sizeof(char),SIZE,fp))>0) {
        my_send(buff,r);
    }
    printf ("Done!\n");
    
    
    // After transmitting the file, a packet with no data (len = 0) is sent to
    // notify the receiver that the file transfer has completed
    printf ("Informing the server about the completion of file transmission...\n");
    
    // STUDENT WORK
    my_send(buff,0);        // Don't really care what to send, as long as len = 0
    printf ("Done!\n");
    
    fclose (fp);
    close (sock);
    
    return 0;
    
}


//***********************
// sends data (of size nbbytes) unreliably to the sender
// **********************
void my_send (char *data, int nbytes)
{
    PACKET	buf;
    int		r;
    int     cs;

    // STUDENT WORK    
    //default checksum value is 0
    buf.header.checksum = 0;    


    buf.header.len = nbytes;    
    buf.header.seq_ack = state;
    printf("sequence number: %d\n",buf.header.seq_ack);

    strcat(data,"\0");
    printf("data: %s\n",data);
    strcpy(buf.data,data);
    
    // simulating erroneous channel... corruption and loss
    // the probability of correct checksum is 80%
    r = rand () % 10;
    if (r <= 8)
        buf.header.checksum = calc_checksum (&buf, sizeof(HEADER)+buf.header.len);
    else
        printf ("\nPacket got corrupted on the way!\n");
    
    cs = state;
    
    printf("\tChecksum: %d\n", buf.header.checksum);
    printf("\tData: %s\n", buf.data);

    // the probability of no packet loss is 80%
    // STUDENT WORK
    r = rand() % 10;
    if(r<=8) 
        sendto(sock, &buf, sizeof(HEADER)+nbytes, 0, NULL, sizeof(serverAddr));
    else 
        printf("\nPacket got lost along the way!\n");

    // wait for ack
    // STUDENT WORK
    recv_ack(&buf, nbytes);

    // if ack not correctly received, retransmit data    
    if(cs == state)
        my_send(data, nbytes);
    return;
}



//***********************
// wait for ack
// **********************
void recv_ack (PACKET *buf, int nbytes)
{
    HEADER	receive_buf;
    int		cs;
    int		r;
    struct timeval tv;
    int		rv;
    int		counter = 0;
    
    // The fd_set data type represents file descriptor sets for the select function
    // It is actually a bit array
    // (set of socket descriptors)
    fd_set readfds;
    
    fcntl(sock, F_SETFL, O_NONBLOCK);
    
    while (1)
    {
        while (1)
        {
            FD_ZERO (&readfds); // Clear an fd_set
            
            // void FD_SET (int filedes, fd_set *set)
            // This macro adds filedes to the file descriptor set set.
            FD_SET (sock, &readfds);
            
            tv.tv_sec = 1;
            tv.tv_usec = 0;
            
            
            // int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
            // maxfd: maximum number of descriptor ready.
            // timeout: How long to wait for select to return.
            //The select function blocks , till an activity occurs
            
            // On success, select() and pselect() return the number of file
            // descriptors contained in the three returned descriptor sets (that is,
            // the total number of bits that are set in readfds, writefds,
            // exceptfds) which may be zero if the timeout expires before anything
            // interesting happens
            
            // in the following we only pass readfds because we are interested in reading only
            

            rv = select (sock + 1, &readfds, NULL, NULL, &tv);
            
            
            // return value is 1 when there is a bit set in readfds
            // so there is data to be read
            if (rv == 1)
            {
                // STUDENT WORK
                counter = 0;
                break;
            }
            
            // this means select() returned due to timeout event
            else if (rv == 0)
            {
                printf ("timeout\n");
                counter ++; 

                // STUDENT WORK
                if(counter >= 3)
                    return;
                continue;
            }
        }
        
        
        
        // we break the previous while(1) loop when there is data to be read (ack received)
        
        recvfrom (sock, &receive_buf, sizeof(HEADER), 0, NULL, NULL);
        
        cs = receive_buf.checksum;
        receive_buf.checksum = 0;
        
        
        // recalculate checksum of the received ack packet
        // STUDENT WORK
        receive_buf.checksum = calc_checksum (&receive_buf, sizeof(HEADER));
        
        printf("\tChecksum: %d\n", receive_buf.checksum);
        printf("\tSequence: %d\n", receive_buf.seq_ack);
        printf("\tcurrent state: %d\n",state);
        
        // a bad ack has been received
        // STUDENT WORK
        if(cs != receive_buf.checksum || state != receive_buf.seq_ack) {
            printf("\nReceived bad packet\n");
            return;
        }
        
        // resend packet - put into sending data
        // simulating erroneous channel...corruption and loss
        // STUDENT WORK
        // good packet:
        if(cs == receive_buf.checksum && state == receive_buf.seq_ack)
            state = !state;
        return;
    }
}



//***********************
// calculate checksum by using XOR
// **********************
int calc_checksum (char *buf, int tbytes)
{
    int		i;
    char	cs = 0;
    char 	*p;
    
    // STUDENT WORK
    for(i = 0; i < tbytes; i++) {
        cs ^= buf[i];
    }
    
    return cs;
}
