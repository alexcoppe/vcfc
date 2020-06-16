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
    char *column = NULL;
    int *col_numbers;
    int col_number;
    char *delimiter = NULL;
    char **row_fields;
    int row_fields_position;

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
        row_fields = get_columns(line, delimiter);

        for (col_number = 0; col_number < 99; col_number++) {
            row_fields_position = col_numbers[col_number];
            if (row_fields_position >= 1){
                column = row_fields[row_fields_position - 1];
                if (column != NULL) {
                    printf("%s\t", column);
                }
            }
        }
        printf("\n");

        for (int el = 0; el <= 100; el++) {
            free(row_fields[el]);
        }
    }

    fclose(f);
    exit(EXIT_SUCCESS);
}
