#include "variant.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[]){
    char *line = NULL;
    FILE *file = NULL;
    ssize_t read;
    size_t len = 0;
    char **row_fields;
    char **format_fields;
    struct info_fields_hasht *AN_ASJ = NULL;
    struct info_fields_hasht *dbNSFP_FATHMM_pred = NULL;
    struct info_fields_hasht *BayesDel_addAF_rankscore = NULL;
    struct info_fields_hasht *MPOS = NULL;
    struct info_fields_hasht *ANN = NULL;

    Variant *var;

    static struct info_fields_hasht *damnhash[HASHSIZE];

    if (!(file = fopen(argv[1], "r"))) { 
        fprintf(stderr, "Coud not find file: %s\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, file)) != -1) {
        if (line[0] == '#')
            continue;
        var = get_variant_from_vcf_line(line);
        format_fields = get_format_fields(var->format);

        char **sample = get_format_fields(var->samples[0]);

        get_info_field(var->info, damnhash);

        AN_ASJ = lookup("AN_ASJ", damnhash);
        if (AN_ASJ != NULL)
            printf("%s\t%s\n", AN_ASJ->key, AN_ASJ->value);

        dbNSFP_FATHMM_pred = lookup("dbNSFP_FATHMM_pred", damnhash);
        if (dbNSFP_FATHMM_pred != NULL)
            printf("%s\t%s\n", dbNSFP_FATHMM_pred->key, dbNSFP_FATHMM_pred->value);

        BayesDel_addAF_rankscore = lookup("BayesDel_addAF_rankscore", damnhash);
        if (BayesDel_addAF_rankscore != NULL)
            printf("%s\t%s\n", BayesDel_addAF_rankscore->key, BayesDel_addAF_rankscore->value);

        MPOS = lookup("MPOS", damnhash);
        if (MPOS != NULL)
            printf("%s\t%s\n", MPOS->key, MPOS->value);

        ANN = lookup("ANN", damnhash);
        if (ANN != NULL)
            printf("%s\t%s\n", ANN->key, ANN->value);


        delete_format_fields(format_fields);
        delete_format_fields(sample);

        free_variant(var);
    }

    free(line);

    return 0;
}
