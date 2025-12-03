#include <stdio.h>
#include <stdlib.h>
#include "sf.h"
#include "inode.h"

static void creerFichierTest(const char* nom, const char* contenu) {
    FILE *f = fopen(nom, "w");
    if (!f) return;
    fputs(contenu, f);
    fclose(f);
}

int main() {
	
	printf("TESTS V2\n");
	//nom du disque
	char nomDisque[] = "sda";
	
	creerFichierTest("fichier1.txt", "Bonjour, ceci est un test");
	creerFichierTest("fichier2.txt", "Bonjour, ceci est un test plus longgggggggggggggggggggggggggggggggggggggggggg");
	
	//création du système de fichiers
	tSF nouvSF = CreerSF(nomDisque);
	printf("SF crée avec succès\n");
	
	char fichier1[] = "fichier1.txt";
	long ecrit1 = Ecrire1BlocFichierSF(nouvSF, fichier1, ORDINAIRE);
	
	char fichier2[] = "fichier2.txt";
	long ecrit2 = Ecrire1BlocFichierSF(nouvSF, fichier2, ORDINAIRE);
	printf("affichage du SF\n");
	AfficherSF(nouvSF);
	DetruireSF(&nouvSF);
	remove("fichier1.txt");
	remove("fichier2.txt");
	

	
	return 0;
}
