#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "bed.h"

#define MAX_LINE_LENGTH 10000


void printBedEntry(BedEntry be){
    printf("%s\t%d\t%d\n", be.chromosome, be.start, be.end);
}

BedEntry *bed_entries(char *file_path){
    FILE *file = NULL;
    ssize_t read;
    size_t len = 0;
    int number_of_chars_in_line = 0;
    int number_of_separators = 0;
    char separatpr;
    char line[MAX_LINE_LENGTH];
    BedEntry *bedEntries = NULL;
    int numEntries = 0;
    int i;

    if (!(file = fopen(file_path, "r"))) { 
        fprintf(stderr, "Coud not find file: %s\n", file_path);
        exit(EXIT_FAILURE);
    }
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        number_of_chars_in_line = strlen(line);
        for (int i = 0; i < number_of_chars_in_line; i++){
            if (line[i] == '\t' | line[i] == ' '){
                number_of_separators++;
                if (number_of_separators == 2){
                    separatpr = line[i];
                    break;
                }
            }
        }
        if (number_of_separators < 2){
            fprintf(stderr, "The %s is not a bed file\n", file_path);
            exit(EXIT_FAILURE);
        }
        number_of_separators = 0;

        BedEntry entry;

        sscanf(line, "%s %d %d", entry.chromosome, &entry.start, &entry.end);

        numEntries++;
        bedEntries = (BedEntry *)realloc(bedEntries, numEntries * sizeof(BedEntry));
        bedEntries[numEntries - 1] = entry;
    }

    fclose(file);

    return bedEntries;
}


