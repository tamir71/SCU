/**********************************************
*	Assignment 2: Run and comment in details  *
*       Winter 2019				  *
***********************************************/

// Including necessary libraries
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <signal.h>

int id;

// Our Mesg struct contains a message
struct Mesg{
    char Message[40];
    int count;
    char token[10][20];
    char sorttoken[10][20];
};

#define KEY       ((key_t)(713))
#define SEGSIZE   sizeof(struct Mesg)

// Cleanup function takes in a signal (ctrl-c or ctrl-\\)
void cleanup(int sigtype){
   shmdt(0);
   printf("\n Terminating\n");
   execlp("ipcrm","ipcrm","-M","713",(char*)(0));   // This function ipcrm -M removes the shared memory segment
   printf("ERROR!");
   exit(0);
}

int main(){
    
    int i,j;
    int count;
    char *token;
    char tmp[20];
    struct Mesg *msg;
    struct shmid_ds shmbuf;
    
    // If we get SIGINT or SIGQUIT signal, then run cleanup
    signal(SIGINT,cleanup);
    signal(SIGQUIT,cleanup);
    
    // shmget with IPC_CREAT creates a shared memory segment
    id=shmget(KEY,SEGSIZE,IPC_CREAT|0666);
    
    // Checking if id returns a positive number (successfully created)
    if (id < 0) {
        perror("shmget failed 1\n");
        exit(1);
    }
    
    // Attach a message to the shared memory segment
    msg=(struct Mesg*) shmat(id,0,0);

    // If we were not able to attach (returns negative), shmat failed
    if (msg <= (struct Mesg *)(0)) {
        perror("shmat failed 2\n");
        exit(1);
    }

    // Start our message counter at 0
    msg->count=0;
    printf("Parent: Enter a Message: \n");

    // count reads from message buffer to see how many bytes (chars) in buffer
    count = read(0,msg->Message,40);
    if (count <= 0) {               // If there was no message (char count = 0 or less)
        printf("read failed or no text entered!\n");
        exit(0);
    }
    msg->Message[count-1]='\0';     // End the message buffer with EOL pointer

    // Our parent will now print what is in the message buffer and print pid
    printf("Parent pid = %d, Message readed:'%s'\n",getpid(),msg->Message);
    printf("Just before forking, pid = %d\n",getpid());

    // fork, creating first child
    if (fork() == 0) {
        printf("fork 1\n");         // This is the first child
        msg->count=1;
        for(i = 0; i < count; i++)
            if(msg->Message[i]==' ')
        msg->count++;
        printf("token count = %d\n",msg->count);
        exit(0);
    }
    else
        if (fork() == 0) {          // fork, creating second child (child-child)
            sleep(1);
            printf("fork 2\n");     
            i=0;
            token=strtok(msg->Message," ");     // Split the message into tokens delimited by spaces
            
            while(token!=NULL) {                // Loop through our tokens buffer
                strcpy(msg->token[i],token);    // copy token buffer into mesg struct
                i++;
                token=strtok(NULL," ");
            }

            printf("Tokens: \n");
            for(i = 0; i < msg->count; i++) {   // For the amount of words we have
                printf("%s\n",msg->token[i]);   // Print our mesg->token array we filled in above while loop
            }
            printf("Tokens end\n");
            exit(0);
        }
        else
            if (fork() == 0) {                  // fork, creating third child (child-child-child)
                sleep(3);
                printf("fork 3\n");
                for(i = 0; i < msg->count; i++) {   // For each char
                    strcpy(tmp,msg->token[i]);      // Copy our existing token array into temp
                    strcpy(msg->sorttoken[i],tmp);  // Copy tmp into our sorttoken array
                }

                // This nested for loop will result in swapping (selection sort)
                // of our words in our sorttoken array
                for(i = msg->count-1; i >= 0;i--) {
                    for(j = 0; j < i; j++) {
                        if (strcmp(msg->sorttoken[j],msg->sorttoken[j+1]) > 0) {
                            strcpy(tmp,msg->sorttoken[j]);
                            strcpy(msg->sorttoken[j],msg->sorttoken[j+1]);
                            strcpy(msg->sorttoken[j+1],tmp);
                        }
                    }
                }

                // After sorting the words this will print the sorted tokens one by one from sorttoken array
                printf("Sorted tokens : \n");
                for(i = 0; i < msg->count; i++) {
                    printf("%s\n",msg->sorttoken[i]);
                }
                printf("Sorted tokens end\n");
            exit(0);
            }
        
        // We have three children, and we will wait for each one to process completely
        for(i = 0; i < 3; i++)
            wait(0);
    // After we are done waiting for each child to run their code, we can tell user to exit
    printf("Press Ctrl-C (or) Ctrl-\\ to clean up the memory and exit.\n");
    
    // A pausing mechanism so we don't hit return 0 automatically
    for(;;);
    
    return 0; 
}

