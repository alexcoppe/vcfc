#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "vcf_functions.c"
#include "variant.h"


void nice_print_variant(Variant *variant){
    printf("CHROM: %s\n", variant->chrom);
    printf("POS: %i\n", variant->pos);
    printf("ID: %s\n", variant->id);
    printf("REF: %s\n", variant->ref);
    printf("ALT: %s\n", variant->alt);
    printf("QUAL: %i\n", variant->qual);
    printf("FILTER: %s\n", variant->filter);
    printf("INFO: %s\n", variant->info);
    printf("FORMAT: %s\n", variant->format);
    printf("SAMPLES: ");
    for (int i = 0; i < 89; i++) {
        if (variant->samples[i])
            printf("%s ", variant->samples[i]);
    }
    puts("");
}

Variant *get_variant_from_vcf_line(char *vcf_line){
    Variant *snp = malloc(sizeof(Variant));
    char **row_fields;
    row_fields = get_columns(vcf_line, "\t");
    /*static char *samples[100] = {NULL};*/
    static char *samples[100];
    for (int i = 0; i < 100; i++)
        samples[i] = NULL;
    int n_sample = 0;
    long int len = 0;

    snp->chrom = strdup(row_fields[0]);
    snp->pos = atoi(row_fields[1]);
    snp->id = strdup(row_fields[2]);
    snp->ref = strdup(row_fields[3]);
    snp->alt = strdup(row_fields[4]);

    if (row_fields[5] == ".")
        snp->qual = -1;
    else
        snp->qual = atoi(row_fields[5]);

    snp->filter = strdup(row_fields[6]);
    snp->info = strdup(row_fields[7]);
    snp->format = strdup(row_fields[8]);

    for (int i = 0; i < 100; i++)
        snp->samples[i] = NULL;

    const int novalue = -1;
    for (int i = 9; i < 100; i++) {
        if (row_fields[i] == NULL) {
            break;
        }
        len = strlen(row_fields[i]);
        snp->samples[n_sample] = malloc(len + 1);
        strcpy(snp->samples[n_sample], row_fields[i]);
        

        n_sample += 1;
    }

    delete_columns(row_fields);

    return snp;
}


void free_variant(Variant *variant) {
    free(variant->chrom);
    free(variant->id);
    free(variant->ref);
    free(variant->alt);
    free(variant->filter);
    free(variant->info);
    free(variant->format);
    for (int i = 0; i < 100; i++){
        if (variant->samples[i]) {
            free(variant->samples[i]);
        }
    }
    
    free(variant);
}

