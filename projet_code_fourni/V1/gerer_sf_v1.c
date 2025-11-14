#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inode.h"
#include "bloc.h"


int main(void) {

	char *texte1 =
        "Ceci est le contenu du premier inode.";
	char *texte2 =
        "Ceci est le contenu du deuxième inode. loulauloaualaua"
        "lalaalalla bonjour bonjour aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaallllllll";
	
	tInode inode1 = CreerInode(1, AUTRE);  
	
	EcrireDonneesInode1bloc(inode1, (unsigned char*)texte1, strlen(texte1));
	
	AfficherInode(inode1);
	DetruireInode(&inode1);
	
	tInode inode2 = CreerInode(2, ORDINAIRE);
	
	EcrireDonneesInode1bloc(inode2, (unsigned char*)texte2, strlen(texte2));
	
	AfficherInode(inode2);
	DetruireInode(&inode2);
	return 0;
}

