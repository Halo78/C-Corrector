#include <stdio.h>
#include <stdlib.h>



typedef struct  {
    void* * data  ;         // Les données du tableau : un pointeur vers des pointeurs
    size_t max_size;      // La taille maximale
} * table_t;
