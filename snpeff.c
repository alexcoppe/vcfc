#include <string.h> 
#include <stdlib.h>
#include <stdio.h>
#include <snpeff.h>

void show_snpeff_annotation_field(Snpeff_ANN s){
    printf("ALT: %s\n", s.ALT);
    printf("Annotation: %s\n", s.Annotation);
    printf("Putative_impact: %s\n", s.Putative_impact);
    printf("Gene_name: %s\n", s.Gene_name);
    printf("Gene_ID: %s\n", s.Gene_ID);
    printf("Feature_type: %s\n", s.Feature_type);
    printf("Feature_ID: %s\n", s.Feature_ID);
    printf("Transcript_biotype: %s\n", s.Transcript_biotype);
    printf("Rank: %s\n", s.Rank);
    printf("HGVS_c: %s\n", s.HGVS_c);
    printf("HGVS_p: %s\n", s.HGVS_p);
    printf("cDNA_position_cDNA_len: %s\n", s.cDNA_position_cDNA_len);
    printf("CDS_position_CDS_len: %s\n", s.CDS_position_CDS_len);
    printf("Protein_position_Protein_len: %s\n", s.Protein_position_Protein_len);
    printf("Distance_to_feature: %s\n", s.Distance_to_feature);
    printf("Errors: %s\n", s.Errors);
    puts("");
}


char **get_snpeff_subfields(char *fields){
    int l;
    char *ptr = NULL;
    char *subfield = NULL;
    Snpeff_ANN annotation;
    int i = 0;
    int j = 0;
    /*Snpeff_ANN *array_of_sub_fields[200] = {NULL};*/
    int number_of_subfields = 0;
    char **subfields;
    int comma = 0;

    for (j = 0; j < strlen(fields); j++){
        if (fields[j] == ',')
            comma++;
    }
    /*printf("%d\n", comma);*/

    /*To bee free*/
    char **array_of_subfields = malloc((comma + 2) * sizeof(char *));

    l = strlen(fields) + 2;
    char *copied_format = NULL;
    /*printf("%s\n\n", fields);*/
    /* Use strlcpy insteed of strncpy because is more secure */
    copied_format = (char *) malloc(l);
    strlcpy(copied_format, fields, l);
    /*puts(copied_format);*/
    // If the delimiter is found in the string
    int array_of_subfields_i = 0;
    if (strstr(copied_format, ",") != NULL) {
        ptr = strtok(copied_format, ",");
        while (ptr != NULL) {
            subfield = (char *) malloc(strlen(ptr) + 2);
            strlcpy(subfield, ptr, strlen(ptr) + 2);
            /*puts(subfield);*/
            /*printf("%d\n", array_of_subfields_i);*/
            array_of_subfields[array_of_subfields_i] = subfield;
            /*printf("%s\n", array_of_subfields[array_of_subfields_i]);*/
            /*printf("%d\n", array_of_subfields_i);*/
            array_of_subfields_i++;
            /*i++;*/
            /*printf("%s\n", subfield);*/
            ptr = strtok(NULL, ",");
            /*annotation = get_snpeff_annotation_field(subfield);*/
    /**//*printf("%s %d\n", var->chrom, var->pos);*/
    /**//*show_snpeff_annotation_field(annotation);*/
            /*array_of_sub_fields[i] = &annotation;*/
            /*number_of_subfields++;*/
            /*free(subfield);*/
            /*if (i == 14)*/
            /*break;*/
            i++;
        }
    }


    free(copied_format);

    /*printf("------ %d\n", array_of_subfields_i);*/

    /*j = 0;*/
    /*while (j < (comma - 1)){*/
        /*printf("%s\n", array_of_subfields[0]);*/
    /*j++;*/
    /*}*/

    return array_of_subfields;
}


char **f2(char *string){
    size_t l = strlen(string) + 2;
    char *copied_info = (char *) malloc(l);
    char *token;
    char **list_of_tokens = (char **) malloc(100 * sizeof(char *));
    int list_position = 0;
    char *positioned_string;
    size_t l2 = 0;
    int j = 0;

    strlcpy(copied_info, string, l);

    token = strtok(copied_info, ",");
                                                                   

    while( token != NULL ) {
        l2 = strlen(token);
        positioned_string = (char *) malloc(l2 + 2);
        strlcpy(positioned_string, token, l2);
        list_of_tokens[j] = positioned_string;
        j++;
        token = strtok(NULL, ",");
    }

    free(copied_info);

    return list_of_tokens;

}


Snpeff_ANN get_snpeff_annotation_field(char *single_annotation){
    int i = 0;
    int j = 0;
    Snpeff_ANN snpeffann;


    /*for (j=0; single_annotation[j]; single_annotation[j]=='|' ? j++ : *single_annotation++);*/
    /*if (j != 15)*/
    /*1 +1;*/
        /*return NULL;*/

    while (single_annotation[i] != '\0'){
        if (single_annotation[i] == '|')
            single_annotation[i] = ' ';
        i++;
    }

    sscanf(single_annotation, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s", snpeffann.ALT,
            snpeffann.Annotation,
            snpeffann.Putative_impact,
            snpeffann.Gene_name,
            snpeffann.Gene_ID,
            snpeffann.Feature_type,
            snpeffann.Feature_ID,
            snpeffann.Transcript_biotype,
            snpeffann.Rank,
            snpeffann.HGVS_c,
            snpeffann.HGVS_p,
            snpeffann.cDNA_position_cDNA_len,
            snpeffann.CDS_position_CDS_len,
            snpeffann.Protein_position_Protein_len,
            snpeffann.Distance_to_feature,
            snpeffann.Errors
            );

    /*puts(snpeffann.Gene_name);*/

    return snpeffann;
}
