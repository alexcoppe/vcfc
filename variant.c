#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "vcf_functions.c"
#include "variant.h"

/*typedef struct {*/
/*char *chrom;*/
/*int pos;*/
/*char *id;*/
/*char *ref;*/
/*char *alt;*/
/*int qual;*/
/*char *filter;*/
/*char *info;*/
/*char *format;*/
/*char *samples[100];*/
/*int n_samples;*/
/*} Variant;*/

void print_variant(Variant *variant){
    printf("%s\t%i\t%s\t%s\t%s\t%i\t%s\t%s\n", variant->chrom, variant->pos, variant->id, variant->ref, variant->alt, variant->qual, variant->filter, variant->format);
}


void nice_print_variant(Variant *variant){
    puts("==============================");
    printf("CHROM: %s\n", variant->chrom);
    printf("POS: %i\n", variant->pos);
    printf("ID: %s\n", variant->id);
    printf("REF: %s\n", variant->ref);
    printf("ALT: %s\n", variant->alt);
    printf("QUAL: %i\n", variant->qual);
    printf("FILTER: %s\n", variant->filter);
    printf("INFO: %s\n", variant->info);
    printf("FORMAT: %s\n", variant->format);
    int number_of_samples = variant->n_samples;
    for (int i = 0; i < number_of_samples; i++)
        printf("SAMPLE %i %s\n", i + 1, variant->samples[i]);
    puts("\n");
}

Variant *get_variant_from_vcf_line(char *vcf_line){
    Variant *snp = malloc(sizeof(Variant));
    char **row_fields;
    row_fields = get_columns(vcf_line, "\t");
    static char *samples[100] = {NULL};
    int n_sample = 0;

    snp->chrom = row_fields[0];
    snp->pos = atoi(row_fields[1]);
    snp->id = row_fields[2];
    snp->ref = row_fields[3];
    snp->alt = row_fields[4];

    if (row_fields[5] == ".")
        snp->qual = -1;
    else
        snp->qual = atoi(row_fields[5]);

    snp->filter = row_fields[6];
    snp->info = row_fields[7];
    snp->format = row_fields[8];

    const int novalue = -1;
    for (int i = 9; i < 100; i++) {
        if (row_fields[i] == NULL) {
            break;
        }
        samples[n_sample] = row_fields[i];
        snp->samples[n_sample] = row_fields[i];
        n_sample += 1;
    }

    snp->n_samples = n_sample;

    return snp;
}


//int main(int argc, char *argv[]){
//    char *line = NULL;
//    FILE *file = NULL;
//    ssize_t read;
//    size_t len = 0;
//    char **row_fields;

//    Variant *var;

//    if (!(file = fopen(argv[1], "r"))) { 
//        fprintf(stderr, "Coud not find file: %s\n", argv[0]);
//        exit(EXIT_FAILURE);
//    }

//    while ((read = getline(&line, &len, file)) != -1) {
//        if (line[0] == '#')
//            continue;
//         var = get_variant_from_vcf_line(line);
//         /*print_variant(var);*/
//         nice_print_variant(var);
//    }
//
//    free(var);
//
//    return 0;
//}
