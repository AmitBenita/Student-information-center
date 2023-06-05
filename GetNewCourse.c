#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
int main() {
    int rbytes, countlines = 1;
    char buffer[256] = "\0", dest[256] = "Courses/", string[256] = "", tempStr[256] = "";
    strcat(dest, "Courses.txt"); //Path to enter the Courses file
    int  Courses_text = open(dest, O_RDONLY);
    if (Courses_text == -1) {
        perror("could not open file 1");
        exit(EXIT_FAILURE);
    }
    while ((read(Courses_text, buffer, 1)) > 0) {//read title
        if (buffer[0] == '\n')
            break;
    }
    while (rbytes = read(Courses_text, &buffer, 1) > 0) {
        if (buffer[0] != '\n') { //read a line from Courses file
            strcat(string, buffer);
            strcpy(tempStr, string);
        }
        else
        {
            countlines++;
            strcpy(string, "");
        }

    }

    printf("%s\n", tempStr);

    close(Courses_text);
}