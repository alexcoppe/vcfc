#include<stdio.h>
#include<stdlib.h>
#include <string.h>


char *get_vcf_field(char *line, int field) {
    char *token = NULL;
    int token_number = 0;
    if (line[0] != '#') {
        while ((token = strtok_r(line, "\t", &line))) {
            if (token_number == field) {
                return token;
            }
            token_number++;
        }
    }

    return token;
}
