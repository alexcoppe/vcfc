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

    Variant *var;

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

        /*printf("%s %i %s %s\n", var->chrom, var->pos, var->ref, var->alt);;*/
        /*print_samples_info(var);*/
        /*puts("");*/

        /*int number_of_samples = 0;*/
        /*while (number_of_samples < 100){*/
        /*if (var->samples[number_of_samples] == NULL)*/
        /*break;*/
        /*else {*/
        /*number_of_samples++;*/
        /*}*/
        /*}*/
        /*printf("%d\n", number_of_samples);*/

        /*for (int i = 0; i < 10; i++){*/
        /*if (sample[i])*/
        /*printf("%s\n", sample[i]);*/
        /*else*/
        /*break;*/
        /*}*/

        /*printf("%d\n", n_of_samples(var));*/

        delete_format_fields(format_fields);
        delete_format_fields(sample);

        free_variant(var);
    }

    free(line);

    return 0;
}
