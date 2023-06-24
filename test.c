#include <unistd.h>
#include <stdio.h>
int main()
{
    int id;
    id = access("./minishell", F_OK);
    printf("%d\n", id);
}