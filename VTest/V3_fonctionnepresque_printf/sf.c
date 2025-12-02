/**
 * ProgC - Projet Automne 25-26 : Gestion de systèmes de fichiers
 * VERSION 3
 * Fichier : sf.c
 * Module de gestion d'un systèmes de fichiers (simulé)
 **/

#include "sf.h"
#include "bloc.h"
#include <stdio.h>
#include <stdlib.h>

// Taille maximale du nom du SF (ou nom du disque)
#define TAILLE_NOM_DISQUE 24

// Définition du super-bloc
struct sSuperBloc
{
  // Le nom du disque (ou du système de fichiers) (avec le '\0')
  char nomDisque[TAILLE_NOM_DISQUE+1];
  // La date de dernière modification du système de fichiers
  time_t dateDerModif;
};

// Type représentant le super-bloc
typedef struct sSuperBloc *tSuperBloc;

// Définition de la liste chaînée des inodes
struct sListeInodes
{
  // Références vers le premier et le dernier élément de la liste chaînée
  struct sListeInodesElement *premier, *dernier;
  // Nombre d'inodes dans la liste
  int nbInodes;
};

// Définition d'un élement de la liste chaînée des inodes dans le SF
struct sListeInodesElement
{
  // L'inode proprement dit
  tInode inode;
  // L'élément suivant dans la liste chaînée
  struct sListeInodesElement *suivant;
};

// Définirion d'un système de fichiers (simplifié)
struct sSF
{
  // Le super-bloc
  tSuperBloc superBloc;
  // La liste chaînée des inodes
  struct sListeInodes listeInodes;
};

/* V2
*  Crée et retourne un super-bloc.
* Entrée : le nom du disque (ou du SF)
* Sortie : le super-bloc, ou NULL en cas de problème
*/
static tSuperBloc CreerSuperBloc(char nomDisque[]) {
	//on alloue la place nécéssaire pour le supeBloc
	tSuperBloc superBloc = malloc(sizeof(struct sSuperBloc));
	if (superBloc == NULL) {
			
		fprintf(stderr, "CreerSuperBloc : probleme creation\n");							///////////////
		return NULL;
	}
	
	int i = 0;
	while (i < TAILLE_NOM_DISQUE && nomDisque[i] != '\0') {
		superBloc->nomDisque[i] = nomDisque[i];
		i++;
	}
	
	superBloc->nomDisque[i] = '\0';
	superBloc->dateDerModif = time(NULL);
	
	printf("CreerSuperBloc: réussi\n");																			//---------------
	return superBloc;
}

/* V2
*  Détruit un super-bloc.
* Entrée : le super-bloc à détruire
* Sortie : aucune
*/
static void DetruireSuperBloc(tSuperBloc *pSuperBloc) {
  if (pSuperBloc != NULL && *pSuperBloc != NULL) {
  	free(*pSuperBloc);
  	*pSuperBloc = NULL;
  }
  
  printf("DetruireSuperBloc: réussi\n");															//---------------
}

/* V2
*  Affiche le contenu d'un super-bloc.
* Entrée : le super-bloc à afficher
* Sortie : aucune
*/
static void AfficherSuperBloc(tSuperBloc superBloc) {
	if (superBloc == NULL) {
		printf("vide\n");
		
		printf("erreur: AfficherSuperBloc: superBloc vide\n");						////////////////////
		return;
	}
	time_t dateDerModif = superBloc->dateDerModif;
	printf("taille bloc = %d, date der modif = %s", TAILLE_BLOC, ctime(&dateDerModif));
	
	printf("AfficherSuperBloc: réussi\n");
}

/* V2
 * Crée un nouveau système de fichiers.
 * Entrée : nom du disque à associer au système de fichiers créé
 * Retour : le système de fichiers créé, ou NULL en cas d'erreur
 */
tSF CreerSF (char nomDisque[]){
  tSF sf = malloc (sizeof(struct sSF));
  if (sf == NULL) {
  
  	fprintf(stderr, "CreerSF : probleme creation\n");									/////////////
  	return NULL;
  }
  
  sf->superBloc = CreerSuperBloc(nomDisque);
  if (sf->superBloc == NULL) {
  	free(sf);
  	
  	printf("erreur: CreerSF: CreerSuperBloc échoué\n");									/////////////// 
  	return NULL;
  }
  sf->listeInodes.premier = NULL;
  sf->listeInodes.dernier = NULL;
  sf->listeInodes.nbInodes = 0;
  
  
  printf("CreerSF: réussi\n");																					//------------------
  return sf;
}

/* V2
 * Détruit un système de fichiers et libère la mémoire associée.
 * Entrée : le SF à détruire
 * Sortie : aucune
 */
