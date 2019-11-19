
# Behnam Dezfouli
# CSEN, Santa Clara University

# This program implements a simple web server that serves html and jpg files

# Input arguments:
# argv[1]: Sever's port number


from socket import *  # Import socket module
import sys            # To terminate the program


if __name__ == "__main__":

    # check if port number is provided
    if len(sys.argv) != 2:
        print 'Usage: python %s <PortNumber>' % (sys.argv[0])
        sys.exit()
    
    serverSocket = socket(AF_INET, SOCK_STREAM)                 # Accept IPv4 connections
    serverSocket.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)        # To avoid 'address already in use' error
    serverPort = int(sys.argv[1])                               # Set port number from user input
    serverSocket.bind(("", serverPort))                         # Bind to (any) IP, and set Port #
    serverSocket.listen(1)                                      # Listen to any connnections


    # Server should be up and running and listening to the incoming connections
    while True:
        print('The server is ready to respond to incoming requests...')
        connectionSocket, addr = serverSocket.accept()          # Accept connection once taken
        message = connectionSocket.recv(1024)                   # Put request-message into buffer
        
        fileName = message.split(' ')[1][1:]                    # file name: get name of file without slash
        
        if (fileName == 'favicon.ico'):                         # if we don't give a filename, it goes to favicon.ico, so we change file name to index.html
            fileName = 'index.html'
        try:
            file_extension = fileName.split('.')[1]             # Get file extension
        except IndexError:
            file_extension = 'html'                             # If we don't find extension, give it html
        try:
            if (file_extension == 'jpg'):
                response_headers = 'Content-Type: image/jpeg; encoding=utf8\n'
            else:
                response_headers = 'Content-Type: text/html; encoding=utf8\n'

            header = 'HTTP/1.1 200 OK\nServer: SCU COEN Server\n'
            header = header + response_headers                  # Add our header and response header
            header = header + 'Content-Length: '                # Add content length
            f = open(fileName, 'rb')                            # try opening file, if error go to IOError
            outputdata = f.read()                               # read from our file
            contentlen = len(outputdata)                        # content length (int) of file size
            header = header + str(contentlen) + '\n\n'          # add file size to header

            connectionSocket.sendall(header)                    # send header
            connectionSocket.sendall(outputdata)                # send file data
            f.close()                                           # close file object
            connectionSocket.close()                            # close connection

        #Raised when an I/O operation (such as a print statement, the built-in open() function or a method of a file object) fails for an I/O-related reason, e.g., "file not found" or "disk full"
        except IOError:
            print 'Error! Something went wrong\n'               # if something went wrong
            f = open('error.html', 'rb')                        # we open our error.html (404)
            outputdata = f.read()                               # read our error.html file
            contentlen = len(outputdata)        
            header = header + str(contentlen) + '\n\n'          # finish up our header
            connectionSocket.sendall(header)                    # send our header
            connectionSocket.sendall(outputdata)                # send error.html data
            f.close()                                           # close file object
            connectionSocket.close()                            # close connection
