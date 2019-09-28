//
// Created by Tushar Malyan on 28/09/19.
//
#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <errno.h>
#include <unistd.h>
int main()
{
    printf("Enter process ID\n");
    int pid;
    scanf(" %d",&pid);
    printf("Enter file name:\n");
    char* filename="";
    scanf(" %s",filename);
    long int ret = syscall(317, pid, filename);
    if(ret != 0)
    {
        printf("Ran into an error while executing sh_task_info.\n");
        printf("Error No.: %d\n", errno);
    }
    else
        printf("Execution of sh_task_info was successfull.\nUse dmesg to see process info.\n");

    return 0;
}
