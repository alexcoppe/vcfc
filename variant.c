#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"vcf_functions.c"
#include"variant.h"

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


    /*free(variant->snpeffann);*/
    /*Snpeff_ANN *i = variant->snpeffann;*/
    /*Snpeff_ANN *next = NULL;*/
    /*reset_Snpeff_ANN(variant->snpeffann);*/

    /*while (i->next != NULL){*/
        /*next = i->next;*/
        /*free(i);*/
        /*i = next;*/
        /*i = i->next;*/
    /*}*/

    for (int i = 0; i < 100; i++){
        if (variant->samples[i]) {
            free(variant->samples[i]);
        }
    }
    
    /*while (i != NULL){*/
    /*next = i->next;*/
    /*free(i);*/
    /*i = next;*/
    /*}*/

    /*free(next);*/

    free(variant);
}

char **get_format_fields(char *format){
    size_t l = strlen(format) + 2;
    char *copied_format = (char *) malloc(l);
    char *ptr = NULL;
    int i = 0;
    char *subfield = NULL;

    char **returned_list = (char **) malloc(10 * sizeof(char *));

    for (int i = 0; i < 10; i++)
        returned_list[i] = NULL;


    /* Use strlcpy insteed of strncpy because is more secure */
    strlcpy(copied_format, format, l);

    // If the delimiter is found in the string
    if (strstr(copied_format, ":") != NULL) {
        ptr = strtok(copied_format, ":");
        while (ptr != NULL) {
            subfield = (char *) malloc(strlen(ptr) + 1);
            strlcpy(subfield, ptr, strlen(ptr) + 1);
            returned_list[i] = subfield;
            ptr = strtok(NULL, ":");
            if (i == 9)
                break;
            i++;
        }
    } else {
        exit(EXIT_FAILURE);
    }

    free(copied_format);

    return returned_list;
}


int number_of_format_fields(char **format_fields){
    int i = 0;
    int number_of_fields = 0;
    while (format_fields[i]){
        number_of_fields++;
        i++;
    }
    return number_of_fields;
}

void delete_format_fields(char **format_fields){
   for (int el = 0; el < 10; el++) {
       free(format_fields[el]);
       format_fields[el] = NULL;
   }
   free(format_fields);
}

int n_of_samples(Variant *var){
    int number_of_samples = 0;
    while (number_of_samples < 100){
        if (var->samples[number_of_samples] == NULL)
            break;
        else {
            number_of_samples++;
        }
    }
    return number_of_samples;
}

void print_samples_info(Variant *var){
    char **format_fields;
    char **sample;
    int n =  n_of_samples(var);
    format_fields = get_format_fields(var->format);
    int n_format_fields =  number_of_format_fields(format_fields);
    for (int i = 0; i < n_format_fields; i++){
        printf("%s ", format_fields[i]);
        for (int j = 0; j < n; j++){
            sample = get_format_fields(var->samples[j]);
            printf("%s ", sample[i]);
            delete_format_fields(sample);
        }
        puts("");
    }
    delete_format_fields(format_fields);
}

void get_info_field(char *info, struct info_fields_hasht **damnhash){
    size_t l = strlen(info) + 2;
    char *copied_info = (char *) malloc(l);
    char *ptr = NULL;
    char *subfield = NULL;
    char *key = NULL;
    char *value = NULL;
    int i = 0;
    int number_of_equals = 0;

    /* Use strlcpy insteed of strncpy because is more secure */
    strlcpy(copied_info, info, l);

    char *end_token = NULL;
    char *token2 = NULL;
    char *end_token2 = NULL;
    int equal_side = 0;
    char *sub_token2 = NULL;
    char *subfield2 = NULL;
    
    // If the delimiter is found in the string
    if (strstr(copied_info, ";") != NULL) {
        ptr = strtok_r(copied_info, ";", &end_token);
        while (ptr != NULL) {
            subfield = (char *) malloc(strlen(ptr) + 1);
            strlcpy(subfield, ptr, strlen(ptr) + 1);

            number_of_equals = 0;
            for (int i = 0; i < strlen(subfield); i++)
                if (subfield[i] == '=')
                    number_of_equals++;

            if (number_of_equals == 0){
                key = (char *) malloc(strlen(subfield) + 1);
                strlcpy(key, subfield, strlen(subfield) + 1);
                value = (char *) malloc(strlen(subfield) + 1);
                strlcpy(value, subfield, strlen(subfield) + 1);
            }  else if (number_of_equals == 1){
                equal_side = 0;
                token2 = strtok_r(ptr, "=", &end_token2);
                while (token2 != NULL){
                    subfield2 = (char *) malloc(strlen(token2) + 1);
                    strlcpy(subfield2, token2, strlen(token2) + 1);
                    if (equal_side == 0 ){
                        key = (char *) malloc(strlen(subfield2) + 1);
                        strlcpy(key, token2, strlen(subfield2) + 1);
                    } else if (equal_side == 1){
                        value = (char *) malloc(strlen(subfield2) + 1);
                        strlcpy(value, token2, strlen(subfield2) + 1);
                    }
                    equal_side++;

                    token2 = strtok_r(NULL, "=", &end_token2);
                    free(subfield2);
                }
            }
            install(key, value, damnhash);
            free(value);
            free(key);

            ptr = strtok_r(NULL, ";", &end_token);
            free(subfield);
        }
    }

    free(ptr);
    free(copied_info);
}

