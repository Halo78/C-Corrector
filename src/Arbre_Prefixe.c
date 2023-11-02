#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../Include/Arbre_Prefixe.h"
#include <time.h>
#include <stdbool.h>


//creer un noeud de l'arbre
tree_t create_node(char value) {

  tree_t new_node = (tree_t)malloc(sizeof(struct _node));

  new_node->value = value;

  new_node->sons = NULL;
  new_node->brothers = NULL;

  return new_node;

}
//ajouter un mot dans l'arbre
void ajouter_mot(tree_t root, char *word) {
  tree_t current = root;
  for (int i = 0; i < strlen(word); i++) {

    tree_t child = current->sons;

    while (child != NULL && child->value != word[i]) {
      child = child->brothers;


    }
    if (child == NULL) {
      child = create_node(word[i]);

      child->brothers = current->sons;
      current->sons = child;
    }
    current = child;
  }
}
//chercher un mot dans l'arbre 
int search_word(tree_t root, char *word) {
    

  if (isupper(word[0])){
    return 1;
  }
  tree_t current = root;

  for (int i = 0; i < strlen(word); i++) {

    tree_t child = current->sons;

    while (child != NULL && child->value != word[i]) {
      child = child->brothers;
      
    }
    if (child == NULL) {
      return 0;
    }
    current = child;
  }
  return 1;
}


// ajouter un dictionnaire dans l'arbre
void ajouter_dico(tree_t root, const char * dico_nom) {
  FILE *dico = fopen(dico_nom, "r");
  char word[100];
  while (fscanf(dico, "%s", word) == 1) {
    ajouter_mot(root, word);
  }
  fclose(dico);
}
// ajouter un dictionnaire dans l'arbre avec un nombre de mots k
tree_t ajouter_dico_analyse(tree_t root, const char *dico_nom, int k ) {
  FILE *dico = fopen(dico_nom, "r");
  char word[100]; 
  int i = 0; 
  while(i<k) { 
  while (fscanf(dico, "%s", word) == 1) {
    ajouter_mot(root, word);
  }
  i++;
  }
  fclose(dico);
  return root;
}
//comparer un texte avec un dictionnaire
void compare(const char *dico_nom, const char *text_nom) {
  tree_t root = create_node('\0');

  FILE *texte = fopen(text_nom, "r");
  FILE *intrus = fopen("intrus", "w");
  char word[256];


   ajouter_dico(root, dico_nom) ; 


   while (fscanf(texte, "%s", word) == 1) {

    char * tmp ;
    char *tmp1 ;
    char *tmp_original ;


      tmp1 = strdup(word) ;
      tmp  = strtok(tmp1," ,;':-().?!\"" ) ;
      tmp_original = strtok (word, " ,;':-().?!\"");


       while (tmp != NULL){
       if (!search_word(root, tmp)) {
      fprintf(intrus, "%s\n", tmp_original);
        }
        tmp = strtok (NULL, " ,;':-().?!\"");


       }
       free(tmp1);
       free(tmp);
  }
  fclose(texte);
  fclose(intrus);
}


//comparer un texte avec un dictionnaire et afficher le temps d'execution
void compare_analyse(tree_t root,const char * dico_nom, const char * text_nom) {

  FILE *texte = fopen(text_nom, "r");
  FILE *intrus = fopen("intrus", "w");
  char word[256];


   ajouter_dico(root, dico_nom) ; 


   while (fscanf(texte, "%s", word) == 1) {

    char * tmp ;
    char *tmp1 ;
    char *tmp_original ;


      tmp1 = strdup(word) ;
      tmp  = strtok(tmp1," ,;':-().?!\"" ) ;
      tmp_original = strtok (word, " ,;':-().?!\"");

        
       while (tmp != NULL){

      
       if (!search_word(root, tmp)) {
      fprintf(intrus, "%s\n", tmp_original);
        }
        tmp = strtok (NULL, " ,;':-().?!\"");


       }
       free(tmp1);
       free(tmp);
  }
  fclose(texte);
  fclose(intrus);
}

int get_size_dico(const char *dico)
{
  FILE *f_dico_size = NULL;
  int size = 0;
  if ((f_dico_size = fopen(dico, "r")) != NULL)
  {
    char mot[256];

    while (fscanf(f_dico_size, "%s", mot) == true)
    {

      size++;
    }
    fclose(f_dico_size);
  }
  return size;
}


int analyse_performance(const char *dictionnaire, const char *texte)
{
  clock_t debut, fin, debut1, fin1;

  tree_t dico_tree = create_node('\0');
  double taille = 0;
  double size_bytes = 0;

  int nbwords = get_size_dico(dictionnaire);

  FILE *ftemps = fopen("temps.dat", "w");
  for (int k = nbwords; k > 1; k -= nbwords / 100)
  {
    debut = clock();

    dico_tree = ajouter_dico_analyse(dico_tree, dictionnaire, k);
    fin = clock();

    // On calcule la taille mémoire réelle du dictionnaire en Moctets  en utilisant _node 
    size_bytes = (double)k * sizeof(struct _node);
    taille = size_bytes / (1024 * 1024);



    debut1 = clock();
    compare_analyse(dico_tree,dictionnaire,texte);
    fin1 = clock();

    /*
     On ecrit dans le fichier les données de nombre de mots du dico, taille mémoire réelle, et temps CPU de la vérification
    */
    fprintf(ftemps, "%d %lf %lf\n", k, taille, ((double)fin1 - debut1) / CLOCKS_PER_SEC);

    /* Liberation dictionnaire */
  }
  fclose(ftemps);
  /*
    Trace avec gnuplot des données enregistrée dans le fichier
    f(x) est la fonction théorique de taille mémoire en fonction du nombre de mots
    g(x) celle de la complexité
  */

  system("gnuplot -p -e \"f(x) = a * (x) + b ; fit f(x) 'temps.dat' u 1:2 via a,b;"
         "set y2range [0:100];set y2tics nomirror;"
         "plot 'temps.dat' u 1:2 with line lt 4 axis x1y2 title 'Taille', a * (x) + b  with line lt 6 axis x1y2 title 'Fit Taille';"
         "g(x) = c * (x) + d ;fit g(x) 'temps.dat' u 1:3 via c,d;"
         "replot 'temps.dat' u 1:3 with line lt 2 title 'Recherchep', g(x)  with line lt 8 title 'Fit Recherche'; quit\"");
}








int main(int ac, char **av)
{

  if (ac != 4)
  {
    printf("Usage : %s ficher_dico fichier_a_verifier \n 1-Analyse des performances \n 0-Verification de fichier \n", av[0]);
    exit(EXIT_FAILURE);
  }

  const char *dictionnaire = av[1];
  const char *texte = av[2];
  if (ac == 4)
  {
    int analyse = atoi(av[3]);

    if (analyse == 0)
    { 
      clock_t debut, fin; 
      debut = clock(); 
      compare(dictionnaire, texte);
      fin = clock();
      printf("Verification terminée avec un temps d'exécution de %lf secondes \n Les mots intrus sont dans le fichier Intrus.txt \n" ,(double)(fin - debut) / CLOCKS_PER_SEC);
    }
    else if (analyse == 1)
    {
      analyse_performance(dictionnaire, texte);
    }
    else
    {
      printf("Veuillez entrer 1 pour l'analyse des performances ou 0 pour la verification de fichier \nExemple : \"./test dico.txt texte.txt 1\"\n");
    }
  }

  else
  {
    printf("Veuillez entrer 1 pour l'analyse des performances ou 0 pour la verification de fichier \n Exemple : \"./test dico.txt texte.txt 1\"\n");
  }
}
