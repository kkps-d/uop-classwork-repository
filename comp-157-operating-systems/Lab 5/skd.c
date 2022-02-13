#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "structs.h"

Queue queue_create();
void queue_push(Process *val, Queue *queue);
Process *find_process(char *by, int val, Process *processes, int n_process);
void sort_queue_arrival(Queue *queue);
int process_execute(Process *process);
void fcfs(Process *processes, int n_process);
void sjf(Process *processes, int n_process);
void rr(Process *processes, int n_process, int quantum);
char *str_tolower(char *str);

int main(int argc, char *argv[])
{
    char *filename;
    char *algorithm;
    int rr_quantum;
    FILE *fptr;
    Process *processes;

    // Check if args are valid
    if (argc >= 3)
    {
        filename = argv[1];
        algorithm = str_tolower(argv[2]);

        // Check if algorithm is fcfs, rr or sjf
        if (strcmp(algorithm, "fcfs") == 0 || strcmp(algorithm, "sjf") == 0)
        {
            // Nothing to do here
        }
        else if (strcmp(algorithm, "rr") == 0)
        {
            // If algorithm is rr, check for quantum
            if (argc == 4)
            {
                rr_quantum = atoi(argv[3]);
            }
            else
            {
                printf("ERR: [time quantum] required for [RR] algorithm!\n");
                return 0;
            }
        }
        else
        {
            printf("ERR: Must choose between [FCFS|RR|SJF] algorithms!\n");
            return 0;
        }
    }
    else
    {
        printf("USAGE: skd input_file [FCFS|RR|SJF] [time_quantum]\n");
        return 0;
    }

    // Open file
    fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        printf("ERR: Unable to open file '%s'\n", filename);
        return 0;
    }

    // Detect empty file
    if (fgetc(fptr) == EOF)
    {
        printf("ERR: Empty file!\n");
        return 0;
    }
    else
    {
        rewind(fptr);
    }

    // Read number of lines
    char buff[255];
    fgets(buff, 255, fptr);
    int n_process = atoi(buff);

    processes = (Process *)malloc(sizeof(Process) * n_process);

    // Continue reading file and store numbers in processes array
    for (int i = 0; i < n_process; i++)
    {
        fgets(buff, 255, fptr);
        processes[i].pid = atoi(strtok(buff, " "));          // pid
        processes[i].arrival_time = atoi(strtok(NULL, " ")); // arrival time
        processes[i].burst_time = atoi(strtok(NULL, " "));   // burst time
    }

    if (strcmp(algorithm, "fcfs") == 0)
    {
        int avg = 0;
        fcfs(processes, n_process);
        printf("Algorithm: FCFS\n");
        printf("---------------\n");
        printf(" PID   Arrival Time   Start Time   End Time   Running Time   Waiting Time\n");
        for (int i = 0; i < n_process; i++)
        {
            Process process = processes[i];
            int pid = process.pid;
            int arrival = process.arrival_time;
            int start = process.start_time;
            int end = process.end_time;
            int running = process.running_time;
            int waiting = process.waiting_time;
            avg += waiting;
            printf(" %3d   %12d   %10d   %8d   %12d   %12d\n", pid, arrival, start, end, running, waiting);
        }
        printf("Average Waiting Time: %d\n", avg / n_process);
    }
    else if (strcmp(algorithm, "sjf") == 0)
    {
        int avg = 0;
        sjf(processes, n_process);
        printf("Algorithm: SJF\n");
        printf("---------------\n");
        printf(" PID   Arrival Time   Start Time   End Time   Running Time   Waiting Time\n");
        for (int i = 0; i < n_process; i++)
        {
            Process process = processes[i];
            int pid = process.pid;
            int arrival = process.arrival_time;
            int start = process.start_time;
            int end = process.end_time;
            int running = process.running_time;
            int waiting = process.waiting_time;
            avg += waiting;
            printf(" %3d   %12d   %10d   %8d   %12d   %12d\n", pid, arrival, start, end, running, waiting);
        }
        printf("Average Waiting Time: %.2f\n", (float)avg / n_process);
    }
    else if (strcmp(algorithm, "rr") == 0)
    {
        int avg = 0;
        printf("Algorithm: RR, quantum: %d\n", rr_quantum);
        printf("---------------\n");
        rr(processes, n_process, rr_quantum);
        printf(" PID   Arrival Time   Running Time   End Time   Waiting Time\n");
        for (int i = 0; i < n_process; i++)
        {
            Process process = processes[i];
            int pid = process.pid;
            int arrival = process.arrival_time;
            int end = process.end_time;
            int running = process.running_time;
            int waiting = process.waiting_time;
            avg += waiting;
            printf(" %3d   %12d   %12d   %8d   %12d\n", pid, arrival, running, end, waiting);
        }
        printf("Average Waiting Time: %.2f\n", (float)avg / n_process);
    }
}

