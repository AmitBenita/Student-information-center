#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
int CheckAttempts(char* user);
int main(int argc, char* argv[]) {

	int StdPass, rbytes, flag = 0, i, att;
	char buffer[256] = "\0", dest[256] = "", studentdest[256] = "student/";
	char STR[256] = "\0", * id, line[256] = "\0";
	char* username = "\0", * password = "\0";
	strcpy(dest, "./");
	if (argc != 3) //Checking if we received the required number of arguments
	{
		printf("missing parameters!\n");
		return 1;
	}
	if ((StdPass = open("std_pass.txt", O_RDONLY)) == -1) //opening a std file
	{
		perror("File std_pass does not exist");
		return(1);
	}
	while ((rbytes = read(StdPass, buffer, 1)) > 0) { //read the title
		if (buffer[0] == '\n')
			break;
	}
	while (rbytes = read(StdPass, buffer, 1) > 0) {
		if (buffer[0] != '\n') //Loop and reading a line into a "line" variable
		{
			strcat(line, buffer);
		}
		else
		{
			flag = 0;
			username = strtok(line, " ");
			password = strtok(NULL, " ");
			id = strtok(NULL, " ");
			if (strcmp(username, argv[1]) != 0) { //Checking if the username is correct (flag=1 if not)
				flag = 1;
			}
			if (flag == 0) //if username correct 
			{
				argv[2][strlen(argv[2]) - 1] = '\0';
				if (strcmp(password, argv[2]) != 0) //check if the password is correct
				{
					att = CheckAttempts(argv[1]); //check if the user blocked
					if (att == 0)
					{
						printf("Incorrect Password\n");
						close(StdPass);
						return 0;
					}
					if (att == 1)
					{
						printf("%s account Blocked!\n", username);
						strcat(studentdest, id);
						chmod(studentdest, 0000); //limit permissions
						close(StdPass);
						return 0;
					}
				}
				flag = 2;
			}
			if (flag == 2) {
				close(StdPass);
				strcat(dest, "Std_shell"); //If the username and password are correct
				if (execl(dest, "Std_shell", argv[1], NULL) == -1)
				{
					printf("execl not exist\n");
					return 2;
				}
			}
			strcpy(line, "");
		}

	}
	printf("Student Not Found!\n");
	close(StdPass);
	return 1;
}
int CheckAttempts(char* username)
{
	int cntfile, wbytes, count = 0, flag = 0;
	char STR[256] = "\0", buffer[256] = "\0";
	char  newnumber[3];
	char* name, * num;
	if ((cntfile = open("CntFile.txt", O_RDWR)) == -1) //Opening a CNT file for reading
	{
		perror("Failed to open CntFile.txt file");
		return 3;
	}
	while (read(cntfile, buffer, 1) > 0) //The loop checks line by line and if we found the user's name in the file, it checks if he tried to log in 3 times and returns 1 if so
	{

		if (buffer[0] != '\n') { //read one line
			strcat(STR, buffer);
		}
		else
		{
			name = strtok(STR, " ");
			num = strtok(NULL, " ");
			count = atoi(num);
			if (strcmp(username, name) == 0)
			{
				if (count != 3)
				{
					count++;
					if (count == 3)
						flag = 1;
					sprintf(newnumber, "%d", count);
					strcat(name, " ");
					strcat(name, newnumber);
					lseek(cntfile, -strlen(name) - 1, SEEK_CUR);
					if ((wbytes = write(cntfile, name, strlen(name))) == -1)
					{
						perror("Write failed");
						return(3);
					}
					if (flag == 1)//BLOCK
						return 1;
					else {
						return 0;
					}
				}
				return 1;
			}
			strcpy(STR, "");
		}
	}
	close(cntfile);
	return 3;
}