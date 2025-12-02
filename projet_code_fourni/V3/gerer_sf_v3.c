#include <stdio.h>
#include <stdlib.h>
#include "bloc.h"
#include "inode.h"
#include "sf.h"
#include <string.h>

static void creerFichierTest(const char* nom, const char* contenu) {
    FILE *f = fopen(nom, "w");
    if (!f) return;
    fputs(contenu, f);
    fclose(f);
}

int main() {
		/*
		//TODO AJOUTER DES TESTS
    printf("TESTS V3:\n\n\n");
		
    // créer les fichiers de test
    creerFichierTest("fichier1.txt", "Bonjour SF V3 nananananannananananannana je parle bcp\n");
    creerFichierTest("fichier2.txt", "0000000000000000000000000000000000000000000000000000001122222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222221111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111abcabcAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
		creerFichierTest("fichier3.txt", "Ce Fichier comporte des caractères et\ndes sautes de lignes\net encore des sauts de lignes\net encore\net encore");
    // créer le système de fichiers
    tSF sf = CreerSF("SF_V3");

    // écriture dans le SF
    Ecrire1BlocFichierSF(sf, "fichier1.txt", ORDINAIRE);
    EcrireFichierSF(sf, "fichier2.txt", ORDINAIRE);
    EcrireFichierSF(sf, "fichier3.txt", ORDINAIRE);

    // affichage et sauvegarde
    AfficherSF(sf);
    SauvegarderSF(sf, "sauvegarde_SF_test_V3.bin");
		

    DetruireSF(&sf);
    printf("\n\n\n");
    */
    
    //test decalage pour ecrireDonneesInode
    printf("EcrireDonneesInode: TEST DECALAGE :\n\n");
		char *texte = "Bonjour je m'appelle swiatowid et je suis en L2 informatique etle projet commence a devenir vrm long";
		char *texte1 = "1234";
		char *texte2 = "5678";
		char *texte3 = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
		char *texte4 = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
		
		/*
		printf("\n\nTEST 1\n");
		tInode inode1 = CreerInode(1, ORDINAIRE);
		long ecrits = EcrireDonneesInode(inode1, (unsigned char*)texte, strlen(texte), 200);
		AfficherInode(inode1);
		ecrits = EcrireDonneesInode(inode1, (unsigned char*)texte3, 500, 200);
		printf("\n octets ecrits :%ld\n", ecrits);
		AfficherInode(inode1);
    DetruireInode(&inode1);
    printf("\n");
    */
    /*
    printf("\n\nTEST 2\n");
    tInode inode2 = CreerInode(2, ORDINAIRE);
		long ecrits = EcrireDonneesInode(inode2, (unsigned char*)texte4, strlen(texte4), 0);
		AfficherInode(inode2);
		ecrits = EcrireDonneesInode(inode2, (unsigned char*)texte3, 500, 200);
		printf("\noctets écrits : %ld\n", ecrits);
		AfficherInode(inode2);
    DetruireInode(&inode2);
    printf("\n");
    
    printf("\n\nTEST 3\n");
    tInode inode3 = CreerInode(3, ORDINAIRE);
		ecrits = EcrireDonneesInode(inode3, (unsigned char*)texte, strlen(texte), 300);
		AfficherInode(inode3);
		ecrits = EcrireDonneesInode(inode3, (unsigned char*)texte, 100, 500);
		printf("\n octets ecrits : %ld\n", ecrits);
		AfficherInode(inode3);
    DetruireInode(&inode3);
    printf("\n");
    */
    
    //tests pour lire
    
    printf("EcrireDonneesInode: TEST DECALAGE :\n\n");
		printf("TEST 1\n");
    
    tInode inode4 = CreerInode(4, ORDINAIRE);
    long ecrits = EcrireDonneesInode(inode4, (unsigned char*)texte, strlen(texte), 0);
    AfficherInode(inode4);
    
    long taille = Taille(inode4);
    unsigned char contenu4[200];
    LireDonneesInode(inode4, contenu4, taille, 0);
    AfficherInode(inode4);
    
    DetruireInode(&inode4);
    
    printf("\n TEST 2\n");
    
    tInode inode5 = CreerInode(5, ORDINAIRE);
    ecrits = EcrireDonneesInode(inode5, (unsigned char*)texte, strlen(texte), 0);
    AfficherInode(inode5);
    
    tInode inode6 = CreerInode(5, ORDINAIRE);
    taille = Taille(inode5);
    unsigned char contenu5[200];
    long lus = LireDonneesInode(inode6, contenu5, taille, 10);
    AfficherInode(inode6);
    
    DetruireInode(&inode5);
    DetruireInode(&inode6);
    
    /*
    //test chargerSF
    printf("TEST AVEC LE FICHIER SF CHARGÉ PRÉCÉDEMENT:\n\n\n");
    
		tSF sf2 = NULL;
		ChargerSF(&sf2, "sauvegarde_SF_test_V3.bin");
		
		AfficherSF(sf2);
		DetruireSF(&sf2);
		*/
    return 0;
}

