#include <stdio.h> //deletestudent 
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
int main(int argc, char* argv[])	//argv[0]=name.c	argv[1]=id
{
	int i;
	char StudentDest[256] = "student/", dest[256];
	if (argc != 2)
	{
		printf("Invalid number of arguments"); //Checking if we received the required number of arguments
		return 1;
	}
	strcat(StudentDest, argv[1]);	//StudentDest = student/id
	strcpy(dest, StudentDest);	//dest=student/id
	strcat(dest, "/Schedule.txt");	//dest=student/id/Schedule.txt
	remove(dest);
	//Printing an appropriate message
	if (rmdir(StudentDest) != 0)
	{
		printf("Failed to delete folder.\n");
		return 1;
	}
	if (rmdir(StudentDest) == 0)
	{
		printf("The folder has been successfully deleted!\n");
		return 0;
	}
}