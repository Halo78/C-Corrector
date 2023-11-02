#include <time.h>
#include <math.h>
#include<stdlib.h>
#include<stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../Include/Trie.h"





 int get_size_dico(const char * dico ) {
   FILE *f_dico_size = NULL ;
   int size = 0  ;
    if((f_dico_size = fopen(dico,"r")) != NULL){
      char mot[256];

      while(fscanf(f_dico_size,"%s",mot) == true ){

        size ++  ;
      }
    fclose(f_dico_size);
    }
    printf("Taille OK !\n");
    return size ;
   }


tree_t  tree_new()  {
  return NULL;

}


int  tree_is_empty(tree_t r)  {
  return r==NULL;
}

  tree_t tree_add(char* mot,tree_t t){
    //printf("la\n");

    if (mot==NULL){
      return NULL;

    }
    if (tree_is_empty(t)){
      t=calloc(1,sizeof(*t));
    }
    int key;
    int i=0;
    char c= mot[0];
    tree_t p=t;
    while(c!=0){

      key=c-96;
      if (!tree_is_empty(p->sons[key])){


        p=p->sons[key];
        i=i+1;
        c=mot[i];

      }
      else {

        key=c-96;
        p->sons[key]=calloc(1,sizeof(*p));
        p=p->sons[key];
        i=i+1;
        c=mot[i];
        // est ce qu'il faut allouer un nouveau noeud
      }


      }
      if(tree_is_empty(p->sons[0])){
        p->sons[0]=calloc(1,sizeof(*p));
      }
      return t;

    }

void tree_print(tree_t t){
  if (tree_is_empty(t)){
    printf("L'arbre est vide");
  }
  else {
    tree_t p=t;
    int i=1;
    if (!tree_is_empty(p->sons[0])){
      printf("]");

    }
    while(i<27){
      if (!tree_is_empty(p->sons[i])){
        printf("%c",i+96);

        tree_print(p->sons[i]);
      }
      i=i+1;
    }


  }

}

int tree_look(char* mot, tree_t t){
  if (mot==NULL){
    return 0;
  }
  if (tree_is_empty(t)){
    printf("L'arbre est vide");
    return 0;
  }

  int key=0;
  int i=0;
  char c= mot[0];
  tree_t p=t;
  while(c!=0){
    if((c<123) & (c>96)){

      key=c-96;
    }
    if((c<92)&(c>64)){

      key=c-64;
    }


    if (!tree_is_empty(p->sons[key])){
      p=p->sons[key];
      i=i+1;
      c=mot[i];

    }
    else {
      return 0;

    }


    }
    if(tree_is_empty(p->sons[0])){
      return 0;
    }
    return 1;

}

tree_t tree_delete(tree_t t){

  int i=0;
  while(i<27){
    if (!tree_is_empty(t->sons[i])){
      tree_delete(t->sons[i]);
    }
    i=i+1;
  }
  free(t);
  return NULL;
}


tree_t tree_get_dico(tree_t t , const char * dico ) {
  FILE *fp = NULL ;
   if((fp = fopen(dico,"r")) != NULL){
     char mot[256];
     while(fscanf(fp,"%s",mot) == 1 ){
       char* c =strdup(mot);
       t = tree_add(c,t);
       free(c);

     }
   fclose(fp);
   }
   return t;

  }



tree_t tree_get_dico_analyse(tree_t t , const char * dico , int k ) {
  FILE *fp = NULL ;
  int compteur_mot = 0 ; 
   if((fp = fopen(dico,"r")) != NULL){
     char mot[256];
     while(compteur_mot<k){ 
     while(fscanf(fp,"%s",mot) == 1 ){
       char* c =strdup(mot);
       t = tree_add(c,t);
       compteur_mot ++ ; 
     }
     }
   fclose(fp);
   }
   return t;

  }


void get_texte(const char* dictionnaire , const char* texte) {
  FILE *fp = NULL ;
  FILE *faux = NULL;
  faux = fopen("Intrus.txt", "w");
  tree_t tdico = tree_new();
  tdico = tree_get_dico(tdico,"dico1.txt");
  if((fp = fopen(texte,"r")) != NULL){

    char mot[256];

    while(fscanf(fp,"%s",mot) == 1 ){
      char * tmp ;
      char *tmp1 ;

      tmp1 = strdup(mot) ;
      tmp  = strtok(tmp1," ,;':-().?!\"" ) ;


       while (tmp != NULL){
         if (tree_look(tmp,tdico)==0){
           //printf(tmp);
           fwrite(tmp, sizeof(char), strlen(tmp),faux);
           fwrite("\n",sizeof(char),1,faux);
           //vect_append(tmp,faux);
           //printf("la\n");
         }
        tmp = strtok (NULL, " ,;':-().?!\"");


       }
       free(tmp1);
       free(tmp);
    }


  fclose(fp);
  fclose(faux);

  }
  else{
    printf("Erreur d'ouverture du fichier \n");
  }
  
}


void get_texte_analyse(tree_t tdico , const char* texte) {
  FILE *fp = NULL ;
  FILE *faux = NULL;
  faux = fopen("Intrus.txt", "w");
  if((fp = fopen(texte,"r")) != NULL){

    char mot[256];

    while(fscanf(fp,"%s",mot) == 1 ){
      char * tmp ;
      char *tmp1 ;

      tmp1 = strdup(mot) ;
      tmp  = strtok(tmp1," ,;':-().?!\"" ) ;


       while (tmp != NULL){
         if (tree_look(tmp,tdico)==0){
           //printf(tmp);
           fwrite(tmp, sizeof(char), strlen(tmp),faux);
           fwrite("\n",sizeof(char),1,faux);
           //vect_append(tmp,faux);
           //printf("la\n");
         }
        tmp = strtok (NULL, " ,;':-().?!\"");


       }
       free(tmp1);
       free(tmp);
    }


  fclose(fp);
  fclose(faux);

  }
  else{
    printf("Erreur d'ouverture du fichier \n");
  }
  
}


int analyse_performance(const char *dictionnaire, const char *texte)
{
  clock_t debut, fin, debut1, fin1;

  tree_t dico_tab = tree_new(); 
  double taille = 0;
  double size_bytes = 0;

  int nbwords = get_size_dico(dictionnaire);

  FILE *ftemps = fopen("temps.dat", "w");
  for (int k = nbwords; k > 1; k -= nbwords / 100)
  {
    debut = clock();
    dico_tab = tree_get_dico_analyse(dico_tab, dictionnaire, k);
    fin = clock();

    //// calcul de la taille réelle du dico en Moctets
    size_bytes = k * sizeof(char *);
    taille = size_bytes / (1024 * 1024);

    debut1 = clock();
    get_texte_analyse(dico_tab, texte);
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
      get_texte(dictionnaire, texte);
      printf("Verification terminée ! les mots intrus sont dans le fichier Intrus.txt \n");
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
