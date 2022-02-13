#include <stdlib.h>

typedef struct Process
{
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int end_time;
    int running_time;
    int waiting_time;
    size_t size;
} Process;

typedef struct Queue
{
    int length;
    Process **processes;
    size_t size;
} Queue;