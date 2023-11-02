#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../Include/Dichotomie.h"
#include <time.h>
#include <math.h>
#include <ctype.h>

table_t table_new(unsigned int n)
{
  table_t t;
  t = malloc(sizeof(*t));
  if (t == NULL)
  {
    printf("erreur d'allocation ");
  }
  t->max_size = n;
  t->data = calloc(n, sizeof(*(t->data)));
  return t;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////PARTIE DICO ///////////////////////////////////////////////////////

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
  printf("Taille OK !\n");
  return size;
}

void get_dico_analyse(table_t tab, const char *dico, int k)
{
  FILE *f_dico = NULL;
  int i = 0;
  if ((f_dico = fopen(dico, "r")) != NULL)
  {
    char mot[256];
    while (fscanf(f_dico, "%s", mot) == 1 && i < k)
    {
      tab->data[i] = strdup(mot);
      ;
      i++;
    }
    fclose(f_dico);
  }
}

void get_dico(table_t tab, const char *dico)
{
  FILE *f_dico = NULL;
  int i = 0;
  if ((f_dico = fopen(dico, "r")) != NULL)
  {
    char mot[256];
    while (fscanf(f_dico, "%s", mot) == 1 )
    {
      tab->data[i] = strdup(mot);
      ;
      i++;
    }
    fclose(f_dico);
  }
}


void compare(const char *dictionnaire, const char *texte)
{
  FILE *fp = NULL;
  FILE *f = NULL;
  table_t dico = table_new(get_size_dico(dictionnaire));
  get_dico(dico, dictionnaire);

  fp = fopen("Intrus.txt", "wb"); // j'ouvre un fichier pour mettre les mots intrus
  if ((f = fopen(texte, "r")) != NULL)
  {
    char mot[256];
    while (fscanf(f, "%s", mot) == 1)
    {
      char *tmp = strtok(strdup(mot), " ,«»;’':-(\"!?).");
      while (tmp != NULL)
      {
        int left = 0, right = dico->max_size - 1;
        while (left <= right)
        {
          int mid = (left + right) / 2;
          int cmp = strcasecmp(tmp, dico->data[mid]);
          if (cmp == 0)
          {
            break;
          }
          else if (cmp < 0)
          {
            right = mid - 1;
          }
          else
          {
            left = mid + 1;
          }
        }
        if (left > right && isupper(tmp[0]) == 0)
        {
          fwrite(tmp, sizeof(char), strlen(tmp), fp);
          fwrite("\n", sizeof(char), 1, fp);
        }
        tmp = strtok(NULL, " ,«»;'’:-(\"!?).");
      }
    }
  }
  fclose(f);
  fclose(fp);
}


void compare_analyse(table_t dico, const char *texte)
{
  FILE *fp = NULL;
  FILE *f = NULL;

  fp = fopen("Intrus.txt.txt", "w");

  if ((f = fopen(texte, "r")) != NULL)
  {
    char mot[256];
    char *tmp;

    while (fscanf(f, "%s", mot) == 1)
    {
      tmp = strtok(strdup(mot), " ,;':-(\"!?).");
      while (tmp != NULL)
      {
        int is_equal;

        int left = 0, right = dico->max_size - 1;

        while (left <= right)
        {
          int mid = (left + right) / 2;
          if (strcmp(tmp, dico->data[mid]) == 0)
          {
            is_equal = 1;
            break;
          }
          else if (strcmp(tmp, dico->data[mid]) == 1)
          {
            is_equal = 0;
            left = mid + 1;
          }
          else
          {
            right = mid - 1;
          }
        }

        if (is_equal == 0)
        {
          fwrite(tmp, sizeof(char), strlen(tmp), fp);
          fwrite("\n", sizeof(char), 1, fp);
        }

        tmp = strtok(NULL, " ,;':-(\"!?).");
      }
    }
  }
  fclose(f);
  fclose(fp);
}

int analyse_performance(const char *dictionnaire, const char *texte)
{
  clock_t debut, fin, debut1, fin1;

  table_t dico_tab;
  double taille = 0;
  double size_bytes = 0;

  int nbwords = get_size_dico(dictionnaire);

  FILE *ftemps = fopen("temps.dat", "w");
  for (int k = nbwords; k > 1; k -= nbwords / 100)
  {
    debut = clock();

    dico_tab = table_new(k);
    get_dico_analyse(dico_tab, dictionnaire, k);
    fin = clock();

    //// calcul de la taille réelle du dico en Moctets
    size_bytes = k * sizeof(char *);
    taille = size_bytes / (1024 * 1024);

    debut1 = clock();
    compare_analyse(dico_tab, texte);
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
  clock_t debut, fin;
  if (ac != 2 && ac != 3 && ac != 4)
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
      debut = clock();
      compare(dictionnaire, texte);
      fin = clock();
      printf("Verification terminée ! les mots intrus sont dans le fichier Intrus.txt \n");
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