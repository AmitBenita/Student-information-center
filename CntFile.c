#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
int main()
{
	int CntFile, StdPass, rbytes, wbytes;
	char buffer[256] = "";
	char STR[256] = "";
	char* myuser;
	if ((CntFile = open("CntFile.txt", O_WRONLY | O_CREAT, 0664)) == -1)
	{
		perror("Failed to open CntFile file");
		return(-1);
	}
	if ((StdPass = open("std_pass.txt", O_RDONLY)) == -1)
	{
		perror("Failed to open StdPass file");
		return(-1);
	}
	while ((rbytes = read(StdPass, buffer, 1)) > 0) { //skip the first line
		if (buffer[0] == '\n')
			break;
	}
	while ((rbytes = read(StdPass, buffer, 1)) > 0)
	{
		if (buffer[0] != '\n') {
			strcat(STR, buffer);
		}
		else
		{
			myuser = strtok(STR, " ");

			strcat(myuser, " 0");
			strcat(myuser, "\n");

			if ((wbytes = write(CntFile, myuser, strlen(myuser))) == -1)
			{
				perror("Writing to file failed");
				return(-1);
			}
			myuser[0] = '\0';
		}
	}
	close(CntFile);
	close(StdPass);
	return 0;
}