Queue queue_create()
{
    Queue temp;
    temp.length = 0;
    temp.processes = (Process **)malloc(sizeof(Process *));
    return temp;
}

void queue_push(Process *val, Queue *queue)
{
    int q_len = queue->length;
    Process **temp = (Process **)malloc((q_len + 1) * sizeof(Process *));
    for (int i = 0; i < q_len; i++)
    {
        temp[i] = queue->processes[i];
    }
    temp[q_len] = val;
    queue->length = q_len + 1;
    free(queue->processes);
    queue->processes = temp;
}

Process *queue_pop(Queue *queue)
{
    int q_len = queue->length;
    Process **temp = (Process **)malloc((q_len - 1) * sizeof(Process *));
    for (int i = 1; i < q_len; i++)
    {
        temp[i - 1] = queue->processes[i];
    }
    Process *first = queue->processes[0];
    queue->length = q_len - 1;
    free(queue->processes);
    queue->processes = temp;
    return first;
}

// Returns address to PROCESS inside PROCESSES, does NOT return a SEPARATE Process
Process *find_process(char *by, int val, Process *processes, int n_process)
{
    // Find in array with to_find
    for (int i = 0; i < n_process; i++)
    {
        if (strcmp(by, "pid") == 0)
        {
            if (val == processes[i].pid)
            {
                return &processes[i];
            }
        }
        else if (strcmp(by, "arrival") == 0)
        {
            if (val == processes[i].arrival_time)
            {
                return &processes[i];
            }
        }
    }

    // Return NULL if process not found
    return NULL;
}

void sort_queue_arrival(Queue *queue)
{

    int max;
    int len = queue->length;
    for (int i = 0; i < len - 1; i++)
    {
        max = i;
        for (int j = i + 1; j < len; j++)
        {
            if (queue->processes[j]->arrival_time < queue->processes[max]->arrival_time)
            {
                max = j;
            }

            int pid = queue->processes[j]->pid;
            int arrival_time = queue->processes[j]->arrival_time;
            int burst_time = queue->processes[j]->burst_time;
            int start_time = queue->processes[j]->start_time;
            int end_time = queue->processes[j]->end_time;
            int running_time = queue->processes[j]->running_time;
            int waiting_time = queue->processes[j]->waiting_time;

            queue->processes[j]->pid = queue->processes[max]->pid;
            queue->processes[j]->arrival_time = queue->processes[max]->arrival_time;
            queue->processes[j]->burst_time = queue->processes[max]->burst_time;
            queue->processes[j]->start_time = queue->processes[max]->start_time;
            queue->processes[j]->end_time = queue->processes[max]->end_time;
            queue->processes[j]->running_time = queue->processes[max]->running_time;
            queue->processes[j]->waiting_time = queue->processes[max]->waiting_time;

            queue->processes[max]->pid = pid;
            queue->processes[max]->arrival_time = arrival_time;
            queue->processes[max]->burst_time = burst_time;
            queue->processes[max]->start_time = start_time;
            queue->processes[max]->end_time = end_time;
            queue->processes[max]->running_time = running_time;
            queue->processes[max]->waiting_time = waiting_time;
        }
    }
}

