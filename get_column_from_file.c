
#include <stdio.h>
#include <stdlib.h>
#include<string.h>


int main(int argc, char *argv[]){
    FILE *file = NULL;
    char *line = NULL;
    size_t len = 0;    
    size_t read = 0;
    char *column = NULL;
    char *copied_line = NULL;
    char *token;
    int field_number = 0;
    int wanted_field = 1;
    char *contains_new_line = NULL;
    char *subtoken = NULL;

    /*If the ids file is not present */
    if (!(file = fopen(argv[1], "r"))) {
        fprintf(stderr, "Coud not find file: %s\n", argv[0]);
        return 1;
    }

    while ((read = getline(&line, &len, file) ) != -1) {
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

        free(copied_line);
    }
    free(line);

    return 0;
}
