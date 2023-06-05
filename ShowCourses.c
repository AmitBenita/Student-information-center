#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
int main() {
	int rbytes;
	char buffer[256] = "\0", CoursesDest[] = "Courses/Courses.txt"; //Path to enter the Courses file
	int  Courses_text = open(CoursesDest, O_RDONLY);
	if (Courses_text == -1) {
		perror("could not open Courses_text");
		return 1;
	}
	while ((rbytes = read(Courses_text, buffer, 1)) > 0) { //read title
		if (buffer[0] == '\n')
			break;
	}
	while (rbytes > 0) {
		printf("%s", buffer); //Printing available courses
		if ((rbytes = read(Courses_text, buffer, 256)) == -1)
		{
			perror("Could not read Courses_text");
			exit(1);
		}
	}
	close(Courses_text);
	printf("\n");
	return 0;
}
