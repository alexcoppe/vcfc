#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "bed.h"

int main(int argc, char *argv[]){
    BedEntry *wanted_ranges = {NULL};
    int i = 0;
    char c;
    ssize_t read;
    char *line = NULL;
    size_t len = 0;
    FILE *file = NULL;
    char chromosome[10];
    int position;

    if (!(file = fopen(argv[2], "r"))) { 
        fprintf(stderr, "Coud not find file: %s\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    wanted_ranges = bed_entries(argv[1]);

    while ((read = getline(&line, &len, file)) != -1) {
        if (line[0] == '#')
            continue;
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