// Simulates process execution by incrementing the running_time counter
// If running_time == burst_time, returns 1 to signal process completion
int process_execute(Process *process)
{
    process->running_time++;
    if (process->running_time == process->burst_time)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void fcfs(Process *processes, int n_process)
{
    int time = 0;
    Queue p_queue = queue_create(); // Contains address to processes in queue
    int n_process_finished = 0;

    Process *running = NULL;

    // Start time loop
    while (1)
    {
        // Find process that has arrived at current time
        Process *process = find_process("arrival", time, processes, n_process);
        int running_process_complete;

        // If process found, add to ready queue
        if (process != NULL)
        {
            queue_push(process, &p_queue);
        }

        // Check if any process is being executed
        if (running == NULL)
        {
            // Execute process
            running = find_process("pid", queue_pop(&p_queue)->pid, processes, n_process);
            running->start_time = time;
        }

        // Execute process until done
        if (running != NULL)
        {
            if (time > 0)
            {
                // Couldn't get output to match, had to skip process execution at time = 0
                running_process_complete = process_execute(running);
            }
            if (running_process_complete == 1)
            {
                running->end_time = time;
                // If process is done executing, remove it from running
                running = NULL;
                // And bring in new process

                // Check if all processes are executed
                n_process_finished++;
                if (n_process_finished == n_process)
                {
                    break;
                }

                running = find_process("pid", queue_pop(&p_queue)->pid, processes, n_process);
                running->start_time = time;
            }
        }
        // Increment waiting time of processes in queue
        for (int i = 0; i < p_queue.length; i++)
        {
            p_queue.processes[i]->waiting_time++;
        }

        // Increment time
        time++;
    }
}

void sjf(Process *processes, int n_process)
{
    int time = 0;
    Queue p_queue = queue_create(); // Contains address to processes in queue
    int n_process_finished = 0;

    Process *running = NULL;

    // Start time loop
    while (1)
    {
        // Find process that has arrived at current time
        Process *process = find_process("arrival", time, processes, n_process);
        int running_process_complete;

        // If process found, add to ready queue
        if (process != NULL)
        {
            queue_push(process, &p_queue);
            // Sort queue according to waiting time
            sort_queue_arrival(&p_queue);
        }

        // Check if any process is being executed
        if (running == NULL)
        {
            // Execute process
            running = find_process("pid", queue_pop(&p_queue)->pid, processes, n_process);
            running->start_time = time;
        }

        // Execute process until done
        if (running != NULL)
        {
            if (time > 0)
            {
                // Couldn't get output to match, had to skip process execution at time = 0
                running_process_complete = process_execute(running);
            }
            if (running_process_complete == 1)
            {
                running->end_time = time;
                // If process is done executing, remove it from running
                running = NULL;
                // And bring in new process

                // Check if all processes are executed
                n_process_finished++;
                if (n_process_finished == n_process)
                {
                    break;
                }

                running = find_process("pid", queue_pop(&p_queue)->pid, processes, n_process);
                running->start_time = time;
            }
        }
        // Increment waiting time of processes in queue
        for (int i = 0; i < p_queue.length; i++)
        {
            p_queue.processes[i]->waiting_time++;
        }

        // Increment time
        time++;
    }
}

void rr(Process *processes, int n_process, int quantum)
{
    int time = 0;
    int rr = 0;
    Queue p_queue = queue_create(); // Contains address to processes in queue
    int n_process_finished = 0;

    Process *running = NULL;
    printf(" PID   Start Time   End Time   Running Time\n");
    // Start time loop
    while (1)
    {
        // Find process that has arrived at current time
        Process *process = find_process("arrival", time, processes, n_process);
        int running_process_complete;

        // If process found, add to ready queue
        if (process != NULL)
        {
            queue_push(process, &p_queue);
        }

        // Check if any process is being executed
        if (running == NULL)
        {
            // Execute process
            running = find_process("pid", queue_pop(&p_queue)->pid, processes, n_process);
            running->start_time = time;
        }

        // Execute process until done
        if (running != NULL)
        {
            if (time > 0)
            {
                // Couldn't get output to match, had to skip process execution at time = 0
                running_process_complete = process_execute(running);
            }

            if (running_process_complete == 1)
            {
                running->end_time = time;
                printf(" %3d   %10d   %8d   %12d\n", running->pid, running->start_time, running->end_time, running->running_time);
                // If process is done executing, remove it from running
                running = NULL;

                // Check if all processes are executed
                n_process_finished++;
                if (n_process_finished == n_process)
                {
                    break;
                }

                // And bring in new process
                running = find_process("pid", queue_pop(&p_queue)->pid, processes, n_process);
                running->start_time = time;
            }

            // RR expires, push process to queue and get another
            if (rr == quantum && running_process_complete != 1)
            {
                running->end_time = time;
                printf(" %3d   %10d   %8d   %12d\n", running->pid, running->start_time, running->end_time, running->running_time);
                queue_push(running, &p_queue);
                running = NULL;
                rr = 0;

                // And bring in new process
                running = find_process("pid", queue_pop(&p_queue)->pid, processes, n_process);
                running->start_time = time;
            }
        }
        // Increment waiting time of processes in queue
        for (int i = 0; i < p_queue.length; i++)
        {
            p_queue.processes[i]->waiting_time++;
        }

        // Increment time and rr
        rr++;
        time++;
        
    }
}

char *str_tolower(char *str)
{
    int len = strlen(str);
    char *strlower = (char *)malloc(len * sizeof(char));

    for (int i = 0; i < len; i++)
    {
        strlower[i] = tolower(str[i]);
    }

    return strlower;
}