# vcfc
A C library and programs for VCF files analyses

## get_columns2

Shows only the columns you choose from a cvs file. Does not work on a .vcf file (as it has meta-information lines e.g. ##fileformat=VCFv4.2)  

Option | What does it do
------------ | -------------
-h | Show help
-d | The field delimiter to use instead of the tab character
-f | The fields to be shown (separated by ,)

##### Example
```
get_columns2   -f 2,1,3,4  input.txt
```

## get_pass_variants

This program filters a VCF file showing only the ones with PASS in the FILTER field.

Option | What does it do
------------ | -------------
-h | Show help

##### Example

```
get_pass_variants mutations.vcf
```
