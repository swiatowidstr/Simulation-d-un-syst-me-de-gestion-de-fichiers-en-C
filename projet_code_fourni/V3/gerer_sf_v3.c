#include <stdio.h>
#include <stdlib.h>
#include "bloc.h"
#include "inode.h"
#include "sf.h"
#include <string.h>
#define NB_BLOCS_DIRECTS 10

static void creerFichierTest(const char* nom, const char* contenu) {
    FILE *f = fopen(nom, "w");
    if (!f) return;
    fputs(contenu, f);
    fclose(f);
}

static void AfficherContenu(unsigned char *contenu, long taille) {
	for (long i = 0; i < taille; i++) {
    	printf("%c", contenu[i]);
    }
    printf("\n");
}

//test de sauvegarder et chargement de bloc
static void TestSauvegarderChargerBloc() {
	printf("\nTEST BLOC: SauvegarderBloc ChargerBloc\n");
	
	tBloc bloc1 = CreerBloc();
	tBloc bloc2 = CreerBloc();
	unsigned char contenu[] = "Contenu du bloc pour le test de sauvegarder";
	EcrireContenuBloc(bloc1, contenu, strlen((char*)contenu));
	
	FILE *f = fopen("test_sauvegarder_bloc.bin", "wb");
	if (f !=  NULL) {
		int resultat = SauvegarderBloc(bloc1, strlen((char*)contenu), f);
		if (resultat == 0) {
			printf("sauvegarde du bloc réussie\n");
		}
		else {
			printf("sauvegarde du bloc erreur\n");
		}
		fclose(f);
	}
	
	f = fopen("test_sauvegarder_bloc.bin", "rb");
	if (f != NULL) {
		int resultat = ChargerBloc(bloc2, strlen((char*)contenu), f);
		if (resultat == 0) {
			printf("bloc chargement réussi\n");
		}
		else {
			printf("echec chargement du bloc\n");
		}
		fclose(f);
	}
	
	unsigned char contenu1[TAILLE_BLOC];
	unsigned char contenu2[TAILLE_BLOC];
	LireContenuBloc(bloc1, contenu1, TAILLE_BLOC);
	LireContenuBloc(bloc2, contenu2, TAILLE_BLOC);
	
	printf("%s\n", contenu1);
	printf("%s\n", contenu2);
	
	DetruireBloc(&bloc1);
	DetruireBloc(&bloc2);
	remove("test_sauvegarder_bloc.bin");
	printf("\n");
}


//test de Lire et ecrire donnees Inode
static void TestEcrireLireDonneesInode() {
    printf("\nTEST INODE: EcrireDonneesInode LireDonneesInode\n");

    char *texte = "bonjour je m'appelle swiatowid et je suis en L2";
    tInode inode = CreerInode(1, ORDINAIRE);

    long ecrits = EcrireDonneesInode(inode, (unsigned char*)texte, strlen(texte), 0);
    AfficherInode(inode);

    unsigned char contenu[TAILLE_BLOC * NB_BLOCS_DIRECTS];
    long lus = LireDonneesInode(inode, contenu, strlen(texte), 0);
    contenu[lus] = '\0';
    AfficherContenu(contenu, lus);

    char *texte2 = "test";
    ecrits = EcrireDonneesInode(inode, (unsigned char*)texte2, strlen(texte2), 10);
    printf("octets écrits avec le décalage : %ld\n", ecrits);
    AfficherInode(inode);

    lus = LireDonneesInode(inode, contenu, sizeof(contenu), 0);
    contenu[lus] = '\0';
    AfficherContenu(contenu, lus);

    DetruireInode(&inode);
    printf("\n");
    
    
    //tests un peu plus précis pour lire et ecrire Donnees inode 
    
    tInode inode10 = CreerInode(10, ORDINAIRE);
    char *texte3 = "azuibcaizuebuiazbvbaezruivbazvubzervze";
    ecrits =  EcrireDonneesInode(inode10, (unsigned char*)texte3, strlen(texte3), 0);
    AfficherInode(inode10);
    
    
    char *texte4 = "BONJOUR";
    ecrits = EcrireDonneesInode(inode10, (unsigned char*)texte4, strlen(texte4), TAILLE_BLOC + 10);
    AfficherInode(inode10);
    
    //on test l'écriture quand elle dépasse la taille max d'un fichier
    unsigned char grosTexte[1000];
    for (int i = 0; i < 1000; i++) {
    	grosTexte[i] = 'A';
    }
    
    ecrits = EcrireDonneesInode(inode10, grosTexte, 1000, 0);
    AfficherInode(inode10);
    //test lecture quand le décalage dépasse la taille du fichier
    unsigned char buffer[1000];
    lus = LireDonneesInode(inode10, buffer, 100, 800);
    DetruireInode(&inode10);
    printf("\n");
    
}



