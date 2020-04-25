#include <string.h>  /* strcpy */
#include <stdlib.h>  /* malloc */
#include <stdio.h>   /* printf */


char *get_column(const char *line, const int n) {
    size_t l = strlen(line) + 2;
    char *copied_line = (char *) malloc(l);
    char *returned_line = NULL;
    char *delim = "\t";
    int colum_done = 0;
    char *ptr = NULL;

    strncpy(copied_line, line, l);

    // If the delimiter is found in the string
    if (strstr(copied_line, delim) != NULL) {
        ptr = strtok(copied_line, delim);
        
        while (ptr != NULL) {
            if (colum_done == n)
                break;
            ptr = strtok(NULL, delim);
            colum_done++;
        }
    } 

    else {
        free(copied_line);
        return NULL;
    }

    if (ptr == NULL) {
        free(copied_line);
        return "";
    }


    returned_line = (char *) malloc(strlen(ptr));
    strcpy(returned_line, ptr);

    free(copied_line);

    // Remove the \n if it returns the last word
    returned_line[strcspn(returned_line, "\n")] = 0;

    return returned_line;
}


