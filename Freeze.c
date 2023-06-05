#include <stdio.h> 
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
	int i;
	char dest[256] = "student/";
	if (argc != 2)
	{
		printf("Invalid number of arguments");
		return 1;
	}
	strcat(dest, argv[1]);
	if (chmod(dest, 0000) == 0) //Restrict folder permissions
	{
		printf("Permissions canceled successfully.\n");
		return 0;
	}
	else {
		printf("Failed to cancel permissions.\n");
		return 1;
	}

}