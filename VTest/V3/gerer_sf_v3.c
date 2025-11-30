#include <stdio.h>
#include <stdlib.h>
#include "bloc.h"
#include "inode.h"
#include "sf.h"

static void creerFichierTest(const char* nom, const char* contenu) {
    FILE *f = fopen(nom, "w");
    if (!f) return;
    fputs(contenu, f);
    fclose(f);
}

int main() {
    printf("TESTS V3\n");

    // créer les fichiers de test
    creerFichierTest("fichier1.txt", "Bonjour SF V3\n");
    creerFichierTest("fichier2.txt", "000000000000000000000000000000000000000000000000000000111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111\n");

    // créer le système de fichiers
    tSF sf = CreerSF("SF_V3");

    // écriture dans le SF
    Ecrire1BlocFichierSF(sf, "fichier1.txt", ORDINAIRE);
    EcrireFichierSF(sf, "fichier2.txt", ORDINAIRE);

    // affichage et sauvegarde
    AfficherSF(sf);
    SauvegarderSF(sf, "sauvegarde_SF_test_V3.txt");

    DetruireSF(&sf);
    return 0;
}

