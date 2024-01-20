#include <string.h> 
#include <stdlib.h>
#include <stdio.h>
#include "variant.h"
#include "snpeff.h"
#include "krhashtable.h"

void display(Snpeff_ANN *s){
    Snpeff_ANN *n = s;
    int i = 0;

    while (n != NULL){
        show_snpeff_annotation_field(n);
        i++;
        n = n->next;
    }
}

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
        fprintf(stderr, "Coud not find file: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, file)) != -1) {
        if (line[0] == '#')
            continue;

        var = get_variant_from_vcf_line(line);
        /*nice_print_variant(var);*/

        get_info_field(var->info, damnhash);
        ANN = lookup("ANN", damnhash);

        Snpeff_ANN *i = NULL;
        Snpeff_ANN *next = NULL;
        Snpeff_ANN *to_remove = NULL;


        if (ANN != NULL){

            for (int z = 0; z < strlen(ANN->value); z++){
                if (ANN->value[z] == ',')
                    number_of_subfields++;
            }
            /*printf("%s\n", ANN->value);*/

            ann_subfields = get_snpeff_subfields(ANN->value);

            if (number_of_subfields == 1){
                var->snpeffann = get_snpeff_annotation_field(ann_subfields[0]);
            }
            else {
                for (int w = 0; w < number_of_subfields - 1; w++){
                    if (w == 0){
                        var->snpeffann = get_snpeff_annotation_field(ann_subfields[w]);
                        next = var->snpeffann;
                    } else {
                        next->next = get_snpeff_annotation_field(ann_subfields[w]);
                        next = next->next;
                    }
                }
            }

            display(var->snpeffann);

            for (int j = 0; j < number_of_subfields; j++){
                free(ann_subfields[j]);
            }

            free(ann_subfields);

            free_variant(var);

        }

        number_of_subfields = 1;
    }


    free(line);

    return 0;
}
