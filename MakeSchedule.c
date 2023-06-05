#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
int Course(char* course, char** line);
int main(int argc, char* argv[])
{
    int sch_file, rbytes, flag = 0, flagReturn;
    char input[256], path_stu[256] = "student/";
    char* line_course = "";
    char* del_rm[3] = { "rm","", NULL }, ttl[256] = "ID Name day start end\n";
    int lenTtl = strlen(ttl);
    if (argc != 2)
    {
        printf("missing parameters!");
        exit(1);

    }
    strcat(path_stu, argv[1]);
    strcat(path_stu, "/Schedule.txt");

    if ((sch_file = open(path_stu, O_RDWR | O_CREAT, 0664)) == -1)
    {
        printf("file Schedule.txt couldn't open");
        exit(1);
    }
    if ((rbytes = read(sch_file, input, 256)) == 0)
        write(sch_file, ttl, lenTtl);

    lseek(sch_file, 0, SEEK_END);
    printf("Insert Course ID:\n");

    fgets(input, 256, stdin);
    input[strlen(input) - 1] = '\0';

    while (1)
    {

        if ((strcmp(input, "Exit") == 0) || (strcmp(input, "exit") == 0))
            break;

        if (strcmp("Confirm", input) != 0 && strcmp("confirm", input) != 0)
        {
            flagReturn = Course(input, &line_course);
        }
        if (flagReturn == 1)
        {
            rewind(stdin);
            fgets(input, 256, stdin);
            input[strlen(input) - 1] = '\0';

            if ((strcmp("Confirm", input) == 0) || (strcmp("confirm", input) == 0))
            {
                write(sch_file, line_course, strlen(line_course));
                write(sch_file, "\n", 1);
                flag = 1;
            }
        }
        if (flagReturn == 0)
        {
            printf("Course doesn't exist");
            exit(1);

        }

    }
    if (flag != 1)
    {
        del_rm[1] = (char*)malloc(strlen(path_stu) * sizeof(char) + 1);
        strcpy(del_rm[1], path_stu);
        execvp("/bin/rm", del_rm);
    }
    if (flag == 1)
        close(sch_file);
    return 0;
}
int Course(char* course, char** line)
{
    int Courses_txt, rbytes, flag = 0;
    char Line[256] = "", buffer[256] = "";
    char* id_course;

    if ((Courses_txt = open("Courses/Courses.txt", O_RDONLY)) == -1)
    {
        printf("file Courses.txt couldn't open");
        exit(1);
    }
    while ((rbytes = read(Courses_txt, buffer, 1)) > 0)
    {
        if (buffer[0] == '\n')
            break;
    }


    while ((rbytes = read(Courses_txt, buffer, 1)) > 0)
    {

        if (buffer[0] != '\n')
            strcat(Line, buffer);
        else
        {
            strcpy(buffer, Line);
            id_course = strtok(Line, " ");
            if ((strcmp(id_course, course)) == 0)
            {
                while (id_course != NULL)
                {
                    printf("%s ", id_course);
                    id_course = strtok(NULL, " ");
                }
                printf("\n");
                flag = 1;
                break;
            }
            strcpy(Line, "");
        }
    }
    close(Courses_txt);
    if (flag == 0)
        return 0;
    else
    {
        *line = strdup(buffer);
        return 1;
    }

}