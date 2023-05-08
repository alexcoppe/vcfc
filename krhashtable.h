#include <string.h> 
#include <stdlib.h>
#include <stdio.h>

#define HASHSIZE 101


struct info_fields_hasht {
    struct info_fields_hasht *next;
    char *key;
    char *value;
};

void print_info_fields_hasht(struct info_fields_hasht *);

unsigned hash(char *);

struct info_fields_hasht *lookup(char *key, struct info_fields_hasht **);

struct info_fields_hasht *install(char *key, char *value, struct info_fields_hasht **);
