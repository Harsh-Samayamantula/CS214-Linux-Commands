#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
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

typedef struct node
{
    char *name;
    int is_dir;
    struct node *next;
} node;

void tree(const char *directory, const char *prefix)
{
    node *alpha = NULL;
    node *curr;
    node *temp;
    int size = 0;
    int index;

    struct dirent *dr;
    DIR *de;

    char *next_prefix;

    de = opendir(directory);
    if (!de)
    {
        printf("Error opening directory");
        return;
    }
    while ((dr = readdir(de)) != NULL)
    {
        if (dr->d_name[0] != '.')
        {
            curr = malloc(sizeof(node));
            curr->name = strcpy(malloc(257), dr->d_name);

            curr->next = NULL;
            curr->is_dir = dr->d_type == DT_DIR;

            if (alpha == NULL)
            {
                alpha = curr;
            }
            else
            {
                char *cmp1 = toLowercase(curr->name, 256);
                char *cmp2 = toLowercase(alpha->name, 256);
                if (strcmp(cmp1, cmp2) < 0)
                {
                    curr->next = alpha;
                    alpha = curr;
                    free(cmp1);
                    free(cmp2);
                }
                else
                {
                    temp = alpha;
                    free(cmp1);
                    free(cmp2);
                    while (temp->next)
                    {
                        cmp1 = toLowercase(temp->next->name, 256);
                        cmp2 = toLowercase(curr->name, 256);
                        if (strcmp(cmp1, cmp2) >= 0)
                        {
                            free(cmp1);
                            free(cmp2);
                            break;
                        }

                        temp = temp->next;
                        free(cmp1);
                        free(cmp2);
                    }

                    curr->next = temp->next;
                    temp->next = curr;
                }
            }
            size++;
        }
    }

    closedir(de);

    char *full_path;
    for (index = 0; index < size; index++)
    {

        printf("%s%s%s\n", prefix, "- ", alpha->name);

        if (alpha->is_dir)
        {
            full_path = malloc(strlen(directory) + strlen(alpha->name) + 2);
            sprintf(full_path, "%s/%s", directory, alpha->name);

            next_prefix = malloc(strlen(prefix) + strlen("- ") + 1);
            sprintf(next_prefix, "%s%s", prefix, "  ");

            tree(full_path, next_prefix);
            free(full_path);
            free(next_prefix);
        }

        curr = alpha;
        alpha = alpha->next;

        free(curr->name);
        free(curr);
    }
}

int main(int argc, char *argv[])
{

    printf(".\n");
    tree(".", "");
    return 0;
}