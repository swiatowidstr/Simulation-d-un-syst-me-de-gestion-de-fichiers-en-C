#include <stdio.h>
#include <stdlib.h>
#include "sf.h"
#include "inode.h"

int main() {
	
	printf("TESTS V2\n");
	//nom du disque
	char nomDisque[] = "sda";
	//création du système de fichiers
	tSF nouvSF = CreerSF(nomDisque);
	printf("SF crée avec succès\n");
	
	char fichier1[] = "fichier1.txt";
	long ecrit1 = Ecrire1BlocFichierSF(nouvSF, fichier1, ORDINAIRE);
	
	char fichier2[] = "fichier2";
	long ecrit2 = Ecrire1BlocFichierSF(nouvSF, fichier2, ORDINAIRE);
	
	char fichier3[] = "fichier3.txt";
	long ecrit3 = Ecrire1BlocFichierSF(nouvSF, fichier3, ORDINAIRE);
	
	char fichier4[] = "fichier4.txt";
	long ecrit4 = Ecrire1BlocFichierSF(nouvSF, fichier4, ORDINAIRE);
	
	char fichier5[] = "fichier5.txt";
	long ecrit5 = Ecrire1BlocFichierSF(nouvSF, fichier5, ORDINAIRE);
	
	printf("affichage du SF\n");
	AfficherSF(nouvSF);
	DetruireSF(&nouvSF);
	

	
	return 0;
}