void DetruireSF(tSF *pSF) {
	if (pSF != NULL && *pSF != NULL) {
		if ((*pSF)->superBloc != NULL) {
			//détruit le super Bloc si il existe
			DetruireSuperBloc(&(*pSF)->superBloc);
		}
		
		//Détruit les inodes de la liste chainée
		struct sListeInodesElement *courant = (*pSF)->listeInodes.premier;
		while (courant != NULL) {
			struct sListeInodesElement *suivant = courant->suivant;
			if (courant->inode != NULL) {
				DetruireInode(&courant->inode);
			}
			free(courant);
			courant = suivant;
		}
		
		if ((*pSF)->superBloc != NULL) {
			free((*pSF)->superBloc);
			(*pSF)->superBloc = NULL;
		}
		
		free(*pSF);
		*pSF = NULL;
	}
}

/* V2
 * Affiche les informations relative à un système de fichiers i.e;
 * le contenu du super-bloc et celui des différents inodes du SF
 * Entrée : le SF à afficher
 * Sortie : aucune
 */
void AfficherSF (tSF sf){
	if (sf == NULL) {
		
		printf("vide\n");																						//////////////////
		return;
	}
  printf("SF de nom %s, super bloc:\n", sf->superBloc->nomDisque);
  AfficherSuperBloc(sf->superBloc);
  
  printf("Affichage des Inodes Du SF\n");
  struct sListeInodesElement *courant = sf->listeInodes.premier;
  while (courant != NULL) {
  	AfficherInode(courant->inode);
  	courant = courant->suivant;
  }
  
  printf("AfficherSF: réussi\n");																	//--------------------
}

/* V2
 * Ecrit un fichier d'un seul bloc dans le système de fichiers.
 * Entrées : le système de fichiers, le nom du fichier (sur disque) et son type dans le SF (simulé)
 * Sortie : le nombre d'octets effectivement écrits, -1 en cas d'erreur.
 */
long Ecrire1BlocFichierSF(tSF sf, char nomFichier[], natureFichier type) {
  if (sf == NULL || nomFichier == NULL) {
  
  	printf("erreur: Ecrire1BlocFichierSF: sf ou nomFichier NULL\n");		//////////////
  	return -1;
  }
  tInode inode = CreerInode(sf->listeInodes.nbInodes, type);
  
  //on ajoute l'inode dans la liste chainée d'inodes
  struct sListeInodesElement *nouvElement = malloc(sizeof(struct sListeInodesElement));
  nouvElement->inode = inode;
  nouvElement->suivant = NULL;
  
  //liste vide
  if (sf->listeInodes.premier == NULL) {
  	sf->listeInodes.premier = nouvElement;
  	sf->listeInodes.dernier = nouvElement;
  }
  else {
  	sf->listeInodes.dernier->suivant = nouvElement;	//cas dans lequel la liste n'est pas vide
  	sf->listeInodes.dernier = nouvElement;
  }
  sf->listeInodes.nbInodes++;
  
  
  FILE *f = fopen(nomFichier, "rb");
  if (f == NULL) {
  
  	printf("erreur: Ecrire1blocFIchierSF: problème ouverturefichier, fichier NULL\n");	////////
  	return -1;
  }
  
  unsigned char buffer[TAILLE_BLOC];
  long nbOctetsLus = fread(buffer, 1, TAILLE_BLOC, f);
  fclose(f);
  
  long nbOctetsEcrits = EcrireDonneesInode1bloc(inode, buffer, nbOctetsLus);
  
  printf("Ecrire1BlocFichierSF: réussi\n");																					//-------------
  return nbOctetsEcrits;
}

/* V3
 * Ecrit un fichier (d'un nombre de blocs quelconque) dans le système de fichiers.
 * Si la taille du fichier à écrire dépasse la taille maximale d'un fichier dans le SF(10 x 64 octets),
 * seuls les 640 premiers octets seront écrits dans le système de fichiers.
 * Entrées : le système de fichiers, le nom du fichier (sur disque) et son type dans le SF (simulé)
 * Sortie : le nombre d'octets effectivement écrits, -1 en cas d'erreur.
 */
long EcrireFichierSF(tSF sf, char nomFichier[], natureFichier type) {
	if (sf == NULL || nomFichier == NULL) {
	
		printf("erreur: EcrireFIchierSF: sf ou nomFichier NULL\n");									/////////////
		return -1;
	}
	
	//création de l'inode
	tInode inode = CreerInode(sf->listeInodes.nbInodes, type);
	//on ajoute l'inode crée dans la liste chainée d'inodes
	struct sListeInodesElement *nouvelElement = malloc(sizeof(struct sListeInodesElement));
	if (nouvelElement == NULL) {
	
		printf("erreur: EcrireFichierSF: nouvel element de inode non crée NULL\n"); 			///////////
		return -1;
	}
	nouvelElement->inode = inode;
	//on met l'élément suivant a NULL
	nouvelElement->suivant = NULL;
	//on regarde si la liste est vide
	if (sf->listeInodes.premier == NULL) {
		sf->listeInodes.premier = nouvelElement;
		sf->listeInodes.dernier = nouvelElement;
	}
	else {
		sf->listeInodes.dernier->suivant = nouvelElement;
		sf->listeInodes.dernier = nouvelElement;
	}
	sf->listeInodes.nbInodes++;
	
	//on ouvre le fichier de nomFichier
	FILE *f = fopen(nomFichier, "rb");
	if (f == NULL) {
	
		printf("erreur: EcrireFichierSF: problème ouverture fichier, fichier NULL\n");		//////
		return -1;
	}
	
	//on crée un buffer bloc de TAILLE_BLOC pour stocker un bloc du fichier
	unsigned char bloc[TAILLE_BLOC];
	long decalage = 0;
	long nbOctetsLus = 0;
	long nbOctetsEcrits = 0;
	
	while ((nbOctetsLus = fread(bloc, 1, TAILLE_BLOC, f)) > 0) {
		EcrireDonneesInode(inode, bloc, nbOctetsLus, decalage);
		decalage += nbOctetsLus;
		nbOctetsEcrits += nbOctetsLus;
	}
	fclose(f);
	
	printf("EcrireFichierSF: réussi\n");																					//-------------
	return nbOctetsEcrits;
}

