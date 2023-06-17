#include <string.h> 
#include <stdlib.h>
#include <stdio.h>
#include <snpeff.h>

void show_snpeff_annotation_field(Snpeff_ANN *s){
    printf("ALT: %s\n", s->ALT);
    printf("Annotation: %s\n", s->Annotation);
    printf("Putative_impact: %s\n", s->Putative_impact);
    printf("Gene_name: %s\n", s->Gene_name);
    printf("Gene_ID: %s\n", s->Gene_ID);
    printf("Feature_type: %s\n", s->Feature_type);
    printf("Feature_ID: %s\n", s->Feature_ID);
    printf("Transcript_biotype: %s\n", s->Transcript_biotype);
    printf("Rank: %s\n", s->Rank);
    printf("HGVS_c: %s\n", s->HGVS_c);
    printf("HGVS_p: %s\n", s->HGVS_p);
    printf("cDNA_position_cDNA_len: %s\n", s->cDNA_position_cDNA_len);
    printf("CDS_position_CDS_len: %s\n", s->CDS_position_CDS_len);
    printf("Protein_position_Protein_len: %s\n", s->Protein_position_Protein_len);
    printf("Distance_to_feature: %s\n", s->Distance_to_feature);
    printf("Errors: %s\n", s->Errors);
    puts("");
}


char **get_snpeff_subfields(char *fields){
    size_t l = strlen(fields) + 2;
    char *copied_info = (char *) malloc(l);
    char *token;
    char **list_of_tokens = NULL;
    int list_position = 0;
    char *positioned_string;
    size_t l2 = 0;
    int j = 0;

    strlcpy(copied_info, fields, l);

    token = strtok(copied_info, ",");

    while( token != NULL ) {
        l2 = strlen(token);
        list_of_tokens = (char **) realloc(list_of_tokens, (j + 1) * sizeof(char *));
        list_of_tokens[j++] = strdup(token);
        token = strtok(NULL, ",");
    }

    free(copied_info);

    return list_of_tokens;
}


/* This function uses the strchr function insteed of the strtok one because 
as explained here: https://stackoverflow.com/questions/3375530/c-parse-empty-tokens-from-a-string-with-strtok
it's better much better to loop with a memcpy inside the loop. It's fast and does not destroy the input buffer */
Snpeff_ANN *get_snpeff_annotation_field(char *single_annotation){
    char *p2;
    int i = 0;
    Snpeff_ANN *snpeffann = (Snpeff_ANN *) malloc(sizeof(Snpeff_ANN));

    const char *const string = single_annotation;

    const char *p = string, *q;

    char *s;

    while ( ( q = strchr( p, '|' ) ) != NULL ){
        s = (char *) malloc(sizeof(char ) * (q-p));
        memcpy(s, p, q-p);

        if (i == 0){
            snpeffann->ALT = (char *) malloc(sizeof(char) * (strlen(s)));
            strlcpy(snpeffann->ALT, s, strlen(s) + 1);
        } else if (i == 1){
            snpeffann->Annotation = (char *) malloc(sizeof(char) * (strlen(s)));
            strlcpy(snpeffann->Annotation, s, strlen(s) + 1);
        } else if (i == 2){
            snpeffann->Putative_impact = (char *) malloc(sizeof(char) * (strlen(s)));
            strlcpy(snpeffann->Putative_impact, s, strlen(s) + 1);
        } else if (i == 3){
            snpeffann->Gene_name = (char *) malloc(sizeof(char) * (strlen(s)));
            strlcpy(snpeffann->Gene_name, s, strlen(s) + 1);
        } else if (i == 4){
            snpeffann->Gene_ID = (char *) malloc(sizeof(char) * (strlen(s)));
            strlcpy(snpeffann->Gene_ID, s, strlen(s) + 1);
        } else if (i == 5){
            snpeffann->Feature_type = (char *) malloc(sizeof(char) * (strlen(s)));
            strlcpy(snpeffann->Feature_type, s, strlen(s) + 1);
        } else if (i == 6){
            snpeffann->Feature_ID = (char *) malloc(sizeof(char) * (strlen(s)));
            strlcpy(snpeffann->Feature_ID, s, strlen(s) + 1);
        } else if (i == 7){
            snpeffann->Transcript_biotype = (char *) malloc(sizeof(char) * (strlen(s)));
            strlcpy(snpeffann->Transcript_biotype, s, strlen(s) + 1);
        } else if (i == 8){
            snpeffann->Rank = (char *) malloc(sizeof(char) * (strlen(s)));
            strlcpy(snpeffann->Rank, s, strlen(s) + 1);
        } else if (i == 9){
            snpeffann->HGVS_c = (char *) malloc(sizeof(char) * (strlen(s)));
            strlcpy(snpeffann->HGVS_c, s, strlen(s) + 1);
        } else if (i == 10){
            snpeffann->HGVS_p = (char *) malloc(sizeof(char) * (strlen(s)));
            strlcpy(snpeffann->HGVS_p, s, strlen(s) + 1);
        } else if (i == 11){
            snpeffann->cDNA_position_cDNA_len = (char *) malloc(sizeof(char) * (strlen(s)));
            strlcpy(snpeffann->cDNA_position_cDNA_len, s, strlen(s) + 1);
        } else if (i == 12){
            snpeffann->CDS_position_CDS_len = (char *) malloc(sizeof(char) * (strlen(s)));
            strlcpy(snpeffann->CDS_position_CDS_len, s, strlen(s) + 1);
        } else if (i == 13){
            snpeffann->Protein_position_Protein_len = (char *) malloc(sizeof(char) * (strlen(s)));
            strlcpy(snpeffann->Protein_position_Protein_len, s, strlen(s) + 1);
        } else if (i == 14){
            snpeffann->Distance_to_feature = (char *) malloc(sizeof(char) * (strlen(s)));
            strlcpy(snpeffann->Distance_to_feature, s, strlen(s) + 1);
        }

        free(s);

        i++;
        p = q + 1;
    }

    snpeffann->Errors = (char *) malloc(sizeof(char) * (strlen(p)));
    strlcpy(snpeffann->Errors, s, strlen(p) + 1);
    
    /*memset(ALT,0,strlen(ALT));*/

    return snpeffann;
}


void reset_Snpeff_ANN(Snpeff_ANN *snpeffann){
    free(snpeffann->ALT);
    free(snpeffann->Annotation);
    free(snpeffann->Putative_impact);
    free(snpeffann->Gene_name);
    free(snpeffann->Gene_ID);
    free(snpeffann->Feature_type);
    free(snpeffann->Feature_ID);
    free(snpeffann->Transcript_biotype);
    free(snpeffann->Rank);
    free(snpeffann->HGVS_c);
    free(snpeffann->HGVS_p);
    free(snpeffann->cDNA_position_cDNA_len);
    free(snpeffann->CDS_position_CDS_len);
    free(snpeffann->Protein_position_Protein_len);
    free(snpeffann->Distance_to_feature);
    free(snpeffann->Errors);
}
