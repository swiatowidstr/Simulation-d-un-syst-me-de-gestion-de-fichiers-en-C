#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inode.h"
#include "bloc.h"
#include <stdbool.h>


int main(void) {

	char *texte1 = "Ceci est le contenu du premier inode.";
        
	char *texte2 =
        "Ceci est le contenu du deuxième inode. loulauloaualaua\n"
        "lalaalalla bonjour bonjour aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaallllllll"
        "corinevoenronervon";
        
	char *texte3 = "";
	
	char *texte4 = " ";
	
	char *texte5 = "a";
	
	char *texte6 = "ABC\0DEF";
	size_t taille6 = 7;
	
	char *texte7 =
								"Ceci est le contenu.\n"
								"Du 7 ème inode.";
	
	char texte8[65];
	for (int i=0; i<64; i++) texte8[i] = 'A';
	texte8[64] = '\0';
	
	unsigned char buffer[TAILLE_BLOC];

	printf("\n ------------------TESTS DE LA V1------------------\n");
	printf("\ncas inode de base avec mois d'octets que le max:\n");
	tInode inode1 = CreerInode(1, AUTRE);  
	EcrireDonneesInode1bloc(inode1, (unsigned char*)texte1, strlen(texte1));
	AfficherInode(inode1);
	DetruireInode(&inode1);
	
	printf("\ncas inode avec beacoup de texteet des sauts de ligne:\n");
	tInode inode2 = CreerInode(2, ORDINAIRE);
	EcrireDonneesInode1bloc(inode2, (unsigned char*)texte2, strlen(texte2));
	AfficherInode(inode2);
	DetruireInode(&inode2);
	
	printf("\ncas inode avec une chaine de caractères vide:\n");
	tInode inode3 = CreerInode(3, ORDINAIRE);
	EcrireDonneesInode1bloc(inode3, (unsigned char*)texte3, strlen(texte3));
	AfficherInode(inode3);
	DetruireInode(&inode3);
	
	printf("\ncas inode avec un seul espace:\n");
	tInode inode4 = CreerInode(4, ORDINAIRE);
	EcrireDonneesInode1bloc(inode4, (unsigned char*)texte4, strlen(texte4));
	AfficherInode(inode4);
	DetruireInode(&inode4);
	
	printf("\ncas inode avec un seul octet:\n");
	tInode inode5 = CreerInode(5, ORDINAIRE);
	EcrireDonneesInode1bloc(inode5, (unsigned char*)texte5, strlen(texte5));
	AfficherInode(inode5);
	DetruireInode(&inode5);
	
	printf("\ncas inode avec une fin de chaine de caractères au milieu en utilisant le caractère fin de chaine:\n");
	tInode inode6 = CreerInode(6, ORDINAIRE);
	EcrireDonneesInode1bloc(inode6, (unsigned char*)texte6, taille6);
	AfficherInode(inode6);
	DetruireInode(&inode6);
	
	printf("\ncas inode avec un saut de ligne a l'interieur:\n");
	tInode inode7 = CreerInode(7, ORDINAIRE);
	EcrireDonneesInode1bloc(inode7, (unsigned char*)texte7, strlen(texte7));
	AfficherInode(inode7);
	DetruireInode(&inode7);
	
	printf("\ncas inode avec exactement 64 octets:\n");
	tInode inode8 = CreerInode(8, ORDINAIRE);
	EcrireDonneesInode1bloc(inode8, (unsigned char*)texte8, strlen(texte8));
	AfficherInode(inode8);
	DetruireInode(&inode8);
	
	printf("\ncas inode vide:\n");
	AfficherInode(NULL);
	EcrireDonneesInode1bloc(NULL, (unsigned char*)"abc", 3);
	LireDonneesInode1bloc(NULL, buffer, 10);
	
	printf("\ncas des inodes avec des scanf de l'utilisateur en utilisant une fonction qui lit une chaine de caractères pour la mettre dans un inode:\n");

	
	bool continuer = true;
	int numInode = 9;
	while (continuer == true) {
		printf("Voulez vous faire un test avec une chaine de caractères entrée par l'utilisateur ?(o/n)\n");
		char rep;
		scanf(" %c", &rep);
		if (rep == 'o' || rep == 'O') {
			printf("Entrez une chaine de caractères:\n");
			char texte[256];
			scanf(" %257[^\n]", texte);
			tInode inode = CreerInode(numInode, ORDINAIRE);
			EcrireDonneesInode1bloc(inode, (unsigned char*)texte, strlen(texte));
			AfficherInode(inode);
			DetruireInode(&inode);
			continuer = true;
			numInode++;
		}
		else {
			continuer = false;
		}

	}
	
	
	return 0;
}

