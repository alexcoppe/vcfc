#include <string.h> 
#include <stdlib.h>
#include <stdio.h>
#include "snpeff.h"

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

    strncpy(copied_info, fields, l);

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
as explained here: https://stackoverflow.com/questions/3375530/c-parse-empty-tokens-from-a-string-with-strtok*/
Snpeff_ANN *get_snpeff_annotation_field(char *single_annotation){
    Snpeff_ANN *snpeffann = (Snpeff_ANN *) malloc(sizeof(Snpeff_ANN));
    char *inputString = single_annotation;
    int ii = 0;

    char *token = strchr(single_annotation, '|');

    while (token != NULL){
        if (ii == 0){
            snpeffann->ALT = malloc(token - inputString + 1);
            strncpy(snpeffann->ALT, inputString, token - inputString);
            snpeffann->ALT[token - inputString] = '\0';
            /*printf("%s\n", snpeffann->ALT);*/
        }
        if (ii == 1){
            snpeffann->Annotation = malloc(token - inputString + 1);
            strncpy(snpeffann->Annotation, inputString, token - inputString);
            snpeffann->Annotation[token - inputString] = '\0';
            /*printf("%s\n", snpeffann->Annotation);*/
        }
        if (ii == 2){
            snpeffann->Putative_impact = malloc(token - inputString + 1);
            strncpy(snpeffann->Putative_impact, inputString, token - inputString);
            snpeffann->Annotation[token - inputString] = '\0';
            /*printf("%s\n", snpeffann->Putative_impact);*/
        }
        if (ii == 3){
            snpeffann->Gene_name = malloc(token - inputString + 1);
            strncpy(snpeffann->Gene_name, inputString, token - inputString);
            snpeffann->Gene_name[token - inputString] = '\0';
            /*printf("%s\n", snpeffann->Gene_name);*/
        }
        if (ii == 4){
            snpeffann->Gene_ID = malloc(token - inputString + 1);
            strncpy(snpeffann->Gene_ID, inputString, token - inputString);
            snpeffann->Gene_ID[token - inputString] = '\0';
            /*printf("%s\n", snpeffann->Gene_ID);*/
        }
        if (ii == 5){
            snpeffann->Feature_type = malloc(token - inputString + 1);
            strncpy(snpeffann->Feature_type, inputString, token - inputString);
            snpeffann->Feature_type[token - inputString] = '\0';
            /*printf("%s\n", snpeffann->Feature_type);*/
        }
        if (ii == 6){
            snpeffann->Feature_ID = malloc(token - inputString + 1);
            strncpy(snpeffann->Feature_ID, inputString, token - inputString);
            snpeffann->Feature_ID[token - inputString] = '\0';
            /*printf("%s\n", snpeffann->Feature_ID);*/
        }
        if (ii == 7){
            snpeffann->Transcript_biotype = malloc(token - inputString + 1);
            strncpy(snpeffann->Transcript_biotype, inputString, token - inputString);
            snpeffann->Transcript_biotype[token - inputString] = '\0';
            /*printf("%s\n", snpeffann->Transcript_biotype);*/
        }
        if (ii == 8){
            snpeffann->Rank = malloc(token - inputString + 1);
            strncpy(snpeffann->Rank, inputString, token - inputString);
            snpeffann->Rank[token - inputString] = '\0';
            /*printf("%s\n", snpeffann->Rank);*/
        }
        if (ii == 9){
            snpeffann->HGVS_c = malloc(token - inputString + 1);
            strncpy(snpeffann->HGVS_c, inputString, token - inputString);
            snpeffann->HGVS_c[token - inputString] = '\0';
            /*printf("%s\n", snpeffann->HGVS_c);*/
        }
        if (ii == 10){
            snpeffann->HGVS_p = malloc(token - inputString + 1);
            strncpy(snpeffann->HGVS_p, inputString, token - inputString);
            snpeffann->HGVS_p[token - inputString] = '\0';
            /*printf("%s\n", snpeffann->HGVS_p);*/
        }
        if (ii == 11){
            snpeffann->cDNA_position_cDNA_len = malloc(token - inputString + 1);
            strncpy(snpeffann->cDNA_position_cDNA_len, inputString, token - inputString);
            snpeffann->cDNA_position_cDNA_len[token - inputString] = '\0';
            /*printf("%s\n", snpeffann->cDNA_position_cDNA_len);*/
        }
        if (ii == 12){
            snpeffann->CDS_position_CDS_len = malloc(token - inputString + 1);
            strncpy(snpeffann->CDS_position_CDS_len, inputString, token - inputString);
            snpeffann->CDS_position_CDS_len[token - inputString] = '\0';
            /*printf("%s\n", snpeffann->CDS_position_CDS_len);*/
        }
        if (ii == 13){
            snpeffann->Protein_position_Protein_len = malloc(token - inputString + 1);
            strncpy(snpeffann->Protein_position_Protein_len, inputString, token - inputString);
            snpeffann->Protein_position_Protein_len[token - inputString] = '\0';
            /*printf("%s\n", snpeffann->Protein_position_Protein_len);*/
        }
        if (ii == 14){
            snpeffann->Distance_to_feature = malloc(token - inputString + 1);
            strncpy(snpeffann->Distance_to_feature, inputString, token - inputString);
            snpeffann->Distance_to_feature[token - inputString] = '\0';
            /*printf("%s\n", snpeffann->Distance_to_feature);*/
        }
        
        snpeffann->next = NULL;
        ii++;

        inputString = token + 1;

        token = strchr(inputString, '|');
    }
    snpeffann->Errors = malloc(token - inputString + 1);
    snpeffann->Errors = strdup(inputString);
    /*printf("%s\n", snpeffann->Errors);*/

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
    free(snpeffann);
}
