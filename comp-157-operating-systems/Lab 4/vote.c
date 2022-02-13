#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    // Get number of voters and rounds
    int voters, rounds;
    printf("Enter the number of voters: ");
    scanf("%i", &voters);
    printf("Enter the number of rounds: ");
    scanf("%i", &rounds);

    for (int i = 0; i < rounds; i++)
    {
        printf("\n----- Round %i -----\n", i+1);
        // Create N pipes
        int *pipes = (int *)malloc(voters * 2 * sizeof(int));
        for (int j = 0; j < voters; j++)
        {
            // Make pipes
            int pipe_index = j * 2;
            pipe(&pipes[pipe_index]);
        }

        // Create N child processes
        pid_t *childs = (pid_t *)malloc(voters * sizeof(pid_t));
        for (int j = 0; j < voters; j++)
        {
            // Fork childs
            pid_t pid = fork();

            if (pid == 0)
            {
                // Child code

                // Seed for randomizer
                srand(getpid());

                // Close input end of related pipe
                close(pipes[j * 2]);
                int vote = rand() % 2; // 0 = no, 1 = yes

                // Write output end of related pipe
                // https://stackoverflow.com/questions/5237041/how-to-send-integer-with-pipe-between-two-processes
                write(pipes[(j * 2) + 1], &vote, sizeof(int));
                exit(0);
            }
            else if (pid > 0)
            {
                // parent process
                childs[j] = pid;

                // Close output end of related pipe
                close(pipes[(j * 2) + 1]);
            }
        }

        // Wait for all child processes
        int remaining_childs = voters;
        while (remaining_childs > 0)
        {
            wait(NULL);
            remaining_childs--;
        }

        // Done waiting, read all pipes
        int yes = 0;
        int no = 0;
        for (int j = 0; j < voters; j++)
        {
            int vote;
            read(pipes[j * 2], &vote, sizeof(int));
            printf("Voter %i votes: ", j);
            if (vote == 0)
            {
                no++;
                printf("NO\n");
            }
            else
            {
                yes++;
                printf("YES\n");
            }
        }

        // Check who won
        printf("--- Round %i, the voting result is a ", i+1);
        if (yes > no)
        {
            printf("YES.\n");
        }
        else if (no > yes)
        {
            printf("NO.\n");
        }
        else
        {
            printf("TIE.\n");
        }
    }
}