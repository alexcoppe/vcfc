#include<stdio.h>
#include<stdlib.h>
#include<string.h>

enum fields {CHROM, POS, ID, REF, ALT, QUAL, FILTER, INFO, FORMAT};

char *get_vcf_field(char *, int);
 
