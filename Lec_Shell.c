#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<unistd.h>
int main()
{
    char* command, UserInput[256];
    int idx = 1, flag = 0, i;
    char* argv[7];
    char* Commands[7] = { "SetCourses", "GetSchedule","DeleteStudent", "Freeze", "Approve", "ShowCourses","LogOut" }; //The correct command options
    pid_t pid;
    while (1)
    {
        printf("LecShell> ");
        fgets(UserInput, 256, stdin); //user input of the command and arguments
        UserInput[strlen(UserInput) - 1] = '\0';
        command = strtok(UserInput, " ");
        argv[idx - 1] = (char*)malloc(strlen(command) * sizeof(char) + 1);
        strcpy(argv[idx - 1], command);
        while (command != NULL)
        {
            command = strtok(NULL, " ");
            if (command != NULL)
            {
                idx++;
                argv[idx - 1] = (char*)malloc(strlen(command) * sizeof(char) + 1);
                strcpy(argv[idx - 1], command);
            }
        }
        argv[idx] = NULL;

        for (i = 0; i <= 6; i++)
        {
            if (strcmp(argv[0], Commands[i]) == 0)
                flag = 1;
        }
        pid = fork();
        if (pid < 0) //if faild to create child proccess
        {
            printf("Failed to create child process.\n");
            exit(1);
        }
        if (pid == 0) //child proccess
        {
            if (flag == 1)
            {
                if (execv(argv[0], argv) == -1)
                {
                    printf("Not Supported\n");
                    exit(1);
                }
            }
        }
        wait();
        if (strcmp(argv[0], "LogOut") == 0)
        {
            for (i = 0; i < idx; i++)
                free(argv[i]); //Release of dynamic allocations
            exit(1);
        }
        for (i = 0; i < idx; i++)
            free(argv[i]);
        strcpy(UserInput, "");
        flag = 0;
        idx = 1;
        rewind(stdin);
    }
    return 0;
}