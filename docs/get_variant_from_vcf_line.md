### :bookmark: _get_variant_from_vcf_line_ and _free_variant_
  
SYNOPSIS:

```C

#include "variant.h"

Variant *
get_variant_from_vcf_line(char *vcf_line);

void
free_variant(Variant *v)

```
  
DESCRIPTION:

The _get_variant_from_vcf_line_ function reads a single line of string pointer type from a VCF file and returns a Variant struct.
The _free_variant_ function frees the dynamically allocatated memory by the _get_variant_from_vcf_line_ and it takes as input the pointer to the Variant struct to be free.

RETURN VALUES:

The _get_variant_from_vcf_line_ returns a pointer to a struct of type _Variant_.
