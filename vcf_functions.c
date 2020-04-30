#include <string.h>  /* strcpy */
#include <stdlib.h>  /* malloc */
#include <stdio.h>   /* printf */


int compare_ints(const void *a, const void *b) {
    int first = *(int *) a;
    int second = *(int *) b;
    int returned_value = first - second;
    return returned_value;
}


int *sorted_int_array_from_str(char *s) {
    char *x;
    char dst[100];
    static int int_array[100] = {0};
    size_t l = (size_t) strlen(s);
    char *tok;
    int index;
    int i = 0;

    x = strncpy(dst, s, l);
    tok = strtok(dst, ",");

    while (tok != NULL) {
        index = atoi(tok);
        int_array[i] = index;
        tok = strtok(NULL, ",");
        i++;
    }


    qsort(int_array, 100, sizeof(int), compare_ints);

    return int_array;
}


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


