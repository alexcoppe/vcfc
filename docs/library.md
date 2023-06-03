# vcfc library functions :books:

### :bookmark: _bed_entries_

SYNOPSIS:

```C

#include "bed.h"

BedEntry *
bed_entries(char *file_path);

void
free(BedEntry *)
```

DESCRIPTION:

The _bed_entries_ function reads a file and returns an array of BeEntry structs pointers. The only parameter needed is the path to the BED file. The _free_ function is used to free the array returned by the _bed_entries_ function.

RETURN VALUES:

The _bed_entries_ returns an array of BeEntry structs pointers

------

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


------

### :bookmark: _nice_print_variant_

SYNOPSIS:
```C
#include "variant.h"

void
nice_print_variant(Variant *variant)
```

DESCRIPTION:

The _nice_print_variant_ prints all the fields from a Variant struct. As input need a pointer to a Variant struct. The return is void

------

### :bookmark: get_format_fields

SYNOPSIS:
```C
#include "variant.h"

char **
get_format_fields(char *format)
```
DESCRIPTION:

The _get_format_fields_ function take as input a pointer to a format string (_var->format_) or a sample string (_like var->samples[0]_) gotten from the _Variant_ struct and returns an array of strings pointers to the **format** or **sample** fields. 
