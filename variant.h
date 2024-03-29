#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"krhashtable.h"

#ifndef SNPEFF_H
#define SNPEFF_H

typedef struct Variant {
    char *chrom;
    int pos;
    char *id;
    char *ref;
    char *alt;
    int qual;
    char *filter;
    char *info;
    char *format;
    char *samples[100];
    int n_samples;

    struct info_fields_hasht *hashtab[HASHSIZE];

    struct Snpeff_ANN *snpeffann;
} Variant;

#endif

void nice_print_variant(Variant *);

Variant *get_variant_from_vcf_line(char *);

void free_variant(Variant *);

char **get_format_fields(char *);

int number_of_format_fields(char **);

void delete_format_fields(char **);

int n_of_samples(Variant *);

void print_samples_info(Variant *);

void get_info_field(char *, struct info_fields_hasht **);
