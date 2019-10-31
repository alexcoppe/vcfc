#include<stdio.h>
#include<stdlib.h>
#include <string.h>

enum fields {CHROM, POS, ID, REF, ALT, QUAL, FILTER, INFO, FORMAT};

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


int main(int argc, char *argv[]){
    char *line;
    size_t len = 0;    
    FILE *vcf;
    ssize_t read;    
    char *field;

    vcf = fopen(argv[1], "r");

    while ((read = getline(&line, &len, vcf) ) != -1) {
        if (line[0] != '#') {
            field = get_vcf_field(line, INFO);
            printf("%s\n", field);
        }
    }
}
