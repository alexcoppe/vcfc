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

        for (int i = 0; i < 10; i++){
            if (format_fields[i])
                printf("%s\n", format_fields[i]);
            else
                break;
        }

        delete_format_fields(format_fields);

        char **sample = get_format_fields(var->samples[0]);

        for (int i = 0; i < 10; i++){
            if (sample[i])
                printf("%s\n", sample[i]);
            else
                break;
        }

        delete_format_fields(sample);

        /*for (int i = 0; i < 10; i++)*/
        /*puts(format_fields[i]);*/
        /*nice_print_variant(var);*/

        free_variant(var);
    }

    free(line);

    return 0;
}
