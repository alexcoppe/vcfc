#include <string.h> 
#include <stdlib.h>  /* malloc */
#include <stdio.h>   /* printf */
#include "krhashtable.h"


void print_info_fields_hasht(struct info_fields_hasht *key_valu){
    printf("%s %s\n", key_valu->key, key_valu->value);
}

unsigned hash(char *s){
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++){
        hashval = *s + 31 * hashval;
    }
    return hashval % HASHSIZE;
}

struct info_fields_hasht *lookup(char *key, struct info_fields_hasht **hashtb){
    struct info_fields_hasht *np;

    for (np = hashtb[hash(key)];  np != NULL; np = np->next){
        if (strcmp(key, np->key) == 0)
            return np;
    }
    return NULL;
}

struct info_fields_hasht *install(char *key, char *value, struct info_fields_hasht **hashtb)
{
    struct info_fields_hasht *np;
     unsigned hashval;
 
    if ((np = lookup(key, hashtb)) == NULL) {
        np = (struct info_fields_hasht *) malloc(sizeof(*np));
        if (np == NULL || (np->key = strdup(key)) == NULL)
            return NULL;
        hashval = hash(key);
        np->next = hashtb[hashval];
        hashtb[hashval] = np;
    }
    else
        free((void *) np->value);

    if ((np->value = strdup(value)) == NULL)
        return NULL;
    return np;
}

/*int main(){*/

/*install("Ale", "test", hashtab);*/
/*install("Ale", "yes", hashtab);*/
/*install("Rambo", "No", hashtab);*/
/*print_info_fields_hasht(install("Ale", "yes", hashtab));*/

/*struct info_fields_hasht *man = lookup("Ale", hashtab);*/
/*print_info_fields_hasht(man);*/
/*man = lookup("Rambo", hashtab);*/
/*print_info_fields_hasht(man);*/

/*install("chistty", "f", hashtab2);*/
/*man = lookup("chistty", hashtab2);*/
/*print_info_fields_hasht(man);*/

/*man = lookup("ramboso", hashtab2);*/
/*if (man == NULL)*/
/*puts("Not found");*/
/*else*/
/*print_info_fields_hasht(man);*/

/*return 0;*/
/*}*/
