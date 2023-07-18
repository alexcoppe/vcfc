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
        /*printf("%i\n", i);*/
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
        fprintf(stderr, "Coud not find file: %s\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, file)) != -1) {
        if (line[0] == '#')
            continue;

        var = get_variant_from_vcf_line(line);

        get_info_field(var->info, damnhash);
        ANN = lookup("ANN", damnhash);

        Snpeff_ANN *start = NULL;
        Snpeff_ANN *i = NULL;
        Snpeff_ANN *next = NULL;


        if (ANN != NULL){

            for (int z = 0; z < strlen(ANN->value); z++){
                if (ANN->value[z] == ',')
                    number_of_subfields++;
            }

            /*if (number_of_subfields == 1)*/
            /*printf("%s\n\n", ANN->value);*/


            ann_subfields = get_snpeff_subfields(ANN->value);


            if (number_of_subfields == 1){
                var->snpeffann = get_snpeff_annotation_field(ann_subfields[0]);
                /*printf("%i\n", number_of_subfields);*/
                /*show_snpeff_annotation_field(var->snpeffann);*/
            } else {
                for (int w = 0; w < number_of_subfields - 1; w++){
                    if (w == 0){
                        var->snpeffann = get_snpeff_annotation_field(ann_subfields[w]);
                        i = var->snpeffann;
                        /*show_snpeff_annotation_field(var->snpeffann);*/
                    }
                    else{
                        next = get_snpeff_annotation_field(ann_subfields[w]);
                        i->next = next;
                        i = next;
                        /*show_snpeff_annotation_field(var->snpeffann);*/
                        /*printf("W: %s ------- %d\n", i->next->Gene_ID, w);*/
                    }
                }
            }

            Snpeff_ANN *zf = var->snpeffann;
            while (zf != NULL){
                show_snpeff_annotation_field(zf);
                zf = zf->next;
            }



            /*display(var->snpeffann);*/

            for (int j = 0; j < number_of_subfields; j++){
                free(ann_subfields[j]);
            }
            free(ann_subfields);

            free_variant(var);

            /*number_of_subfields = 1;*/
        }

        /*free_variant(var);*/
        number_of_subfields = 1;
    }

    free(line);

    return 0;
}
