#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

struct node
{
    char *string;
    struct node *next;
};

struct node *sortedDirectory = NULL;

char *toLowercase(
    char *string,
    int length)
{
    char *newString = (char *)calloc(length, sizeof(char));
    for (int i = 0; string[i] != '\0'; i++)
    {
        newString[i] = tolower(string[i]);
    }
    return newString;
}

void sorted_insert(
    char *str

)
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->string = (char *)calloc(256, sizeof(char));
    if (strlen(str) > 0)
        strcpy(newNode->string, str);
    // str;

    if (sortedDirectory == NULL)
    {
        newNode->next = sortedDirectory;
        sortedDirectory = newNode;
    }
    else
    {
        char *cmp1 = toLowercase(newNode->string, 256);
        char *cmp2 = toLowercase(sortedDirectory->string, 256);
        int compareVal = strcmp(cmp1, cmp2);

        if (compareVal < 0)
        {
            newNode->next = sortedDirectory;
            sortedDirectory = newNode;
        }
        else
        {
            struct node *ptr = sortedDirectory;
            struct node *prev = sortedDirectory;

            while (ptr->next != NULL && compareVal >= 0)
            {
                prev = ptr;
                ptr = ptr->next;

                free(cmp2);
                cmp2 = toLowercase(ptr->string, 256);
                compareVal = strcmp(cmp1, cmp2);
            }
            if (compareVal < 0)
            {
                newNode->next = prev->next;
                prev->next = newNode;
            }
            else
            {
                ptr->next = newNode;
                newNode->next = NULL;
            }
        }

        free(cmp1);
        free(cmp2);
    }
}

void printDetails(char *longFormat, char *filename)
{
    if (strcmp(longFormat, "-l") == 0)
    {
        struct stat fileStat;
        if (stat(filename, &fileStat) < 0)
            return;
        printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
        printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
        printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
        printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
        printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
        printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
        printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
        printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
        printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
        printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");

        printf(" ");
        struct passwd *pwd;
        if ((pwd = getpwuid(fileStat.st_uid)) != NULL)
            printf("%s ", pwd->pw_name);
        else
            printf("%d ", fileStat.st_uid);

        struct group *grp;
        if ((grp = getgrgid(fileStat.st_gid)) != NULL)
            printf("%s ", grp->gr_name);
        else
            printf("%d ", fileStat.st_gid);

        printf("%ld ", fileStat.st_size);

        struct timespec modifiedTime;
        modifiedTime = fileStat.st_mtim;
        struct tm *my_tm = localtime(&modifiedTime.tv_sec);
        char formattedTime[256];
        strftime(formattedTime, 256, "%b %d %H:%M", my_tm);

        printf("%s ", formattedTime);
    }
}

int main(int argc, char **argv)
{
    struct dirent *dir = NULL;
    DIR *dirp = opendir(".");
    errno = 0;
    char *filename;
    while ((dir = readdir(dirp)) != NULL)
    {
        if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
            continue;
        filename = calloc(256, sizeof(char));
        strcpy(filename, dir->d_name);
        sorted_insert(filename);
        free(filename);
    }
    if (errno)
    {
        printf("error!");
    }
    closedir(dirp);
    free(dir);
    char *longFormat;
    if (argc > 1)
    {
        longFormat = argv[1];
    }
    else
    {
        longFormat = "0";
    }
    while (sortedDirectory != NULL)
    {
        printDetails(longFormat, sortedDirectory->string);
        printf("%s\n", sortedDirectory->string);
        struct node *tempNode = sortedDirectory;
        sortedDirectory = sortedDirectory->next;
        free(tempNode->string);
        free(tempNode);
    }
}