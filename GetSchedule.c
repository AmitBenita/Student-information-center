#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>

int main(int argc, char* argv[])
{
    char path[256] = "student/";
    char* STR, buffer[256] = "\0", lineread[256] = "\0";
    int StdPass, flag = 0, Schedule;
    if (argc != 2) {
        perror("missing parameters!");
        exit(1);
    }

    if ((StdPass = open("std_pass.txt", O_RDONLY)) == -1) { //opening std_pass.txt
        perror("Failed to open std_pass.txt\n");
        exit(1);
    }
    while (read(StdPass, buffer, 1) > 0) //read the title
    {
        if (buffer[0] == '\n')
            break;

    }
    while (read(StdPass, buffer, 1) > 0)
    {
        if (buffer[0] != '\n')
            strcat(lineread, buffer);
        else
        {
            STR = strtok(lineread, " "); //check if the student exist
            STR = strtok(NULL, " ");
            STR = strtok(NULL, " ");
            if (strcmp(STR, argv[1]) == 0)
                flag = 1;
            strcpy(lineread, "");
        }
    }
    if (flag == 0)
    {
        printf("Student Not Found\n");
        return 0;
    }
    close(StdPass);
    strcat(path, argv[1]);
    strcat(path, "/Schedule.txt");
    if ((Schedule = open(path, O_RDONLY)) != -1)
    {
        while (read(StdPass, buffer, 1) > 0) //read the title
        {
            if (buffer[0] == '\n')
                break;

        }
        while (read(Schedule, buffer, 256) > 0) {
            printf("%s", buffer); //print the file
            if (read(Schedule, buffer, 256) == -1)
            {
                perror("read file Schedule_txt");
                exit(1);
            }
        }
        close(Schedule);
    }
    else
    {
        printf("Student Not register\n", argv[1]);
        exit(1);
    }
    return 0;
}