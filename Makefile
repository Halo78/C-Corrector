CC=gcc
EXECUTABLE=./Build/


all: Arbre_Prefixe Dichotomie Sequentielle_Redi Sequentielle_simple Arbre_Suffixe Trie Ensemble

Arbre_Prefixe: ./src/Arbre_Prefixe.c
	$(CC) $(CFLAGS) -o $(EXECUTABLE)Prefix ./src/Arbre_Prefixe.c

Arbre_Suffixe: ./src/Arbre_Suffixe.c
	$(CC) $(CFLAGS) -o $(EXECUTABLE)Suffix ./src/Arbre_Suffixe.c

Dichotomie: ./src/Dichotomie.c
	$(CC) $(CFLAGS) -o $(EXECUTABLE)Dichotomie ./src/Dichotomie.c

Sequentielle_Redi: ./src/Tab_recherche_séquentielle.c
	$(CC) $(CFLAGS) -o $(EXECUTABLE)Sequentielle_Redi ./src/Tab_recherche_séquentielle.c

Sequentielle_simple: ./src/Tab_recherche_séquentielle.c
	$(CC) $(CFLAGS) -o $(EXECUTABLE)Sequentielle_simple ./src/Tab_recherche_séquentielle.c

Trie: ./src/Trie.c
	$(CC) $(CFLAGS) -o $(EXECUTABLE)Trie ./src/Trie.c

Ensemble: ./src/Ensemble.c
	$(CC) $(CFLAGS) -o $(EXECUTABLE)Ensemble ./src/Ensemble.c ./src/Element.c ./src/List.c

clean:
	rm -f $(EXECUTABLE)Prefix $(EXECUTABLE)Sequentielle_simple $(EXECUTABLE)Trie  $(EXECUTABLE)Sequentielle_Redi $(EXECUTABLE)Dichotomie $(EXECUTABLE)Suffix $(EXECUTABLE)Ensemble
