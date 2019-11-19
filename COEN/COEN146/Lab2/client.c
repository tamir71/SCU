//
//  Behnam Dezfouli
//  CSEN, Santa Clara University
//

// This program implements a client that connects to a server and transfers the bytes read from a file over the established connection
//
// The input arguments are as follows:
// argv[1]: Server's IP address
// argv[2]: Server's port number
// argv[3]: Source file
// argv[4]: Destination file at the server side which includes a copy of the source file



#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#define    SIZE 10

int main (int argc, char *argv[]) {
    int        sockfd = 0;                                          // Socket descriptor
    char       net_buff[SIZE];                                      // To hold the bytes read from socket
    char       file_buff[SIZE];                                     // To hold the bytes read from source file
    struct     sockaddr_in serv_addr;                               // Server address structure
    int        net_bytes_read;                                      // Number of bytes received over socket
    FILE       *source_file;                                        // Pointer to the source file
    int        buffer = 0;

    if (argc < 5) {
        printf ("Usage: ./%s <server ip address> <server port number> <source file>  <destination file>\n", argv[0]);
        return 1;
    }
        
    // Make sure intial values are zero
    memset (net_buff, '0', sizeof (net_buff));
    memset (file_buff, '0', sizeof (file_buff));
    memset (&serv_addr, '0', sizeof (serv_addr));
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    serv_addr.sin_family = AF_INET;                                 // Set IP version use to IPv4   
    serv_addr.sin_port = htons(atoi(argv[2]));                      // Set port number from user input
 
    inet_pton(AF_INET, argv[1], &serv_addr.sin_addr);               // Set server IP address from input
    
    source_file = fopen(argv[3], "rb");                             // Open file pointer to reading

    connect(sockfd,(struct sockaddr *)&serv_addr, sizeof(serv_addr));   // Connect to destination server, which should be listening
    strncpy(file_buff, argv[4], strlen(argv[4]));                   // Copy name of source file to a file buffer
    write(sockfd, file_buff, strlen(argv[4]));                      // Write to the server the name of the source file

    while(fread(net_buff, 10, 1, source_file)) {                    // While loop to read 10 bits of source file contents
        write(sockfd, net_buff, 10);                                // and write to server 10 bits at a time
    }

    fclose(source_file);                                            // Once we are done we close file pointer
    close(sockfd);                                                  // Closing socket connection

    return 0;
}

