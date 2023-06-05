#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
int IsBlock(char* name, char** Id);
int main(int argc, char* argv[]) {
	char dest[256] = "\0", buffer[256] = "", line[256] = "", * Id = NULL, InputCommand[256] = "";
	char* Commands[5] = { "ShowCourses", "GetNewCourse", "MakeSchedule", "GetSchedule", "LogOut" }; //The correct command options
	char* arr[3] = { NULL,NULL,NULL };
	int i, flag = 0;
	pid_t pid;
	while (1) {
		printf("StdShell> ");
		fgets(InputCommand, 256, stdin); //user input of the command 
		InputCommand[strlen(InputCommand) - 1] = '\0';
		arr[0] = (char*)malloc(strlen(InputCommand) * sizeof(char) + 1); //arr[0]=command
		strcpy(arr[0], InputCommand);
		if (strcmp(InputCommand, "MakeSchedule") == 0 || strcmp(InputCommand, "GetSchedule") == 0) //Checking if the user is blocked and restricting him from using certain commands
		{
			IsBlock(argv[1], &Id); //If the user is blocked then ID=NULL
			if (Id == NULL)
			{
				flag = -1;
				printf("Blocked Account !permission denied\n");
			}
			else
			{
				arr[1] = (char*)malloc(strlen(Id) * sizeof(char) + 1); //arr[1]=Id
				strcpy(arr[1], Id);
			}
		}
		if (flag != -1) //if not blocked
		{
			for (i = 0; i < 5; i++) //check if the command is valid
			{
				if (strcmp(arr[0], Commands[i]) == 0)
					flag = 1;
			}
			pid = fork();

			if (pid == 0) //child process
			{
				if (flag == 1)
				{
					if ((execv(arr[0], arr) == -1)) {
						printf("Not Supported\n");
						return 1;
					}
				}
			}
			if (pid < 0)
			{
				printf("Failed to create child process.\n");
				exit(1);
			}
			wait();
			if (strcmp(arr[0], "LogOut") == 0)
			{
				free(arr[0]);
				return 0;

			}
		}

		free(arr[0]);
		strcpy(InputCommand, "");
		flag = 0;
		rewind(stdin);
	}
	return 0;

}
//A function that checks if the user is blocked using the Std_pass file and CntFile. If the user is blocked the function will return ID=NULL, otherwise it will return the ID number
int IsBlock(char* name, char** Id) {

	char buffer[256] = "", * token, line[256] = "";
	int StdPass, rbytes, cntfile;

	if ((StdPass = open("std_pass.txt", O_RDONLY)) == -1) {
		perror("File std_pass does not exist");
		return(1);
	}
	while ((rbytes = read(StdPass, buffer, 1)) > 0)
	{
		if (buffer[0] != '\n')
			strncat(line, buffer, 1);
		else
		{
			token = strtok(line, " ");
			if (strcmp(token, name) == 0)
			{
				token = strtok(NULL, " ");
				token = strtok(NULL, " ");
				*Id = token;
				break;
			}
			strcpy(line, "");
		}
	}
	close(StdPass);
	strcpy(line, "");
	if ((cntfile = open("CntFile.txt", O_RDONLY)) != -1)
	{
		while ((rbytes = read(cntfile, buffer, 1)) > 0)
		{
			if (buffer[0] != '\n')
				strncat(line, buffer, 1);


			else
			{
				token = strtok(line, " ");
				if (strcmp(name, token) == 0)
				{
					token = strtok(NULL, " ");
					if (atoi(token) >= 3)
						*Id = NULL;
				}
				strcpy(line, "");
			}
		}
		close(cntfile);
	}


}