/* V3
 * Sauvegarde un système de fichiers dans un fichier (sur disque).
 * Entrées : le système de fichiers, le nom du fichier sauvegarde (sur disque)
 * Sortie : 0 en cas de succèe, -1 en cas d'erreur
 */
int SauvegarderSF(tSF sf, char nomFichier[]) {
	if (sf == NULL || nomFichier == NULL) {
		return -1;
	}
	
  FILE *f = fopen(nomFichier, "wb");
  if (f == NULL) {
  	return -1;
  }
  
  size_t nbLus;
  
  //On sauvegarde le nombre d'inodes
  nbLus = fwrite(&(sf->listeInodes.nbInodes), sizeof(int), 1, f);
  if (nbLus != 1) {
  	fclose(f);
  	return -1;
  }
  
  //on sauvegarde les informations du superBloc
  nbLus = fwrite(sf->superBloc->nomDisque, sizeof(struct sSuperBloc), 1, f);
  if (nbLus != 1) {
		fclose(f);
		return -1;
  }
  
  //on sauvegarde les informations de la liste chainée d'inodes
  struct sListeInodesElement *element = sf->listeInodes.premier;
  while (element != NULL) {
  	if (SauvegarderInode(element->inode, f) != 0) {
  		fclose(f);
  		return -1;
  	}
  	element = element->suivant;
  }
  
  fclose(f);
  return 0;
}

/* V3
 * Restaure le contenu d'un système de fichiers depuis un fichier sauvegarde (sur disque).
 * Entrées : le système de fichiers où restaurer, le nom du fichier sauvegarde (sur disque)
 * Sortie : 0 en cas de succèe, -1 en cas d'erreur
 */
int ChargerSF(tSF *pSF, char nomFichier[]) {
  if (nomFichier == NULL || pSF == NULL) return -1;
  
  FILE *f = fopen(nomFichier, "rb");
  if (f == NULL) return -1;
  
  //on lit le nombre d'inodes
  int nbInodes;
  size_t nbLus;
  
  nbLus = fread(&nbInodes, sizeof(int), 1, f);
  if (nbLus != 1) {
  	fclose(f);
  	return -1;
  }
  
  //on crée un nouveau SF
  tSF sf = malloc(sizeof(struct sSF));
  if (sf == NULL) {
  	fclose(f);
  	return -1;
  }
  
  //on crée la liste d'inodes
  sf->listeInodes.premier = NULL;
  sf->listeInodes.dernier = NULL;
  sf->listeInodes.nbInodes = 0;
  
  
  
  //on alloue le superBloc
  sf->superBloc = malloc(sizeof(struct sSuperBloc));
  if (sf->superBloc == NULL) {
  	free(sf);
  	fclose(f);
  	return -1;
	}

  //on charge les informations du superBloc
  nbLus = fread(sf->superBloc, sizeof(struct sSuperBloc), 1, f);
  if (nbLus != 1) {
  	free(sf->superBloc);
  	free(sf);
  	fclose(f);
  	return -1;
  }
  
  
  //on charge la liste chainée d'inodes
  for (int i = 0; i < nbInodes; i++) {
  	//on crée un inode vide comme nouvel élément de la liste 
  	struct sListeInodesElement *element = malloc(sizeof(struct sListeInodesElement));
  	if (element == NULL) {
  		DetruireSF(&sf);
  		fclose(f);
  		return -1;
  	}
  	
  	//on crée un inode avec des valeurs temporaires
  	element->inode = CreerInode(0, 0);
  	if (element->inode == NULL) {
  		free(element);
  		DetruireSF(&sf);
  		fclose(f);
  	}
  	
  	//on charge les données de l'inode depuis le fichier
  	if (ChargerInode(&element->inode, f) != 0) {
  		DetruireInode(&element->inode);
  		free(element);
  		DetruireSF(&sf);
  		fclose(f);
  	}
  	
  	element->suivant = NULL;
  	if (sf->listeInodes.premier == NULL) {
  		sf->listeInodes.premier = element;
  		sf->listeInodes.dernier = element;
  	}
  	else {
  		sf->listeInodes.dernier->suivant = element;
  		sf->listeInodes.dernier = element;
  	}
  	sf->listeInodes.nbInodes++;
  }
  fclose(f);
  *pSF = sf;
  return 0;
}











