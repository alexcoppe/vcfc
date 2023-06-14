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


Snpeff_ANN *get_snpeff_annotation_field(char *single_annotation){
    int i = 0;
    int j = 0;
    Snpeff_ANN *snpeffann;
    long int l;


    for (j=0; single_annotation[j]; single_annotation[j]=='|' ? j++ : *single_annotation++);
    if (j != 15)
        return NULL;

    while (single_annotation[i] != '\0'){
        if (single_annotation[i] == '|')
            single_annotation[i] = ' ';
        i++;
    }

    char ALT[1000],
    Annotation[1000],
    Putative_impact[1000],
    Gene_name[1000],
    Gene_ID[1000],
    Feature_type[1000],
    Feature_ID[1000],
    Transcript_biotype[1000],
    Rank[1000],
    HGVS_c[1000],
    HGVS_p[1000],
    cDNA_position_cDNA_len[1000],
    CDS_position_CDS_len[1000],
    Protein_position_Protein_len[1000],
    Distance_to_feature[1000],
    Errors[1000];

    sscanf(single_annotation, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s",
            ALT,
            Annotation,
            Putative_impact,
            Gene_name,
            Gene_ID,
            Feature_type,
            Feature_ID,
            Transcript_biotype,
            Rank,
            HGVS_c,
            HGVS_p,
            cDNA_position_cDNA_len,
            CDS_position_CDS_len,
            Protein_position_Protein_len,
            Distance_to_feature,
            Errors
          );


    snpeffann = (Snpeff_ANN *) malloc(sizeof(Snpeff_ANN));

    l = strlen(Annotation);
    snpeffann->Annotation = (char *) malloc(l + 1);
    strcpy(snpeffann->Annotation, Annotation);

    l = strlen(ALT);
    snpeffann->ALT = (char *) malloc(l + 1);
    strcpy(snpeffann->ALT, ALT);

    l = strlen(Putative_impact);
    snpeffann->Putative_impact = (char *) malloc(l + 1);
    strcpy(snpeffann->Putative_impact, Putative_impact);

    l = strlen(Gene_name);
    snpeffann->Gene_name = (char *) malloc(l + 1);
    strcpy(snpeffann->Gene_name, Gene_name);

    l = strlen(Gene_ID);
    snpeffann->Gene_ID = (char *) malloc(l + 1);
    strcpy(snpeffann->Gene_ID, Gene_ID);

    l = strlen(Feature_type);
    snpeffann->Feature_type = (char *) malloc(l + 1);
    strcpy(snpeffann->Feature_type, Feature_type);

    l = strlen(Feature_ID);
    snpeffann->Feature_ID = (char *) malloc(l + 1);
    strcpy(snpeffann->Feature_ID, Feature_ID);

    l = strlen(Transcript_biotype);
    snpeffann->Transcript_biotype = (char *) malloc(l + 1);
    strcpy(snpeffann->Transcript_biotype, Transcript_biotype);

    l = strlen(Rank);
    snpeffann->Rank = (char *) malloc(l + 1);
    strcpy(snpeffann->Rank, Rank);

    l = strlen(HGVS_c);
    snpeffann->HGVS_c = (char *) malloc(l + 1);
    strcpy(snpeffann->HGVS_c, HGVS_c);

    l = strlen(HGVS_p);
    snpeffann->HGVS_p = (char *) malloc(l + 1);
    strcpy(snpeffann->HGVS_p, HGVS_p);

    l = strlen(cDNA_position_cDNA_len);
    snpeffann->cDNA_position_cDNA_len = (char *) malloc(l + 1);
    strcpy(snpeffann->cDNA_position_cDNA_len, cDNA_position_cDNA_len);

    l = strlen(CDS_position_CDS_len);
    snpeffann->CDS_position_CDS_len = (char *) malloc(l + 1);
    strcpy(snpeffann->CDS_position_CDS_len, CDS_position_CDS_len);

    l = strlen(Protein_position_Protein_len);
    snpeffann->Protein_position_Protein_len = (char *) malloc(l + 1);
    strcpy(snpeffann->Protein_position_Protein_len, Protein_position_Protein_len);

    l = strlen(Distance_to_feature);
    snpeffann->Distance_to_feature = (char *) malloc(l + 1);
    strcpy(snpeffann->Distance_to_feature, Distance_to_feature);

    l = strlen(Errors);
    snpeffann->Errors = (char *) malloc(l + 1);
    strcpy(snpeffann->Errors, Errors);


    return snpeffann;
}


void reset_Snpeff_ANN(Snpeff_ANN *snpeffann){
    free(snpeffann->Annotation);
    free(snpeffann->ALT);
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
