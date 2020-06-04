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
    int *col_numbers;
    int col_number;
    int found_column;
    char *delimiter = NULL;

    /**//* Help string */
    char help[] = "Usage: get_pass_variants [OPTION]... VCF_file\n  "
        "-h\tshow help options\n  "
        "-d\tthe field delimiter to use instead of the tab character\n  "
        "-f\tthe fields to be shown (separated by ,)";

    while ((c = getopt (argc, argv, ":hd:f:")) != -1)
        switch (c) {
            case 'h':
                puts(help);
                return 1;
            case 'f':
                /*col_number = atoi(optarg);*/
                col_numbers = sorted_int_array_from_str(optarg);
                break;
            case 'd':
                delimiter = optarg;
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


    /* Check if a delimiter is given */
    if (delimiter == NULL)
        delimiter = "\t";


    while ((read = getline(&line, &n, f)) != -1) {
        found_column = 0;
        for (col_number = 0; col_number < 100; col_number++) {
            if (col_numbers[col_number] > 0){
                /*column = get_column(line, col_numbers[col_number], "\t");*/
                column = get_column(line, col_numbers[col_number], delimiter);
                if (column != NULL && column != "") {
                    found_column = 1;
                    printf("%s\t", column);
                }
                free(column);
            }
        }
        if (found_column == 1)
            puts("");

    }

    free(line);
    fclose(f);
    exit(EXIT_SUCCESS);
}
