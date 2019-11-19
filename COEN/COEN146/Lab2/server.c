//
//  Behnam Dezfouli
//  CSEN, Santa Clara University
//

// This program implements a server that accepts connection from a client and copies the received bytes to a file
//
// The input arguments are as follows:
// argv[1]: Sever's port number



#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>


int main (int argc, char *argv[])
{
    char    message[10] = "received!";  // message to be sent to the client when the destination file name is received
    int     net_bytes_read;             // number of bytes received over socket
    int     socket_fd = 0;              // socket descriptor
    int     connection_fd = 0;          // new connection descriptor
    struct  sockaddr_in serv_addr;      // Address format structure
    char    net_buff[1024];             // buffer to hold characters read from socket
    FILE    *dest_file;                 // pointer to the file that will include the received bytes over socket
    int     i;
    int     readIn = 0;     
    char    buffer[10];

    if (argc < 2) // Note: the name of the program is counted as an argument
    {
        printf ("Port number not specified!\n");
        return 1;
    }
    
    /*struct sockaddr_in {
        short           sin_family;
        unsigned short  sin_port;
        struct in_addr  sin_addr;
        char            sin_zero[8];
    };*/

    serv_addr.sin_family = AF_INET;                 // Set IP version
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // Allow binding to all interfaces
    serv_addr.sin_port = htonl(atoi(argv[1]));      // Take parameter 1 (port number) and set
    
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);    // Create our socket pointer
    bind(socket_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(socket_fd, 10);
    
    connection_fd = accept(socket_fd, (struct sockaddr*)NULL, NULL);
    read(connection_fd, net_buff, sizeof(net_buff));
    
    for(i = 0; i < sizeof(net_buff); i++) {
        if(net_buff[i] == '\0') {
            strncpy(net_buff, net_buff, i);
            break;
        }
    }

    dest_file = fopen(net_buff, "wb");
    printf("%s", message);

    while((readIn = read(connection_fd, buffer, sizeof(buffer))) > 0) {
        if(readIn < sizeof(buffer)) {
            fwrite(buffer, 10, readIn, dest_file);
        }
    }
    
    fclose(dest_file);
    close(connection_fd);
       
}

