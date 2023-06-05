#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void CreateFolders();
int main()
{
	int i, flag = 0;
	char input[256] = "\0", dest[256] = "";
	char* command, * username, * password;
	CreateFolders();
	while (1)
	{
		printf("LockShell>");
		fgets(input, 256, stdin);
		command = strtok(input, " ");
		username = strtok(NULL, " ");
		password = strtok(NULL, " ");
		strcpy(dest, "./");
		pid_t pid;
		pid = fork();
		if (pid < 0)
		{
			printf("Failed to create child process.\n");
			exit(1);
		}
		else if (pid == 0)
		{
			if (command[strlen(command) - 1] == '\n')     
			{
				command[strlen(command) - 1] = '\0';
			}
			strcat(dest, command);
			if (execl(dest, command, username, password, NULL) == -1) {
				printf("Not Supported\n");
				exit(1);
			}
		}
		else
		{
			wait(NULL);
			if (strcmp(command, "exit\n") == 0)
			{
				return 0;
			}
		}
	}
	return 0;
}
void CreateFolders()
{
	int StdPass, Courses, rbytes, i;
	char buffer[256], studentdest[256] = "", STR[256] = "";
	char coursestxt[] = "Courses/Courses.txt";
	char ttl[] = "Id Name Day start end\n61589 deep_learning Monday 17:00 20:00\n";
	char* id;
	if (mkdir("Courses", 0777) == -1 || mkdir("student", 0777) == -1)
	{
		perror("Folder creation failed");
		exit(1);
	}
	if ((Courses = open(coursestxt, O_WRONLY | O_CREAT, 0664)) == -1)//creates courses.txt
	{
		perror("Failed to open file");
		exit(1);
	}
	if ((Courses = write(Courses, ttl, strlen(ttl))) == -1)
	{
		perror("Failed to write to file");
		exit(1);
	}
	if ((StdPass = open("std_pass.txt", O_RDONLY)) == -1)
	{
		perror("File does not exist"); exit(1);
	}
	//skipping the first line
	while ((rbytes = read(StdPass, buffer, 1)) > 0) {
		if (buffer[0] == '\n')
			break;
	}
	while ((rbytes = read(StdPass, buffer, 1)) > 0)
	{
		if (buffer == NULL)
			break;
		if (buffer[0] != '\n')
			strcat(STR, buffer);

		else
		{
			strcpy(studentdest, "student/");
			strtok(STR, " ");
			strtok(NULL, " ");
			id = strtok(NULL, " ");
			strcat(studentdest, id);
			if (mkdir(studentdest, 0777) == -1)
			{
				perror("Folder creation failed\n");
				exit(1);
			}
			strcpy(STR, "");
		}
	}
}