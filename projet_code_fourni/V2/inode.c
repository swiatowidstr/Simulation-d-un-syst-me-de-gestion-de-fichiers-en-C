/**
 * ProgC - Projet Automne 25-26 : Gestion de systèmes de fichiers
 * VERSION 2 = VERSION 1
 * Fichier : inode.c
 * Module de gestion des inodes.
 **/

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "inode.h"
#include "bloc.h"

// Nombre maximal de blocs dans un inode
#define NB_BLOCS_DIRECTS 10

// Définition d'un inode
struct sInode
{
  // Numéro de l'inode
  unsigned int numero;
  // Le type du fichier : ordinaire, répertoire ou autre
  natureFichier type;
  // La taille en octets du fichier
  long taille;
  // Les adresses directes vers les blocs (NB_BLOCS_DIRECTS au maximum)
  tBloc blocDonnees[NB_BLOCS_DIRECTS];
  // Les dates : dernier accès à l'inode, dernière modification du fichier
  // et de l'inode
  time_t dateDerAcces, dateDerModif, dateDerModifInode;
};

/* V1
 * Crée et retourne un inode.
 * Entrées : numéro de l'inode et le type de fichier qui y est associé
 * Retour : l'inode créé ou NULL en cas de problème
 */
tInode CreerInode(int numInode, natureFichier type) {
	
  tInode inode = malloc(sizeof(struct sInode));
  
  if (inode == NULL) {
  	fprintf(stderr, "CreerInode : probleme creation\n");
  	return NULL;
  }
  
  inode->numero = numInode;
  inode->type = type;
  //on initialise les données non spécifiées a 0 et a NULL
  inode->taille = 0;
  for (int i = 0; i < NB_BLOCS_DIRECTS; i++) {
		inode->blocDonnees[i] = NULL;
	}
	//on met le temps actuel pour les dates de dernière modification etc
	time_t tempsActuel = time(NULL);
	inode->dateDerAcces = tempsActuel;
	inode->dateDerModif = tempsActuel;
	inode-> dateDerModifInode = tempsActuel;
  
  return inode;
}

/* V1
 * Détruit un inode.
 * Entrée : l'inode à détruire
 * Retour : aucun
 */
void DetruireInode(tInode *pInode) {
  if (pInode == NULL || *pInode == NULL) {
  	return;
  }
  
  //on détruit les blocs qui constituent l'inode
	for (int i = 0; i < NB_BLOCS_DIRECTS; i++) {
		  if ((*pInode)->blocDonnees[i] != NULL) {
		      DetruireBloc(&(*pInode)->blocDonnees[i]);
		  }
	}
	
	//on détruit l'inode elle meme
  free(*pInode);
 	*pInode = NULL;
}

/* V1
 * Récupère la date de dernier accès à un inode.
 * Entrée : l'inode pour lequel on souhaite connaître la date de dernier accès
 * Retour : la date de dernier accès à l'inode
 */
time_t DateDerAcces(tInode inode) {
  return inode->dateDerAcces;
}

/* V1
 * Récupère la date de dernière modification d'un inode.
 * Entrée : l'inode pour lequel on souhaite connaître la date de dernière modification
 * Retour : la date de dernière modification de l'inode
 */
time_t DateDerModif(tInode inode) {
  return inode->dateDerModifInode;
}

/* V1
 * Récupère la date de dernière modification d'u fichier associé à un inode.
 * Entrée : l'inode pour lequel on souhaite connaître la date de dernière modification du fichier associé
 * Retour : la date de dernière modification du fichier associé à l'inode
 */
time_t DateDerModifFichier(tInode inode) {
  return inode->dateDerModif;
}

/* V1
 * Récupère le numéro d'un inode.
 * Entrée : l'inode pour lequel on souhaite connaître le numéro
 * Retour : le numéro de l'inode
 */
unsigned int Numero(tInode inode) {
  return inode->numero;
}

/* V1
 * Récupère la taille en octets du fichier associé à un inode.
 * Entrée : l'inode pour lequel on souhaite connaître la taille
 * Retour : la taille en octets du fichier associé à l'inode
 */
long Taille(tInode inode) {
  return inode->taille;
}

/* V1
 * Récupère le type du fichier associé à un inode.
 * Entrée : l'inode pour lequel on souhaite connaître le tyep de fichier associé
 * Retour : le type du fichier associé à l'inode
 */
natureFichier Type(tInode inode) {
  return inode->type;
}

