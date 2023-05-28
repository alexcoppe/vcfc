#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct {
    char chromosome[20];
    int start;
    int end;
} BedEntry;

void printBedEntry(BedEntry );

BedEntry *bed_entries(char *);
