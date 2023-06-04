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