//test de sauvegarder et charger inode
static void TestSauvegarderChargerInode() {
	printf("\nTEST INODE: sauvegarderInode ChargerInode\n");
	
	tInode inode = CreerInode(2, ORDINAIRE);
	char *texte = "Dans ce fichier il y a le texte qui sert a tester si l'inode se sauvegarde bien";
	EcrireDonneesInode(inode, (unsigned char*)texte, strlen(texte), 0);
	
	FILE *f = fopen("inode_test.bin", "wb");
	if (f != NULL) {
		SauvegarderInode(inode, f);
		fclose(f);
	}
	
	tInode inodeCharger = NULL;
	f = fopen("inode_test.bin", "rb");
	if (f != NULL) {
		ChargerInode(&inodeCharger, f);
		fclose(f);
	}
	
	AfficherInode(inode);
	AfficherInode(inodeCharger);
	DetruireInode(&inode);
	DetruireInode(&inodeCharger);
	remove("inode_test.bin");
	printf("\n");
}

static void TestAfficherInode() {
    printf("\nTEST INODE: AfficherInode\n");

    tInode inode = CreerInode(42, ORDINAIRE);
    char *txt = "Test d'affichage complet de l'inode\n eurvnizuernvize\nziervbezi\nziuerv\nzierhvb\n\n\nvzerv\n\n\n\n\nuzehrvi";
    EcrireDonneesInode(inode, (unsigned char*)txt, strlen(txt), 0);

    AfficherInode(inode);

    DetruireInode(&inode);
    printf("\n");
}

// test qui écrit un fichier dans le sf
static void TestEcrireFichierSF() {
	printf("TEST SF: EcrireFichierSF\n");
	
	creerFichierTest("fichier1.txt", "Bonjour, ceci est le fichier test de la fonction EcrireFichierSF.");
	creerFichierTest("fichier2.txt", "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
	tSF sf = CreerSF("SF_test_V3");
	
	long ecrits = EcrireFichierSF(sf, "fichier1.txt", ORDINAIRE);
	printf("octets ecrits : %ld\n", ecrits);
	
	AfficherSF(sf);
	
	
	ecrits = EcrireFichierSF(sf, "fichier2.txt", ORDINAIRE);
	printf("octets ecrits : %ld\n", ecrits);
	printf("affichage du sf après avoir écrit plus de la taille max de données\n");
	AfficherSF(sf);
	
	DetruireSF(&sf);
	remove("fichier1.txt");
	remove("fichier2.txt");
	printf("\n");
}

//test qui sauvegarde et charge le sf sur un fichier
static void testSauvegarderChargerSF() {
	printf("TEST SF: SauvegarderSF ChargerSF\n");
	
	tSF sf = CreerSF("SF2_V3");
	
	creerFichierTest("fichier1.txt", "AAAAAAAAAA");
	creerFichierTest("fichier2.txt", "BBBBBBBBBB");
	
	EcrireFichierSF(sf, "fichier1.txt", ORDINAIRE);
	EcrireFichierSF(sf, "fichier2.txt", ORDINAIRE);
	
	SauvegarderSF(sf, "sf_test.bin");
	
	tSF sf2 = NULL;
	ChargerSF(&sf2, "sf_test.bin");
	
	AfficherSF(sf);
	AfficherSF(sf2);
	
	DetruireSF(&sf);
	DetruireSF(&sf2);
	remove("fichier1.txt");
	remove("fichier2.txt");
	remove("sf_test.bin");
	printf("\n");
}

//on appelle toutes les fonctions de test dans le main
int main() {
		TestSauvegarderChargerBloc();
		TestAfficherInode();
		TestSauvegarderChargerInode();
		TestEcrireLireDonneesInode();
		TestEcrireFichierSF();
		testSauvegarderChargerSF();
    return 0;
}

