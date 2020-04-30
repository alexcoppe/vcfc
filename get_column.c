#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<getopt.h>
#include<ctype.h>
#include "vcf_functions.h"

int main(int argc, char *argv[]){
    char *line = NULL;
    FILE *f = NULL;
    ssize_t read = 0;
    size_t n = 0;
    char c;
    int hflag = 1;
    char *nflag = NULL;
    char *column = NULL;
    int col_number = 0;

    /**//* Help string */
    char help[] = "Usage: get_pass_variants [OPTION]... VCF_file\n  "
        "-h\tshow help options";

    while ((c = getopt (argc, argv, "hn:")) != -1)
        switch (c) {
            case 'h':
                puts(help);
                return 1;
            case 'n':
                col_number = atoi(optarg);
                break;
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


    /* Check if there is a file argument */
    if (argc < 1) {
        fprintf(stderr, "File name not specified\n");
        return -1;
    }

    /*If the file is not present */
    if (!(f = fopen(argv[0], "r"))) {
        fprintf(stderr, "Coud not find file: %s\n", argv[0]);
        return 1;
    }



    while ((read = getline(&line, &n, f)) != -1) {
        column = get_column(line, col_number);
        if (column != NULL && column != "") {
            printf("%s\n", column);
            free(column);
        }
    }

    free(line);
    fclose(f);
    exit(EXIT_SUCCESS);
}