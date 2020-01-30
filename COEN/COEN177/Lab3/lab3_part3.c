/* # Name: Tamir Enkhjargal
 * # Date: 1/22/20 Wednesdays 2:15-5p
 * # Title: Lab3 - Part 3
 * # Description: Adjusted Part 2 code to be able to send output of ls into upstream buffer and read from downstream buffer
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
   char buff[60];
   int count;
   int i;
   pipe(fds);
   
   if (fork()==0){
       printf("\nWriter on the upstream end of the pipe -> %d arguments \n",argc);
       close(fds[0]);

       // Redirect using dup2 for upstream, ls output put into fds[1]
       dup2(fds[1], 1);
       // Run command ls in upstream
       execlp("ls", "ls", 0);
       
       /*for(i=0;i<argc;i++){                           // Legacy code
           write(fds[1],argv[i],strlen(argv[i]));       // from 
       }*/                                              // Part 2
       exit(0);
   }
   else if(fork()==0){
       printf("\nReader on the downstream end of the pipe \n");
       close(fds[1]);
       
       // Redirect using dup2 for downstream
       dup2(fds[0], 0);
       // Read from fds[1] upstream buffer
       while((count=read(fds[0],buff,60))>0){
           for(i=0;i<count;i++){
               write(1,buff+i,1);                       // and write to screen from buffer
               write(1," ",1);
           }
           printf("\n");
       }
       exit(0);
    }
   else{     
      close(fds[0]);
      close(fds[1]);
      wait(0);
      wait(0);
   }
return 0;
}
