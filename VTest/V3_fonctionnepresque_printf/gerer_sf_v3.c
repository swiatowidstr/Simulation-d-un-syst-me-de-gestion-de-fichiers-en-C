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
    printf("TESTS V3\n");
		
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
    /*
    printf("\n\n\n");
    printf("test décalage\n");
    char *texte = "Bonjour je m'appelle swiatowisd et je suis en L2 informatique et le projet commence a devenir vrm long";
    tInode inode1 = CreerInode(1, ORDINAIRE);
    printf("affichage inode1\n");
    AfficherInode(inode1);
    
    long octets_ecrits = EcrireDonneesInode(inode1, (unsigned char*)texte, strlen(texte), 10);
    
    AfficherInode(inode1); 
    
    DetruireInode(&inode1);
    */
    printf("\n\n\n");
    
    printf("test avec le sf chargé depuis le fichier enregistré précédement\n");
    
		tSF sf2 = NULL;
		ChargerSF(&sf2, "sauvegarde_SF_test_V3.bin");
		
		AfficherSF(sf2);
		DetruireSF(&sf2);
		
    return 0;
}

