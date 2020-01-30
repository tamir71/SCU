/* # Name: Tamir Enkhjargal
 * # Date: 1/22/20 Wednesdays 2:15-5p
 * # Title: Lab3 - Part 2
 * # Description: Seeing the code outline on how to use the upstream and downstream of a pipe
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

   // Created fds up/down stream and make the pipe between them
   pipe(fds);
   
   if (fork()==0){
       printf("\nWriter on the upstream end of the pipe -> %d arguments \n",argc);
       close(fds[0]);
       
       // The commandline arguments are written to the upstream buffer
       for(i=0;i<argc;i++){
           write(fds[1],argv[i],strlen(argv[i]));
       }
       exit(0);
   }
   else if(fork()==0){
       printf("\nReader on the downstream end of the pipe \n");
       close(fds[1]);
       
       // The upstream buffer is read into buff and written to `1` (screen)
       while((count=read(fds[0],buff,60))>0){
           for(i=0;i<count;i++){
               write(1,buff+i,1);
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
