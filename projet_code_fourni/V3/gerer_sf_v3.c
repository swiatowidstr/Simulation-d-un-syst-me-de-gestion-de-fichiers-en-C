#include <stdio.h>
#include <stdlib.h>
#include "bloc.h"
#include "inode.h"
#include "sf.h"
#include <string.h>

//fonction qui permet de créer un fichier directement avec un contenu dedans pour simplifier les tests
static void creerFichierTest(const char* nom, const char* contenu) {
    FILE *f = fopen(nom, "w");
    if (!f) return;
    fputs(contenu, f);
    fclose(f);
}

int main() {
		
		//TESTS DE sauvegarderBloc et de chargerBloc
		printf("TESTS SAUVEGARDER ET CHARGER BLOC\n");
		
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
    /*
    //test decalage pour ecrireDonneesInode
    printf("EcrireDonneesInode: TEST DECALAGE :\n\n");
		char *texte = "Bonjour je m'appelle swiatowid et je suis en L2 informatique etle projet commence a devenir vrm long";
		char *texte1 = "1234";
		char *texte2 = "5678";
		char *texte3 = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
		char *texte4 = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
		*/
		
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
    
    
		/*
    printf("EcrireDonneesInode: TEST DECALAGE :\n\n");
		printf("TEST 1\n");
    
    tInode inode4 = CreerInode(4, ORDINAIRE);
    long ecrits = EcrireDonneesInode(inode4, (unsigned char*)texte, strlen(texte), 10);
    AfficherInode(inode4);
    
    long taille = Taille(inode4);
    unsigned char contenu4[200];
    LireDonneesInode(inode4, contenu4, taille, 10);
    printf("%s", contenu4);
    
    DetruireInode(&inode4);
    */
    
    /*
    printf("\n TEST 2\n");
    
    tInode inode5 = CreerInode(5, ORDINAIRE);
    ecrits = EcrireDonneesInode(inode5, (unsigned char*)texte, strlen(texte), 0);
    AfficherInode(inode5);
    
    tInode inode6 = CreerInode(5, ORDINAIRE);
    taille = Taille(inode5);
    unsigned char contenu5[200];
    long lus = LireDonneesInode(inode6, contenu5, 10, 10);
    AfficherInode(inode5);
    
    DetruireInode(&inode5);
    DetruireInode(&inode6);
    
    */
    
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

/*

    // ============================================
    // Tests des fonctions avec décalage
    // ============================================
    
    printf("=== Tests EcrireDonneesInode/LireDonneesInode ===\n");
    
    // Test 1 : Exemple 1 de l'énoncé
    printf("Test 1 : Taille=100, decalage=80, taille=50\n");
    tInode inode1 = CreerInode(1, ORDINAIRE);
    
    // Créer un fichier avec 100 caractères 'A' à 'Z' répétés
    creerFichierTest("test100.txt", "");
    FILE *f = fopen("test100.txt", "wb");
    for (int i = 0; i < 100; i++) {
        fputc('A' + (i % 26), f);
    }
    fclose(f);
    
    // Lire le fichier et écrire dans l'inode
    f = fopen("test100.txt", "rb");
    fread(buffer1, 1, 100, f);
    fclose(f);
    EcrireDonneesInode(inode1, buffer1, 100, 0);
    
    // Préparer 50 'X'
    for (int i = 0; i < 50; i++) {
        buffer2[i] = 'X';
    }
    
    // Écrire 50 octets avec décalage 80
    long ecrits = EcrireDonneesInode(inode1, buffer2, 50, 80);
    printf("Octets ecrits : %ld (attendu : 50)\n", ecrits);
    
    // Lecture avec décalage 80, taille 50
    unsigned char lu1[50];
    long lus = LireDonneesInode(inode1, lu1, 50, 80);
    printf("Octets lus : %ld (attendu : 20)\n", lus);
    
    AfficherInode(inode1);
    DetruireInode(&inode1);
    remove("test100.txt");
    
    printf("\n");
    
    // Test 2 : Exemple 2 de l'énoncé
    printf("Test 2 : Taille=300, decalage=200, taille=500\n");
    tInode inode2 = CreerInode(2, ORDINAIRE);
    
    // Créer un fichier avec 300 caractères
    creerFichierTest("test300.txt", "");
    f = fopen("test300.txt", "wb");
    for (int i = 0; i < 300; i++) {
        fputc('B' + (i % 26), f);
    }
    fclose(f);
    
    // Lire et écrire dans l'inode
    f = fopen("test300.txt", "rb");
    fread(buffer1, 1, 300, f);
    fclose(f);
    EcrireDonneesInode(inode2, buffer1, 300, 0);
    
    // Préparer 500 'Y'
    for (int i = 0; i < 500; i++) {
        buffer2[i] = 'Y';
    }
    
    // Écrire 500 octets avec décalage 200
    ecrits = EcrireDonneesInode(inode2, buffer2, 500, 200);
    printf("Octets ecrits : %ld (attendu : 440)\n", ecrits);
    
    // Lecture avec décalage 200, taille 500
    unsigned char lu2[500];
    lus = LireDonneesInode(inode2, lu2, 500, 200);
    printf("Octets lus : %ld (attendu : 100)\n", lus);
    
    DetruireInode(&inode2);
    remove("test300.txt");
    
    printf("\n");
    
    // Test 3 : Exemple 3 de l'énoncé
    printf("Test 3 : Taille=400, decalage=500, taille=100\n");
    tInode inode3 = CreerInode(3, ORDINAIRE);
    
    // Créer un fichier avec 400 caractères
    creerFichierTest("test400.txt", "");
    f = fopen("test400.txt", "wb");
    for (int i = 0; i < 400; i++) {
        fputc('C' + (i % 26), f);
    }
    fclose(f);
    
    // Lire et écrire dans l'inode
    f = fopen("test400.txt", "rb");
    fread(buffer1, 1, 400, f);
    fclose(f);
    EcrireDonneesInode(inode3, buffer1, 400, 0);
    
    // Préparer 100 'Z'
    for (int i = 0; i < 100; i++) {
        buffer2[i] = 'Z';
    }
    
    // Écrire 100 octets avec décalage 500
    ecrits = EcrireDonneesInode(inode3, buffer2, 100, 500);
    printf("Octets ecrits : %ld (attendu : 100)\n", ecrits);
    
    // Lecture avec décalage 500, taille 100
    unsigned char lu3[100];
    lus = LireDonneesInode(inode3, lu3, 100, 500);
    printf("Octets lus : %ld (attendu : 0)\n", lus);
    
    DetruireInode(&inode3);
    remove("test400.txt");
    
    printf("\n");
    
    // ============================================
    // Test de l'affichage modifié
    // ============================================
    
    printf("=== Test affichage inode avec contenu des blocs ===\n");
    
    tInode inode4 = CreerInode(4, ORDINAIRE);
    char *texte = "Ceci est un texte qui depasse un bloc pour tester l'affichage complet.";
    creerFichierTest("texte.txt", texte);
    
    f = fopen("texte.txt", "rb");
    fseek(f, 0, SEEK_END);
    long taille = ftell(f);
    fseek(f, 0, SEEK_SET);
    unsigned char *contenu = malloc(taille);
    fread(contenu, 1, taille, f);
    fclose(f);
    
    EcrireDonneesInode(inode4, contenu, taille, 0);
    free(contenu);
    
    AfficherInode(inode4);
    
    DetruireInode(&inode4);
    remove("texte.txt");
    
    printf("\n");
    
    // ============================================
    // Tests de sauvegarde/chargement d'inodes
    // ============================================
    
    printf("=== Tests sauvegarde/chargement inode ===\n");
    
    tInode inode5 = CreerInode(5, ORDINAIRE);
    char *texte_complet = "Donnees completes pour un inode avec plusieurs blocs de donnees.";
    creerFichierTest("complet.txt", texte_complet);
    
    f = fopen("complet.txt", "rb");
    fseek(f, 0, SEEK_END);
    taille = ftell(f);
    fseek(f, 0, SEEK_SET);
    contenu = malloc(taille);
    fread(contenu, 1, taille, f);
    fclose(f);
    
    EcrireDonneesInode(inode5, contenu, taille, 0);
    free(contenu);
    
    fichier = fopen("test_inode.bin", "wb");
    if (fichier) {
        int resultat = SauvegarderInode(inode5, fichier);
        if (resultat == 0) {
            printf("Sauvegarde inode : OK\n");
        } else {
            printf("Sauvegarde inode : ERREUR\n");
        }
        fclose(fichier);
    }
    
    tInode inode6 = NULL;
    fichier = fopen("test_inode.bin", "rb");
    if (fichier) {
        int resultat = ChargerInode(&inode6, fichier);
        if (resultat == 0) {
            printf("Chargement inode : OK\n");
        } else {
            printf("Chargement inode : ERREUR\n");
        }
        fclose(fichier);
    }
    
    if (inode6) {
        AfficherInode(inode6);
        DetruireInode(&inode6);
    }
    
    DetruireInode(&inode5);
    remove("test_inode.bin");
    remove("complet.txt");
    
    printf("\n");
    
    // ============================================
    // Tests du système de fichiers
    // ============================================
    
    printf("=== Tests systeme de fichiers ===\n");
    
    // Test EcrireFichierSF
    printf("Test EcrireFichierSF\n");
    
    // Création d'un fichier de test avec 700 octets (dépasse la limite de 640)
    creerFichierTest("fichier_test.txt", "");
    f = fopen("fichier_test.txt", "wb");
    for (int i = 0; i < 700; i++) {
        fputc('T', f);
    }
    fclose(f);
    
    tSF sf = CreerSF("MonDisque");
    if (sf) {
        long octets_ecrits = EcrireFichierSF(sf, "fichier_test.txt", ORDINAIRE);
        printf("Octets ecrits dans SF : %ld (max 640)\n", octets_ecrits);
        
        // Sauvegarde du SF
        if (SauvegarderSF(sf, "sauvegarde.sf") == 0) {
            printf("Sauvegarde SF : OK\n");
        } else {
            printf("Sauvegarde SF : ERREUR\n");
        }
        
        AfficherSF(sf);
        
        // Chargement du SF
        tSF sf_charge = NULL;
        if (ChargerSF(&sf_charge, "sauvegarde.sf") == 0) {
            printf("Chargement SF : OK\n");
            AfficherSF(sf_charge);
            DetruireSF(&sf_charge);
        } else {
            printf("Chargement SF : ERREUR\n");
        }
        
        DetruireSF(&sf);
    }
    
    // Nettoyage
    remove("fichier_test.txt");
    remove("sauvegarde.sf");
    
    printf("\n=== Fin des tests ===\n");
    
    return 0;


*/
