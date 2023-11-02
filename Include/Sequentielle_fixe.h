#include <stdio.h>
#include <stdlib.h>



typedef struct  {
    void* * data  ;         // Les données du tableau : un pointeur vers des pointeurs
    size_t max_size;      // La taille maximale
    size_t actual_size;    // La taille actuelle

    void* (*delete_data)(void*); // Un pointeur vers la fonction qui libère les éléments
    int (*equal_data)(void*,void*); // Comment tester l'egalite de 2 elements
    void (*fprint_data)(void*, FILE*); // Comment afficher un éléments
} * table_t ;
