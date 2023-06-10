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
    struct info_fields_hasht *ANN = NULL;
    char **ann_subfields;
    int number_of_subfields = 1;
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
            for (int z = 0; z < strlen(ANN->value); z++){
                if (ANN->value[z] == ',')
                    number_of_subfields++;
            }
            ann_subfields = f2(ANN->value);

            /*printf("%d\n", number_of_subfields);*/
            if (number_of_subfields == 1){
                printf("%s\n", ann_subfields[0]);
            } else {
                for (int w = 1; w < number_of_subfields; w++){
                    puts(ann_subfields[w]);
                }
            }
            number_of_subfields = 1;

            for (int i = 0; i <= number_of_subfields + 100; i++){
                free(ann_subfields[i]);
            }
            free(ann_subfields);

        }

        free_variant(var);
    }

    free(line);

    return 0;
}
