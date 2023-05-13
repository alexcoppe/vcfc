# vcfc :dna:
A C library and programs for working with VCF files

# Build from GitHub :floppy_disk:

```sh
git clone https://github.com/alexcoppe/vcfc.git
cd vcfc
make
```


# Functions available 📚:

The following table shows the available functions. If you want to see a detailed description of the functions go to the [library documentation](docs/library.md) page.

| Function        | Description|
| ------------- |:-------------|
|[get_variant_from_vcf_line](docs/library.md)|reads a single line from a VCF file and returns a Variant struct|
|[free_variant](docs/library.md)|frees the memory allocatated by the get_variant_from_vcf_line|
|[nice_print_variant](docs/library.md)|prints all the fields from a Variant struct|
|[get_format_fields](docs/library.md)|takes as input a pointer to a format string (var->format) or a sample string (like var->samples[0]) gotten from the Variant struct and returns an array of pointers to the format or sample fields|


# Programs available

## get_columns2

Shows only the columns you choose from a cvs file. Does not work on a .vcf file (as it has meta-information lines e.g. ##fileformat=VCFv4.2)  

Option | What does it do
------------ | -------------
-h | Show help
-d | The field delimiter to use instead of the tab character
-f | The fields to be shown (separated by ,)

##### Example
```console
>>> get_columns2   -f 2,1,3,4  input.txt
```

## get_pass_variants

This program filters a VCF file showing only the ones with PASS in the FILTER field.

Option | What does it do
------------ | -------------
-h | Show help

##### Example

```console
>>> get_pass_variants mutations.vcf
```
