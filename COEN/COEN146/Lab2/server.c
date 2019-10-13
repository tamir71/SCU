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
    int     net_bytes_read;             // numer of bytes received over socket
    int     socket_fd = 0;              // socket descriptor
    int     connection_fd = 0;          // new connection descriptor
    struct  sockaddr_in serv_addr;      // Address format structure
    char    net_buff[1024];             // buffer to hold characters read from socket
    FILE    *dest_file;                 // pointer to the file that will include the received bytes over socket
    int i;
    char filename[256];

    if (argc < 2) // Note: the name of the program is counted as an argument
    {
        printf ("Port number not specified!\n");
        return 1;
    }

	serv_addr.sin_family = AF_INET; //IPv4
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); //Bind to all interfaces. Use host to network.
	serv_addr.sin_port = htons(atoi(argv[1]));	//Assign the port number

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);	//create socket
	bind(socket_fd,(const struct sockaddr*)&serv_addr, sizeof(serv_addr));	//bind a socket
	listen(socket_fd, 10);	//listen to the socket
    
	
	connection_fd = accept(socket_fd,(struct sockaddr*)NULL, NULL);	//create connection

	read(connection_fd, filename, sizeof(filename));

	printf("%s\n", filename);
	dest_file = fopen(filename, "wb");
	printf("%s\n", message);

	while((i = read(connection_fd, net_buff, sizeof(net_buff))) >0){	//copy file
		printf("%s\n", net_buff);
		fwrite(net_buff, sizeof(char), i, dest_file);
	}

	close(connection_fd);
	fclose(dest_file);	
	
	return 0;
	//accept(socket_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

      
    
}

