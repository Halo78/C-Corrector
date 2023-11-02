#include "../Include/Ensemble.h" 
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h> 
#include <math.h>
 // Fonction de hachage d'un chaine pour une table de taille n 

 // Utilisé fonction DBJ2   (on peut utiliser la fonction 33 )
unsigned int hash(char *s, int n) {
  unsigned int hashcode = 5381;
  int c;

  while ((c = *s++)) {
    hashcode = ((hashcode << 5) + hashcode) + c; 
  }

  return hashcode % n;
}


//--------------------------------------------------------------------------------------------


/* // Alloue dynamiquement et retourne une nouvelle table de m listes vides ;
hashtable_t hashtable_new(int m) {
  hashtable_t tab;
      t.data = calloc(m, sizeof(list_t)) ; //alloue les m listes
    tab.size=size;
    tab.data=calloc(tab.size,sizeof(tab.data[0]));
    assert(tab.data);
  return tab;
} ----------------------ALLOCATION DYNAMIQUE */

hashtable_t hashtable_new(int m) {
  hashtable_t t;
  t.size = 0;
  t.data = calloc(m, sizeof(list_t)) ; // allocation du tableau de m listes
  if(t.data == NULL) {
    return t ; // échec de l'allocation => retourne une table vide
  }
  t.size = m;
  return t;
}


void hashtable_print(hashtable_t ht) {
  int i;
  for(i=0; i<ht.size; i++) {
    printf("[%d] = ", i);
    list_print(ht.data[i]);
  }

}

//
int hashtable_put(keys_t k, value_t v, hashtable_t t) {
  int h = hash(k, t.size);
  //printf("h = %d\n", h); 
  list_t chain = list_find_key(k, t.data[h]);

  if (!list_is_empty(chain)) {
    // Key already exists, update value
    chain->val.value = v;
    return 1;
  } else {
    // Key does not exist, add new key-value pair to end of linked list
    t.data[h] = list_add_last(element_new(k, v), t.data[h]);
    return 1;
  }
}


void get_dico(hashtable_t hashtable , const char * dico  ) {

     FILE *f_dico = NULL ;
     int j = 0 ;
      if((f_dico = fopen(dico,"r")) != NULL){ //PROBLEME ICI CA RENTRE JAMAIS,
        char mot[256];
        while(fscanf(f_dico,"%s",mot) == 1 ){
          unsigned int hashcode=hash(mot,hashtable.size);
          hashtable_put(mot,hashcode,hashtable);
          // hashtable_print(hashtable);
           }
      fclose(f_dico);
      }

}


void get_dico_analyse(hashtable_t hashtable , const char * dico , int k   ) {

     FILE *f_dico = NULL ;
     int j = 0 ;
      if((f_dico = fopen(dico,"r")) != NULL){ //PROBLEME ICI CA RENTRE JAMAIS,
        char mot[256];
        while(fscanf(f_dico,"%s",mot) == 1 && j<k){
          unsigned int hashcode=hash(mot,hashtable.size);
          hashtable_put(mot,hashcode,hashtable);
          // hashtable_print(hashtable);
          j++;
           }
      fclose(f_dico);
      }

}



//--------------------------------------------------------------------------------------------

int hashtable_contains(keys_t k, hashtable_t t){ 
 int h=hash(k,t.size);
 if(list_is_empty(list_find_key(k,t.data[h]))== 0 ){
  return 0;
}
  else{
  return 1;
  }
}



int hashtable_get_value(keys_t k, value_t* pv, hashtable_t t) {
//  printf("debut get value\n");
  int h=hash(k,t.size);
  list_t chain=list_find_key(k,t.data[h]);

  if(!list_is_empty(chain)){
    // printf("JSUIS DANS LE IF");
    // printf("VALEUR DE LA Chaine %d\n", chain->val.value);


  chain->val.value=*pv; //PROBLEME ICI;
          //printf("VALEUR DE LA Chaine CHANGé %d\n", chain->val.value);

     // list_print(chain);

  return 1;
  }
  return 0;  
}

