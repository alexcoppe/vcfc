#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
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
} Variant;

void nice_print_variant(Variant *);

Variant *get_variant_from_vcf_line(char *);

void free_variant(Variant *);
