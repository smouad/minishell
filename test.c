#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int ac, char **av, char **env)
{
    
    int fd[2];

    pipe(fd);
    int id1 = fork();
    if (id1 == 0)
    {
        dup2 (fd[1], 1);
        close (fd[0]);
        close (fd[1]);
        char *arg[] = {"/bin/ls", "-a", NULL};
        execve (arg[0], arg, env);
    }
    int id2 = fork ();
    if (id2 == 0)
    {
        dup2(fd[0], 0);
        close (fd[0]);
        close (fd[1]);
        char *arg[] = {"/usr/bin/grep", "s", NULL};
        execve (arg[0], arg, env);
    }
    close (fd[0]);
    close (fd[1]);
    wait (NULL);
}