// supprime la cle k et la valeur associee de la table t
// retourne 1 si la suppression est realisee, 0 sinon
int hashtable_delete_key(keys_t k, hashtable_t t) {
 
  int h=hash(k,t.size);
  list_t chain=list_find_key(k,t.data[h]);
  if(list_is_empty(chain)){
    t.data[h]=list_delete_key(k,chain);
  }
  // Calculer le hashcode de k
  //Si la cle est presente dans la liste adequate,detruit le couple k,v
}

// supprime tous les elements, detruit la table et retourne une table vide
hashtable_t hashtable_delete(hashtable_t t) {
    for (int i = 0; i < t.size; i++) {
        if (!list_is_empty(t.data[i])) {
            list_delete(t.data[i]);
            free(t.data[i]);
        }
    }
    free(t.data);
    t.size = 0;
    return t;
}




 int get_size_dico(const char * dico ) {
   FILE *f_dico_size = NULL ;
   int size = 0  ;
    if((f_dico_size = fopen(dico,"r")) != NULL){
      char mot[256];

      while(fscanf(f_dico_size,"%s",mot) == 1 ){
        size ++  ;
      }
    fclose(f_dico_size);
    }
    return size ;
   }


  void get_texte(hashtable_t hashtable , const char* texte){
  FILE *fp = NULL ;
  FILE *f = NULL ;
 fp = fopen( "MotsPasDansLeDico.txt" , "w" ); // j'ouvre un fichier pour mettre les mots intrus

   if((f = fopen(texte,"r")) != NULL){
     char mot[256];
     

     while(fscanf(f,"%s",mot) == 1 ){
       char * tmp ;
       char * tmp1 ;
       tmp1 = strdup(mot) ;
       tmp  = strtok(tmp1," ,;':-(\"!?)." ) ;
        while (tmp != NULL){

        //printf("hashtable containt %d\n", hashtable_contains(tmp, hashtable));
              if(hashtable_contains(tmp,hashtable)==1){
                if (!isupper(tmp[0])) {
    FILE *fichier = fopen("MotsPasDansLeDico.txt", "a");
    if (fichier != NULL) {
      fwrite(tmp, sizeof(char), strlen(tmp), fp);
      fwrite("\n",sizeof(char),1,fp);
      //  fputs(mot, fichier);
       // fputs("\n", fichier);
        fclose(fichier);
    }
}

              //  // printf(" Le mot %s du texte est pas présent dans le dico  \n ",tmp1);
              //          fwrite(tmp, sizeof(char), strlen(tmp), fp);
              //           fwrite("\n",sizeof(char),1,fp);

              }

         tmp = strtok (NULL, " ,;':-(\"!?).");

        }
        free(tmp);
        free(tmp1);
     }
   
  //free(dico);
  fclose(f);
  fclose(fp);
   }
}

void verification(const char * dico , const char * texte) { 
    int taille_dico  ;
      hashtable_t dico_hashtable ;
      double taille = 0  ;
      double size_bytes = 0  ;

      taille_dico = get_size_dico(dico);
      printf("taille dico = %d\n",taille_dico);

      dico_hashtable = hashtable_new(taille_dico);

    

      get_dico(dico_hashtable,dico);


      get_texte(dico_hashtable,texte);

}




int analyse_performance(const char *dictionnaire, const char *texte)
{
  clock_t debut, fin, debut1, fin1;

      int taille_dico  ;
      hashtable_t dico_hashtable ;
      double taille = 0  ;
      double size_bytes = 0  ;

      taille_dico = get_size_dico(dictionnaire);
      printf("taille dico = %d\n",taille_dico);

      dico_hashtable = hashtable_new(taille_dico);

  int nbwords = get_size_dico(dictionnaire);

  FILE *ftemps = fopen("temps.dat", "w");
  for (int k = nbwords; k > 1; k -= nbwords / 100)
  {
    debut = clock();
      get_dico_analyse(dico_hashtable,dictionnaire,k);
    fin = clock();

    //// calcul de la taille réelle du dico en Moctets
    size_bytes = k * sizeof(char *);
    taille = size_bytes / (1024 * 1024);

    debut1 = clock();
    get_texte(dico_hashtable,texte);
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




int main(int ac, char** av) {
  clock_t debut, fin;


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
       clock_t debut = clock();  
      verification(dictionnaire, texte);
      clock_t fin = clock(); 
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
