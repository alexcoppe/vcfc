#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "bed.h"
#include<getopt.h>

int main(int argc, char *argv[]){
    BedEntry *wanted_ranges = {NULL};
    int i = 0;
    ssize_t read;
    char *line = NULL;
    size_t len = 0;
    FILE *file = NULL;
    char chromosome[20];
    int position;
    int opt;
    int header = 0;

    char help[] = "Usage: filter_vcf_by_bed [OPTION]... BED_file VCF_file\n  "
        "-h\tshow help options\n  "
        "-a\tshow the header in the filtered VCF";

    while ((opt = getopt(argc, argv, "ah")) != -1){
        switch (opt){
            case 'h':
                puts(help);
                return 1;
            case 'a':
                header = 1;
                break;
            case '?':
                printf("Unknown option: %c\n", optopt);
                break;
            case ':':
                printf("Missing arg for %c\n", optopt);
                break;
        }
    }

    argc -= optind;
    argv += optind;

    if (argc < 1) {
        fprintf(stderr, "BED file not specified\n");
        return -1;
    }

    if (argc < 2) {
        fprintf(stderr, "VCF file not specified\n");
        return -1;
    }

    if (!(file = fopen(argv[0], "r"))) { 
        fprintf(stderr, "Could not find BED file: %s\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (!(file = fopen(argv[1], "r"))) { 
        fprintf(stderr, "Could not find VCF file: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    wanted_ranges = bed_entries(argv[0]);

    while ((read = getline(&line, &len, file)) != -1) {
        if (line[0] == '#'){
            if (header != 0){
                printf("%s", line);
            }
            continue;
        }
        sscanf(line, "%s %i", chromosome, &position);
        i = 0;
        while (wanted_ranges[i].chromosome[0]){
            if (strcmp(wanted_ranges[i].chromosome, chromosome) == 0){
                if (position > wanted_ranges[i].start && position < wanted_ranges[i].end){
                    /*printf("%d %s %d\n", position,  wanted_ranges[i].chromosome, wanted_ranges[i].start);*/
                    printf("%s", line);
                }
            }
            i++;
        }
    }

    free(wanted_ranges);
    free(line);

    return 0;
}
