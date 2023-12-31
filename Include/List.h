// Fichier list.h
#ifndef _LIST_H
#define _LIST_H
#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 
#include "../Include/Element.h"


// 1. Définition des types maillon (link_t) et liste (list_t)
typedef struct _link {
  element_t val; /* un élément de la liste*/
  struct _link *next; /* l'adresse du maillon suivant */
} link_t, *list_t;

// 2. Protoype des fonctions realisant les opérations essentielles du type abstrait Liste

// Crée une liste vide
list_t list_new() ;

// Retourne VRAI si l est une liste vide
int list_is_empty(list_t l);

// Retourne l'élément en tête de liste
// PRECONDITION : liste non vide
element_t list_first(list_t l);

// Retourne le reste de la liste
// PRECONDITION : liste non vide
list_t list_next(list_t l);

// Ajoute l'élément e en tête de la liste et retourne la nouvelle liste
list_t list_add_first(element_t e, list_t l);

// Supprime le maillon en tête de liste et retourne la nouvelle liste
// PRECONDITION : liste non vide
list_t list_del_first(list_t l);

// Retourne le nombre d'éléments (ou de maillons) de la liste
int list_length(list_t l);

// Retourne un pointeur sur le premier maillon contenant e,
// ou NULL si e n'est pas dans la liste
list_t list_find(element_t e, list_t l);

// Affiche la liste
void list_print(list_t l);

// Trouve une cle dans la list_is_empty
list_t list_find_key(keys_t k, list_t l);

//SUppresion du maillon de cle k
list_t list_delete_key(keys_t k, list_t l);




// Libère toute la liste et retourne une liste vide
list_t list_delete(list_t l);

// Compte le nombre de e dans la liste
int list_count(element_t e, list_t l) ;

// Ajoute en fin de liste
list_t list_add_last(element_t e, list_t l) ;

// Concatene 2 listes
list_t list_concat(list_t l1, list_t l2);

// Clone une liste
list_t list_copy(list_t l);

// Clone une liste a l'envers
list_t list_inverse_copy(list_t l);


// Supprime l'element en position n et retourne la nouvelle liste
list_t list_remove_n(int n, list_t l) ;

// Duplique les n premiers maillons
list_t list_dup_n(list_t l, int n) ;

// Fusionne 2 listes ordonnees. Ordre donne par la fonction element_compare
// Ici, ordre decroissant des frequences de l'histogramme
list_t list_fusion(list_t l1, list_t l2) ;

// Retourne la liste trie par ordre donne par la fonction element_compare
// Ici, ordre decroissant des frequences de l'histogramme
// La liste n'est pas dupliquee
list_t list_sort_value(list_t l ) ;

// Sauvegarde des elemetns dnas un fichier
int list_fprint(list_t l, char* filename) ;

// Duplique les n premiers maillons
list_t list_dup_n(list_t l, int n);



#endif
