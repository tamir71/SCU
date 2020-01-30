/* # Name: Tamir Enkhjargal
 * # Date: 1/22/20 Wednesdays 2:15-5p
 * # Title: Lab3 - Part 1
 * # Description: Seeing the code outline on how to pipe two commands using two child processes
 *
 */

/**************************
*	pipe()
**************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <sys/wait.h> 
//main
int main() {
 	
        // Create our pipe streams
        int fds[2];
        // and make the pipe between the two
 	pipe(fds);
	/*child 1 duplicates downstream into stdin */
	if (fork() == 0) {
		dup2(fds[0], 0);            // fds[0] points to downstream
		close(fds[1]);
		execlp("more", "more", 0);  // the command to run on right side of pipe
	}
	/*child 2 duplicates upstream into stdout */
	else if (fork() == 0) {
		dup2(fds[1], 1);            // fds[1] points to upstream
		close(fds[0]);
		execlp("ls", "ls", 0);      // the command to run on left side of pipe
	}
	else {  /*parent closes both ends and wait for children*/
		close(fds[0]);
		close(fds[1]);
		wait(0);
		wait(0); 
	}
} 
