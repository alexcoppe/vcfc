#include<stdio.h>
#include<stdlib.h>
#include <string.h>


char *get_vcf_field(char *line, int field) {
    char *token;
    int token_number = 0;
    if (line[0] != '#') {
        token = strtok(line, "\t");
        while (token != NULL) {
            if (token_number == field) {
                return token;
            }
            token = strtok(NULL, "\t");
            token_number++;
        }
    }
    return NULL;
}
