//
// # Name: Tamir Enkhjargal
// # Date: February 26, 2020
// # Title: Simulated CPU Scheduling application
// # Description: Creating an user friendly simulation of CPU scheduling
//

/* Scheduling Simulation*/

#include <stdio.h>
#include <stdlib.h>

/* Process Data Structure */
struct process {
    int pid;                /* Process ID */
    int burst;              /* CPU Burst Time */
    int priority;           /* Priority */
    int working;            /* Working time, for round-robin scheduling */
    int waiting;            /* Waiting time, for round-robin scheduling */
    struct process *next;
};

/* Function Prototype Declarations */
struct process *init_process (int pid, int burst, int priority);
void fcfs (struct process *proc);
void listprocs (struct process *proc);
void priority (struct process *proc);
void rr (struct process *proc, int quantum);
void sjf (struct process *proc);
 
/* Main Program Segment */
int main (void) {
    /* Initialize process list */
    
    struct process *plist, *ptmp;
    int int1, int2, int3;
    printf("Please add your five processes one at a time\n");
    printf("Process 1: [ProcessID Priority Burst]\n");
    scanf("%d %d %d", &int1, &int2, &int3);
    plist       = init_process(int1, int3, int2);
    printf("Process 2: [ProcessID Priority Burst]\n");
    scanf("%d %d %d", &int1, &int2, &int3);
    plist->next = init_process(int1, int3, int2); 
    ptmp = plist->next;
    printf("Process 3: [ProcessID Priority Burst]\n");
    scanf("%d %d %d", &int1, &int2, &int3);
    ptmp->next  = init_process(int1, int3, int2); 
    ptmp = ptmp->next;
    printf("Process 4: [ProcessID Priority Burst]\n");
    scanf("%d %d %d", &int1, &int2, &int3);
    ptmp->next  = init_process(int1, int3, int2); 
    ptmp = ptmp->next;
    printf("Process 5: [ProcessID Priority Burst]\n");
    scanf("%d %d %d", &int1, &int2, &int3);
    ptmp->next  = init_process(int1, int3, int2);

    /* Perform simulations */
    listprocs(plist);
    printf("What scheduling method do you want to use?\n");
    printf("First come first serve (1), Shortest Job First (2), Priority (3) or Round Robin (4)?\n");
    scanf("%d", &int1);
    switch(int1) {
        case 1:
            fcfs(plist);
            break;
        case 2:
            sjf(plist);
            break;
        case 3:
            priority(plist);
            break;
        case 4:
            printf("Please indicate what quanta you wish to use:\n");
            scanf("%d", &int2);
            rr(plist, int2);
            break;
        default:
            printf("You didn't input a selection!\n");
    }

    /* Terminate cleanly */
    while (plist != NULL) {
        ptmp = plist;
        plist = plist->next;
        free(ptmp);
    };
    return(0);
};


/* Process list entry initialization routine */
struct process *init_process (int pid, int burst, int priority) {
    struct process *proc;
    proc = malloc(sizeof(struct process));
    if (proc == NULL) {
        printf("Fatal error: memory allocation failure.\nTerminating.\n");
        exit(1);
    };
    proc->pid = pid;
    proc->burst = burst;
    proc->priority = priority;
    proc->working = 0;
    proc->waiting = 0;
    proc->next = NULL;
    return(proc);
};


/* First-Come-First-Served scheduling simulation */
void fcfs (struct process *proc) {
    int time = 0, start, end;
    struct process *tmp = proc;

    printf("BEGIN:\tFirst-Come-First-Served scheduling simulation\n");

    while (tmp != NULL) {
        start = time;
        time += tmp->burst;
        end = time;
        printf("Process: %d\tEnd Time: %d\tWaiting: %d\tTurnaround: %d\n", tmp->pid, time, start, end);
        tmp = tmp->next;
    };

    printf("END:\tFirst-Come-First-served scheduling simulation\n\n");
};


/* Process listing */
void listprocs (struct process *proc) {
    struct process *tmp = proc;

    printf("BEGIN:\tProcess Listing\n");

    while (tmp != NULL) {
        printf("PID: %d\t\tPriority: %d\tBurst: %d\n", tmp->pid, tmp->priority, tmp->burst);
        tmp = tmp->next;
    };

    printf("END:\tProcess Listing\n\n");
};


/* Priority scheduling simulation
 * Note: lower priority value gets a higher priority
 */
