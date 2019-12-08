
#include <stdio.h>
#include <stdlib.h>
#include<string.h>


char *get_column_from_line(char *line, int column_number) {
    char *copied_line = NULL;
    int field_number = 0;
    char *column = NULL;
    char *subtoken = NULL;
    int wanted_field = column_number;

    copied_line = (char *) malloc((int) strlen(line));
    strncpy(copied_line, line, strlen(line) + 1);
    field_number = 0;
    column = strtok(copied_line, "\t");
    subtoken = column;
    if (subtoken[strlen(subtoken) - 1] == '\n')
        subtoken[strlen(subtoken) - 1] = '\0';

    while (column != NULL) {
        if (subtoken == NULL) {
            break;
        }
        else if (field_number == wanted_field) {
            if (subtoken[strlen(subtoken) - 1] == '\n')
                subtoken[strlen(subtoken) - 1] = '\0';
            printf("%s\n", subtoken);
        }

        subtoken = strtok(NULL, "\t");
        field_number++;

    }
    return copied_line;
}

int main(int argc, char *argv[]){
    FILE *file = NULL;
    char *line = NULL;
    size_t len = 0;    
    size_t read = 0;

    /*If the ids file is not present */
    if (!(file = fopen(argv[1], "r"))) {
        fprintf(stderr, "Coud not find file: %s\n", argv[0]);
        return 1;
    }

    char *wanted_column = NULL;
    while ((read = getline(&line, &len, file) ) != -1) {
        wanted_column = get_column_from_line(line, 2);
        free(wanted_column);
    }
    free(line);

    return 0;
}
