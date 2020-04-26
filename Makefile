CFLAGS=-I.

get_column: get_column.o vcf_functions.o
	gcc get_column.o vcf_functions.o -o get_column
get_column.o: get_column.c
	gcc $(CFLAGS) -c get_column.c
vcf_functions.o: vcf_functions.c vcf_functions.h
	gcc $(CFLAGS) -c vcf_functions.c
clean:
	rm -f get_column vcf_functions.o get_column.o
