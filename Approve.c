#include <stdio.h> 
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
void Reset(char* id);
int main(int argc, char* argv[]) {
	int i;
	char dest[256] = "student/";
	if (argc != 2)
	{
		printf("Invalid number of arguments");
		return 1;
	}
	strcat(dest, argv[1]);
	if (chmod(dest, 0777) == 0) //Unrestrict folder permissions
	{
		printf("Successfully Approved\n"); //Printing an appropriate message
		Reset(argv[1]);

		return 0;
	}
	else {
		printf("Failed to Returning permissions.\n");
		return 1;
	}
}

void Reset(char* id) {
	int cntfile, StdPass, flag = 0, count = 0;
	char buffer[256] = "\0", line[256] = "", * FileCntUser, CorrectLine[256] = "", zero[256] = " 0\n";
	char* username, * pass, * ID;
	char  newnumber[3];
	if ((StdPass = open("std_pass.txt", O_RDWR)) == -1) //Opening a CNT file for reading
	{
		perror("Failed to open std_pass.txt file");
	}
	while (read(StdPass, buffer, 1) > 0)
	{

		if (buffer[0] != '\n') { //read one line
			strcat(line, buffer);
		}
		else
		{
			username = strtok(line, " ");
			pass = strtok(NULL, " ");
			ID = strtok(NULL, " ");
			if (strcmp(id, ID) == 0)
			{

				flag = 1;
				break;
			}
			strcpy(line, "");
		}
	}
	strcpy(line, "");
	if (flag == 1)
	{
		if ((cntfile = open("CntFile.txt", O_RDWR)) == -1) //Opening a CNT file for reading and writing
		{
			perror("Failed to open CntFile.txt file");
		}
		while (read(cntfile, buffer, 1) > 0)
		{
			if (buffer[0] != '\n') { //read one line
				strcat(line, buffer);
			}
			else
			{
				FileCntUser = strtok(line, " ");
				if (strcmp(FileCntUser, username) == 0)
				{
					sprintf(newnumber, "%d", count);
					strcat(username, " ");
					strcat(username, newnumber);
					lseek(cntfile, -strlen(username) - 1, SEEK_CUR);
					if (write(cntfile, username, strlen(username)) == -1)
					{
						perror("Write failed");
					}
					break;
				}
				else
				{
					strcpy(line, "");
				}
			}
		}
	}
	else {
		printf("Student Not Found!");
	}
}
