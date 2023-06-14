#include <string.h> 
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    char *ALT;
    char *Annotation;
    char *Putative_impact;
    char *Gene_name;
    char *Gene_ID;
    char *Feature_type;
    char *Feature_ID;
    char *Transcript_biotype;
    char *Rank;
    char *HGVS_c;
    char *HGVS_p;
    char *cDNA_position_cDNA_len;
    char *CDS_position_CDS_len;
    char *Protein_position_Protein_len;
    char *Distance_to_feature;
    char *Errors;
} Snpeff_ANN;


void reset_Snpeff_ANN(Snpeff_ANN *snpeffann);

char ** get_snpeff_subfields(char *);

Snpeff_ANN *get_snpeff_annotation_field(char *);

void show_snpeff_annotation_field(Snpeff_ANN *);
