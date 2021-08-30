CFLAGS=-I.

all: get_columns2 get_columns get_pass_variants

get_columns: get_columns.o vcf_functions.o
	gcc get_columns.o vcf_functions.o -o get_columns
get_columns2: get_columns2.o vcf_functions.o
	gcc get_columns2.o vcf_functions.o -o get_columns2
get_columns.o: get_columns.c
	gcc $(CFLAGS) -c get_columns.c
get_columns2.o:
	gcc $(CFLAGS) -c get_columns2.c
vcf_functions.o: vcf_functions.c vcf_functions.h
	gcc $(CFLAGS) -c vcf_functions.c
get_pass_variants: get_vcf_field.o get_pass_variants.o
	gcc get_vcf_field.o get_pass_variants.o -o get_pass_variants
get_vcf_field.o: get_vcf_field.c
	gcc $(CFLAGS) -c get_vcf_field.c
get_pass_variants.o: get_pass_variants.c
	gcc $(CFLAGS) -c get_pass_variants.c
clean:
	rm -f get_columns vcf_functions.o get_columns.o get_columns2 get_columns2 get_columns2.o \
		get_vcf_field.o get_pass_variants.o get_pass_variants
