#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"get_vcf_field.h"
#include<getopt.h>
#include<ctype.h>


int main(int argc, char *argv[]){
    char *line;
    char *line_to_be_printed;
    size_t len = 0;    
    FILE *vcf;
    ssize_t read;    
    char *field;
    char c;
    int hflag = 0;
    int aflag = 0;
    int bflag = 0;
    char *sflag = NULL;

    /* Help string */
    char help[] = "Usage: get_pass_variants [OPTION]... VCF_file\n  "
        "-h\tshow help options";

    while ((c = getopt (argc, argv, "h")) != -1)
        switch (c) {
            case 'h':
                hflag = 1;
                puts(help);
                return 1;
            case '?':
                if (isprint(optopt))
                    fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
                return 1;
            default:
                abort();
        }

    argc -= optind;
    argv += optind;


    /* Check if there is a VCF file argument */
    if (argc < 1) {
        fprintf(stderr, "VCF file name not specified\n");
        return -1;
    }

    /*If the VCF file is not present */
    if (!(vcf = fopen(argv[0], "r"))) {
        fprintf(stderr, "Coud not find file: %s\n", argv[0]);
        return 1;
    }

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

    return 1;
}
