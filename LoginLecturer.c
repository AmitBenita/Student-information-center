#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
int main(int argc, char* argv[]) {

	int LecPass, rbytes, flag = 0;
	char buffer[256] = "\0", dest[256] = "", * id, line[256] = "\0";
	char* username = "\0", * password = "\0";
	strcpy(dest, "./");
	if (argc != 3) //Checking if we received the required number of arguments
	{
		printf("Invalid number of arguments\n");
		return 1;
	}
	if ((LecPass = open("lec_pass.txt", O_RDONLY)) == -1) //opening a lec file
	{
		perror("File lec_pass does not exist");
		return(1);
	}
	while ((rbytes = read(LecPass, buffer, 1)) > 0) {  //read the title
		if (buffer[0] == '\n')
			break;
	}
	while (rbytes = read(LecPass, buffer, 1) > 0) { //Loop and reading a line into a "line" variable
		if (buffer[0] != '\n')
		{
			strcat(line, buffer);
		}
		else
		{
			flag = 0;
			username = strtok(line, " ");
			password = strtok(NULL, " ");
			if (strcmp(username, argv[1]) != 0) {
				flag = 1;
			}
			if (flag == 0) //if username correct 
			{
				argv[2][strlen(argv[2]) - 1] = '\0';
				if (strcmp(password, argv[2]) != 0) //check if the password is correct
				{
					printf("Incorrect Password\n");
					close(LecPass);
					return 0;
				}
				flag = 2;
			}
			if (flag == 2) {
				close(LecPass);
				strcat(dest, "Lec_shell");
				if (execl(dest, "Lec_shell", argv[1], NULL) == -1)
				{
					printf("execl not exist\n");
					return 2;
				}
			}
			strcpy(line, "");
		}
	}
	printf("Lecturer not found\n");
	close(LecPass);
	return 1;
}