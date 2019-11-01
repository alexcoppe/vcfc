#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"get_vcf_field.h"

int main(int argc, char *argv[]){
    char *line;
    char *line_to_be_printed;
    size_t len = 0;    
    FILE *vcf;
    ssize_t read;    
    char *field;

    vcf = fopen(argv[1], "r");

    while ((read = getline(&line, &len, vcf) ) != -1) {
        if (line[0] != '#') {
            line_to_be_printed = (char *) malloc(strlen(line));
            strcpy(line_to_be_printed, line);
            field = get_vcf_field(line, FILTER);
            if (strcmp(field, "PASS") == 0) {
                fprintf(stdout, "%s", line_to_be_printed);                
            }
            free(line_to_be_printed);
        }
        else {
            fprintf(stdout, "%s", line);                
        }
    }
}