void priority (struct process *proc) {
    int time, start, end, highest;
    struct process *copy, *tmpsrc, *tmp, *beforehighest;

    printf("BEGIN:\tPriority scheduling simulation\n");

    /* Duplicate process list */
    tmpsrc = proc;
    copy = tmp = NULL;
    while (tmpsrc != NULL) {
        if (copy == NULL) {
            copy = init_process(tmpsrc->pid, tmpsrc->burst, tmpsrc->priority);
            tmp = copy;
        } else {
            tmp->next = init_process(tmpsrc->pid, tmpsrc->burst, tmpsrc->priority);
            tmp = tmp->next;
        };
        tmpsrc = tmpsrc->next;
    };

    /* Main routine */
    time = 0;
    while (copy != NULL) {
        /* Find the next job */
        beforehighest = NULL;
        highest = copy->priority;
        tmp = copy->next;
        tmpsrc = copy;
        while (tmp != NULL) {
            if (tmp->priority < highest) {
                highest = tmp->priority;
                beforehighest = tmpsrc;
            };
            tmpsrc = tmp;
            tmp = tmp->next;
        };

        /* Process job and remove from copy of process list */
        if (beforehighest == NULL) {
            /* Handle first job is highest priority case */
            start = time;
            time += copy->burst;
            end = time;
            printf("Process: %d\tEnd Time: %d\tWaiting: %d\tTurnaround: %d\n", copy->pid, time, start, end);
            tmpsrc = copy->next;
            free(copy);
            copy = tmpsrc;
        } else {
            /* Handle first job is not highest priority case */
            tmp = beforehighest->next;
            start = time;
            time += tmp->burst;
            end = time;
            printf("Process: %d\tEnd Time: %d\tWaiting: %d\tTurnaround: %d\n", tmp->pid, time, start, end);
            beforehighest->next = tmp->next;
            free(tmp);
        };
    };

    printf("END:\tPriority scheduling simulation\n\n");
};


/* Round-Robin scheduling simulation */
void rr (struct process *proc, int quantum) {
    int jobsremain, passes;
    struct process *copy, *tmpsrc, *tmp, *slot;

    printf("BEGIN:\tRound-Robin scheduling simulation (Quantum: %d)\n", quantum);
    /* Duplicate process list */
    tmpsrc = proc;
    copy = tmp = NULL;
    while (tmpsrc != NULL) {
        if (copy == NULL) {
            copy = init_process(tmpsrc->pid, tmpsrc->burst, tmpsrc->priority);
            tmp = copy;
        } else {
            tmp->next = init_process(tmpsrc->pid, tmpsrc->burst, tmpsrc->priority);
            tmp = tmp->next;
        };
        tmpsrc = tmpsrc->next;
    };

    /* Main routine */
    jobsremain = 1;
    slot = NULL;
    while (jobsremain) {
        jobsremain = 0;

        /* Pick next working slot */
        if (slot == NULL) {
            slot = copy;
            jobsremain = 1;
        } else {
            passes = 0;
            do {
                if (slot->next == NULL) {
                    passes++;
                    slot = copy;
                } else {
                    slot = slot->next;
                };
            } while (passes <= 2 && slot->burst == slot->working);
            if (passes <= 2) {
                jobsremain = 1;
            };
        };

        /* Perform a cycle */
        tmp = copy;
        while (tmp != NULL) {
            if (tmp->burst > tmp->working) {
                if (tmp == slot) {
                    tmp->working += quantum;
                } else {
                    tmp->waiting += quantum;
                };
            };
            tmp = tmp->next;
        };
    };

    /* Display statistics and clean up copy */
    tmp = copy;
    while (tmp != NULL) {
        printf("Process: %d\tWorking: %d\tWaiting: %d\tTurnaround: %d\n", tmp->pid, tmp->working, tmp->waiting, tmp->working + tmp->waiting);
        tmpsrc = tmp;
        tmp = tmp->next;
        free(tmpsrc);
    };

    printf("END:\tRR scheduling simulation\n\n");
};


/* Shortest Job First scheduling simulation */
void sjf (struct process *proc) {
    int time, start, end, shortest;
    struct process *copy, *tmpsrc, *tmp, *beforeshortest;

    printf("BEGIN:\tShortest Job First scheduling simulation\n");

    /* Duplicate process list */
    tmpsrc = proc;
    copy = tmp = NULL;
    while (tmpsrc != NULL) {
        if (copy == NULL) {
            copy = init_process(tmpsrc->pid, tmpsrc->burst, tmpsrc->priority);
            tmp = copy;
        } else {
            tmp->next = init_process(tmpsrc->pid, tmpsrc->burst, tmpsrc->priority);
            tmp = tmp->next;
        };
        tmpsrc = tmpsrc->next;
    };

    /* Main routine */
    time = 0;
    while (copy != NULL) {
        /* Find the next job */
        beforeshortest = NULL;
        shortest = copy->burst;
        tmp = copy->next;
        tmpsrc = copy;
        while (tmp != NULL) {
            if (tmp->burst < shortest) {
                shortest = tmp->burst;
                beforeshortest = tmpsrc;
            };
            tmpsrc = tmp;
            tmp = tmp->next;
        };

        /* Process job and remove from copy of process list */
        if (beforeshortest == NULL) {
            /* Handle first job is shortest case */
            start = time;
            time += copy->burst;
            end = time;
            printf("Process: %d\tEnd Time: %d\tWaiting: %d\tTurnaround: %d\n", copy->pid, time, start, end);
            tmpsrc = copy;
            copy = copy->next;
            free(tmpsrc);
        } else {
            /* Handle first job is not shortest case */
            tmp = beforeshortest->next;
            start = time;
            time += tmp->burst;
            end = time;
            printf("Process: %d\tEnd Time: %d\tWaiting: %d\tTurnaround: %d\n", tmp->pid, time, start, end);
            beforeshortest->next = tmp->next;
            free(tmp);
        };
    };

    printf("END:\tShortest Job First scheduling simulation\n\n");
};
