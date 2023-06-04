#include <string.h> 
#include <stdlib.h>
#include <stdio.h>
#include "snpeff.h"
#include "variant.h"

int main(int argc, char *argv[]){
    char *line = NULL;
    FILE *file = NULL;
    ssize_t read;
    size_t len = 0;
    char **format_fields;
    struct info_fields_hasht *ANN = NULL;
    size_t l = 0;
    char *copied_format = NULL;
    char *ptr = NULL;
    int i = 1;
    char *subfield = NULL;
    Snpeff_ANN annotation;

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

        get_info_field(var->info, damnhash);
        ANN = lookup("ANN", damnhash);
        if (ANN != NULL){
            l = strlen(ANN->value) + 2;

            /* Use strlcpy insteed of strncpy because is more secure */
            copied_format = (char *) malloc(l);
            strlcpy(copied_format, ANN->value, l);
            // If the delimiter is found in the string
            if (strstr(copied_format, ",") != NULL) {
                ptr = strtok(copied_format, ",");
                while (ptr != NULL) {
                    subfield = (char *) malloc(strlen(ptr) + 2);
                    strlcpy(subfield, ptr, strlen(ptr) + 2);
                    ptr = strtok(NULL, ",");
                    annotation = get_snpeff_annotation_field(subfield);
                    show_snpeff_annotation_field(annotation);
                    printf("%s %d\n", var->chrom, var->pos);
                    free(subfield);
                    if (i == 14)
                        break;
                    i++;
                }
            }
            free(copied_format);
        }

        free_variant(var);
    }

    free(line);

    return 0;
}
