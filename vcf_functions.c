#include <string.h>  /* strcpy */
#include <stdlib.h>  /* malloc */
#include <stdio.h>   /* printf */
#include "vcf_functions.h"
#include <search.h>


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
        if (index < 100)
            int_array[i] = index;
        else
            int_array[i] = 0;
        tok = strtok(NULL, ",");
        i++;
    }


    /*qsort(int_array, 100, sizeof(int), compare_ints);*/

    return int_array;
}


char *get_column(const char *line, const int n, const char *delimiter_char) {
    size_t l = strlen(line) + 3;
    char *copied_line = (char *) malloc(l);
    char *returned_line = NULL;
    const char *delim = delimiter_char;
    int colum_done = 0;
    char *ptr = NULL;
    

    strncpy(copied_line, line, l);

    // If the delimiter is found in the string
    if (strstr(copied_line, delim) != NULL) {
        ptr = strtok(copied_line, delim);
        
        while (ptr != NULL) {
            if (colum_done == n - 1)
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
        return NULL;
    }


    returned_line = (char *) malloc(strlen(ptr) + 1);
    strcpy(returned_line, ptr);

    free(copied_line);

    // Remove the \n if it returns the last word
    returned_line[strcspn(returned_line, "\n")] = 0;

    return returned_line;
}


char **get_columns(const char *line, const char *delimiter_char) {
    size_t l = strlen(line) + 2;
    char *copied_line = (char *) malloc(l);
    char *returned_line = NULL;
    const char *delim = delimiter_char;
    int colum_done = 0;
    char *ptr = NULL;
    int i = 0;

    static char *returned_list[100] = {NULL};

    /* Use strlcpy insteed of strncpy because is more secure */
    strlcpy(copied_line, line, l);

    // If the delimiter is found in the string
    if (strstr(copied_line, delim) != NULL) {
        ptr = strtok(copied_line, delim);
        
        while (ptr != NULL) {
            returned_line = (char *) malloc(strlen(ptr) + 1);
            strlcpy(returned_line, ptr, strlen(ptr) + 1);
            returned_line[strcspn(returned_line, "\n")] = 0;
            returned_list[i] = returned_line;
            ptr = strtok(NULL, delim);
            if (i == 99)
                break;
            i++;
        }
    } else
        exit(EXIT_FAILURE);

    free(copied_line);

    return returned_list;
}


void delete_columns(char **columns){
    for (int i = 0; i < 100; i++)
        free(columns[i]);
}