/* V1
 * Affiche les informations d'un inode
 * Entrée : l'inode dont on souhaite afficher les informations
 * Retour : aucun
 */
void AfficherInode(tInode inode) {
	if (inode == NULL) {
		printf("vide\n");
		return;
	}
	
	//titre
	printf("------Inode------[%u]\n", Numero(inode));
	
	//afficahge du type
	char *typeStr;
	if (Type(inode) == ORDINAIRE) {
		typeStr = "ordinaire";
	}
	else if (Type(inode) == REPERTOIRE) {
		typeStr = "repertoire";
	}
	else if (Type(inode) == AUTRE) {
		typeStr = "autre";
	}
	printf("type : %s\n", typeStr);
		
	//affichage de la taille
	long taille = Taille(inode);
	if (taille > 64) {
		taille = TAILLE_BLOC;
	}
	printf("		taille : %ld octets\n", taille);
	
	//affichage des dates
	time_t t1 = DateDerAcces(inode);
	time_t t2 = DateDerModif(inode);
	time_t t3 = DateDerModifFichier(inode);

	printf("                date dernier accès : %s", ctime(&t1));
	printf("                date dernière modification : %s", ctime(&t2));
	printf("                date dernière modification inode : %s", ctime(&t3));

	
	//affichage des données
	printf("		Données : \n");
	
	for (int i = 0; i < NB_BLOCS_DIRECTS; i++) {
	
		if (inode->blocDonnees[i] != NULL) {
		
			unsigned char *contenu = malloc(TAILLE_BLOC);
			if (contenu == NULL) {
			
				perror("AfficherInode : malloc");
			}
			else {
			
				long n = LireDonneesInode1bloc(inode, contenu, Taille(inode));
				if (n >= 0) {
				
					fwrite(contenu, 1, n, stdout);
					printf("\n");
					printf("Nombre d'octets lus : %ld\n", n);
				}
				free(contenu);
			}
		}
	}
}

/* V1
 * Copie à l'adresse contenu les taille octets stockés dans un inode.
 * Si taille est supérieure à la taille d’un bloc, seuls les TAILLE_BLOC premiers octets doivent être copiés.
 * Entrées : l'inode, l'adresse de la zone où recopier et la taille en octets de l'inode
 * Retour : le nombre d'octets effectivement lus dans l'inode ou -1 en cas d'erreur
 */
long LireDonneesInode1bloc(tInode inode, unsigned char *contenu, long taille) {
	if (contenu == NULL || inode == NULL || inode->blocDonnees[0] == NULL) {
		return -1;
	}
	//on vérifie que la taille ne dépasse pas celle d'un bloc
	long nbOctetsEcrits;
	if (taille > TAILLE_BLOC) {
		nbOctetsEcrits = TAILLE_BLOC;
	}
	else {
		nbOctetsEcrits = taille;
	}
	
	LireContenuBloc(inode->blocDonnees[0], contenu, nbOctetsEcrits);
  
  //On met a jour la date
  inode->dateDerAcces = time(NULL);
  
  return nbOctetsEcrits;
}

/* V1
 * Copie dans un inode les taille octets situés à l’adresse contenu.
 * Si taille est supérieure à la taille d’un bloc, seuls les TAILLE_BLOC premiers octets doivent être copiés.
 * Entrées : l'inode, l'adresse de la zone à recopier et sa taille en octets
 * Retour : le nombre d'octets effectivement écrits dans l'inode ou -1 en cas d'erreur
 */
long EcrireDonneesInode1bloc(tInode inode, unsigned char *contenu, long taille) {
	if (contenu == NULL || inode == NULL) {
		return -1;
	}
	
	if (inode->blocDonnees[0] == NULL) {
		inode->blocDonnees[0] = CreerBloc();
		if (inode->blocDonnees[0] == NULL) {
			return -1;
		}
	}
	//on vérifie que la taille ne dépasse pas celle d'un bloc
	long nbOctetsEcrits;
	if (taille > TAILLE_BLOC) {
		nbOctetsEcrits = TAILLE_BLOC;
	}
	else {
		nbOctetsEcrits = taille;
	}
	
	EcrireContenuBloc(inode->blocDonnees[0], contenu, nbOctetsEcrits);
  
  //On met a jour la date
  inode->dateDerAcces = time(NULL);
  inode->dateDerModif = time(NULL);
  inode->dateDerModifInode = time(NULL);
  
  inode->taille = taille;
  
  return nbOctetsEcrits;
}









