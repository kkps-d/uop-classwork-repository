/**
 * This program illustrates the functionality of the ipcs command on POSIX systems.
 *
 * sm.c
 *
 * Usage:
 *      gcc -o sm sm.c
 *
 *      ./sm 
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int segment_id;            // identifier of the shared memory segment
    unsigned short mode;       // permissions of the segment
    struct shmid_ds shmbuffer; // the shared memory segment

    // Step 1: Create a new shared memory segment using shmget
    segment_id = shmget(IPC_PRIVATE, 200 * sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR);

    // Step 2: Retrieve the information of the segment and store in shmbuffer
    if (shmctl(segment_id, IPC_STAT, &shmbuffer) == -1)
    {
        fprintf(stderr, "Unable to access segment %d\n", segment_id);
        return -1;
    }

    // Step 3: output information about the segment in the required format

    printf("ID         KEY    MODE       OWNER   SIZE   ATTACHES\n");
    printf("--         ---    ----       -----   ----   --------\n");
    printf("%i         %i     ", segment_id, shmbuffer.shm_perm.__key);

    /** report on the permission */
    mode = shmbuffer.shm_perm.mode;

    /** OWNER */
    if (mode & 0400)
        printf("r");
    else
        printf("-");
    if (mode & 0200)
        printf("w");
    else
        printf("-");
    if (mode & 0100)
        printf("x");
    else
        printf("-");

    /** GROUP */
    if (mode & 0040)
        printf("r");
    else
        printf("-");
    if (mode & 0020)
        printf("w");
    else
        printf("-");
    if (mode & 0010)
        printf("x");
    else
        printf("-");

    /** WORLD */
    if (mode & 0004)
        printf("r");
    else
        printf("-");
    if (mode & 0002)
        printf("w");
    else
        printf("-");
    if (mode & 0001)
        printf("x");
    else
        printf("-");

    printf("  %i    %lu    %lu\n", shmbuffer.shm_perm.uid, shmbuffer.shm_segsz, shmbuffer.shm_nattch);

    // Step 4: Create a new process using fork
    __pid_t pid = fork();

    // Step 5: The child process sends a message to the parent process via the
    //         shared memory segment created in Step 1 and the parent prints out
    //         the message it received from the child process
    if (pid == 0)
    {
        // Child process
        char *shared = (char *)shmat(segment_id, NULL, 0); // Attach to shared memory
        sprintf(shared, "Hello Parent Process!"); // Write to shared memory
        shmdt(shared); // Detach from shared memory
    }
    else if (pid > 0)
    {
        // Parent process
        wait(NULL); // Wait for child process to write message
        char *shared = (char *)shmat(segment_id, NULL, 0); // Attach to shared memory
        printf("\nParent received message from Child: %s\n", shared); // Print contents of shared memory
        // shmdt(shared); // Detach from shared memory
        // shmctl(segment_id, IPC_RMID, NULL); // Remove shared memory
    }

    return 0;
}
