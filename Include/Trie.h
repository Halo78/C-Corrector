#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef _LEXTREE
#define _LEXTREE



    typedef
      struct _node {
        struct _node *sons[27]; } *  tree_t;


  // Creer un arbre vide
  tree_t tree_new();

  int tree_is_empty(tree_t t);

  tree_t tree_add(char* mot, tree_t t);

  void tree_print(tree_t t);

  int tree_look(char* mot, tree_t t);

  tree_t tree_get_dico(tree_t t , const char * dico );

  void get_texte(const char* dictionnaire , const char* texte);

  tree_t tree_delete(tree_t t);


#endif
