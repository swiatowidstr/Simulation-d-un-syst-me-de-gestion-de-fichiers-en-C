#include <stdio.h>
#include <stdlib.h>
#include "sf.h"
#include "inode.h"

int main() {
	
	// Nom du disque
	char nomDisque[] = "sda";
	// Création du système de fichiers
	tSF nouvSF = CreerSF(nomDisque);
	
	// Ajout de 5 fichiers
	char fichier1[] = "fichier1.txt";
	long ecrit1 = Ecrire1BlocFichierSF(nouvSF, fichier1, ORDINAIRE);
	
	char fichier2[] = "fichier2.txt";
	long ecrit2 = Ecrire1BlocFichierSF(nouvSF, fichier2, ORDINAIRE);
	
	char fichier3[] = "fichier3.txt";
	long ecrit3 = Ecrire1BlocFichierSF(nouvSF, fichier3, ORDINAIRE);
	
	char fichier4[] = "fichier4.txt";
	long ecrit4 = Ecrire1BlocFichierSF(nouvSF, fichier4, ORDINAIRE);
	
	char fichier5[] = "fichier5.txt";
	long ecrit5 = Ecrire1BlocFichierSF(nouvSF, fichier5, ORDINAIRE);

	AfficherSF(nouvSF);
	
	// Destruction du SF
	DetruireSF(&nouvSF);
	
	return 0;
}

