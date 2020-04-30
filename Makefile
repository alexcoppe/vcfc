CFLAGS=-I.

get_columns: get_columns.o vcf_functions.o
	gcc get_columns.o vcf_functions.o -o get_columns
get_columns.o: get_columns.c
	gcc $(CFLAGS) -c get_columns.c
vcf_functions.o: vcf_functions.c vcf_functions.h
	gcc $(CFLAGS) -c vcf_functions.c
clean:
	rm -f get_columns vcf_functions.o get_columns.o
