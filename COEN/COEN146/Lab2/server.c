//
//  Behnam Dezfouli
//  CSEN, Santa Clara University
//

// This program implements a server that accepts connection from a client and copies the received bytes to a file
//
// The input arguments are as follows:
// argv[1]: Server's port number


#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>


int main (int argc, char *argv[]) {
    char    message[10] = "received!";                                          // Message upon receiving file name
    int     net_bytes_read;
    int     socket_fd = 0;             
    int     connection_fd = 0;         
    struct  sockaddr_in serv_addr;     
    char    net_buff[1024];
    FILE    *dest_file;                                                         // File pointer to write to destination file
    int i;
    char filename[256];                                                         // File name buffer

    if (argc < 2) {                                                             // Name of executable file and port number
        printf ("Port number not specified!\n");
        return 1;
    }

    serv_addr.sin_family = AF_INET;                                             // IPv4
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);                              // Bind to all interfaces. Use host to network.
    serv_addr.sin_port = htons(atoi(argv[1]));                                  // Set port number from argument

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);                                // Create socket
    bind(socket_fd,(const struct sockaddr*)&serv_addr, sizeof(serv_addr));	// Bind socket
    listen(socket_fd, 10);	                                                // Listen to open receive

    
    connection_fd = accept(socket_fd,(struct sockaddr*)NULL, NULL);	        // Accept and open connection in socket

    read(connection_fd, filename, sizeof(filename));                            // Read in the name of the source file

    dest_file = fopen(filename, "wb");                                          // Open destination file for writing from source
    printf("%s\n", message);                                                    // Print we have received source file name

    while((i = read(connection_fd, net_buff, sizeof(net_buff))) >0) {           // Loop to copy bits from source file contents
            fwrite(net_buff, sizeof(char), i, dest_file);                       // Writing to our destination file from buffer
    }

    close(connection_fd);                                                       // Close our connection
    fclose(dest_file);	                                                        // Close the file pointer
    
    return 0;

}
