#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
int main(int argc, char* argv[])
{
	int Courses_txt;
	int check, i;
	char Title[] = "Id Name day start end\n";
	//char line[256] = "\n";
	char line[256] = "";
	if (argc != 6) //Checking if we received the required number of arguments
	{
		printf("SetCourses: missing parameters!\n");
		return 1;
	}
	for (i = 1; i < 6; i++)
	{
		strcat(line, argv[i]);
		if (i != 5)
			strcat(line, " ");
	}

	if ((Courses_txt = open("Courses/Courses.txt", O_WRONLY | O_CREAT, 0664)) == -1)
	{
		perror("Failed to open Courses_txt");
		return(3);
	}
	check = lseek(Courses_txt, 0, SEEK_END);

	if (check == 0) //if empty
	{
		if ((write(Courses_txt, Title, strlen(Title))) == -1) //write the title
		{
			perror("Failed write Courses_txt");
			return(3);
		}
		if ((write(Courses_txt, line, strlen(line))) == -1)
		{
			perror("Failed write Courses_txt");
			return(3);
		}
		write(Courses_txt, "\n", 1);
	}
	else 	//not empty
	{
		if ((write(Courses_txt, line, strlen(line))) == -1)
		{
			perror("Failed write Courses_txt");
			return(3);
		}
		write(Courses_txt, "\n", 1);
		printf("Succesfully created Course\n");
	}
	close(Courses_txt);
	return 0;
}