#ifndef _ELEMENT
#define _ELEMENT
#include <string.h>
#include <stdio.h>

typedef char* keys_t;

typedef int value_t;

typedef struct {
  keys_t key;
  value_t value;
} element_t;

// Retourne un nouvel element initialisé avec les valeurs cle et valeur.
// L'espace mémoire pour stocker la clé est allouée dynamiquement.
element_t element_new(keys_t key, value_t value);

// Libère l'espace mémoire alloué pour l'element et retourne une élément vide (empty)
element_t element_delete(element_t e);

// Retourne un clone (meme cle, meme valeur)
element_t element_clone(element_t e);


// Affiche la cle (mot) et la valeur (nombre d'occurrences)
void element_print (element_t e);


// Initialise un couple cle, valeur avec le couple NULL,0
void element_init (element_t* e);

// Teste si 2 clés (chaînes de char) sont egales, sans se préoccuper des majuscules et minuscules
int key_equal(keys_t, keys_t);

// Teste si 2 clés (chaînes de char) sont egales, sans se préoccuper des majuscules et minuscules
int value_equal(value_t, value_t);

// Teste si 2 couples sont égaux (meme cle, meme valeur)
int element_equal(element_t*, element_t*);

// Ecrit dans un fichier la cle (mot) et la valeur (nombre d'occurrences)
void element_fprint (FILE* fd, element_t e) ;

// Compare les 2 elemetns pointes par e1 et e2
int element_compare(element_t* e1, element_t* e2) ;

#endif
