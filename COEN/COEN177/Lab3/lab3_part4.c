/* # Name: Tamir Enkhjargal
 * # Date: 1/22/20 Wednesdays 2:15-5p
 * # Title: Lab3 - Part 4
 * # Description: Writing a C program that implements the shell command `cat /etc/passwd | grep root`
 * #    and deal with execlp with multiple arguments
 *
 */

/**************************
*   Lab3 - pipe()
**************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/wait.h> 

// main
int main(int argc,char *argv[]){
   int  fds[2];
   pipe(fds);
   
   // Using the same code foundation from Part 1
   if (fork()==0){
       dup2(fds[0], 0);
       close(fds[1]);
       // We need to include /bin/grep as the `file source`, which points to the code we want to run
       // and then we call grep and root as two separate parameters
       execlp("/bin/grep", "grep", "root", 0);
   }
   else if(fork()==0){
       dup2(fds[1], 1);
       // Same as above, include /bin/cat as file source, and code inputted as separate parameters `cat` and `/etc/passwd`
       close(fds[0]);
       execlp("/bin/cat", "cat", "/etc/passwd", 0);
    }
   else{     
      close(fds[0]);
      close(fds[1]);
      wait(0);
      wait(0);
   }
return 0;
}
