#include <string.h> 
#include <stdlib.h>
#include <stdio.h>


typedef struct {
    char ALT[1000];
    char Annotation[1000];
    char Putative_impact[1000];
    char Gene_name[1000];
    char Gene_ID[1000];
    char Feature_type[1000];
    char Feature_ID[1000];
    char Transcript_biotype[1000];
    char Rank[1000];
    char HGVS_c[1000];
    char HGVS_p[1000];
    char cDNA_position_cDNA_len[1000];
    char CDS_position_CDS_len[1000];
    char Protein_position_Protein_len[1000];
    char Distance_to_feature[1000];
    char Errors[1000];
} Snpeff_ANN;


Snpeff_ANN get_snpeff_annotation_field(char *);

void show_snpeff_annotation_field(Snpeff_ANN);
