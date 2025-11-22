/**
 * ProgC - Projet Automne 25-26 : Gestion de systèmes de fichiers
 * VERSION 2
 * Fichier : sf.c
 * Module de gestion d'un systèmes de fichiers (simulé)
 **/

#include "sf.h"
#include "bloc.h"

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

// Définition d'un système de fichiers (simplifié)
struct sSF
{
  // Le super-bloc
  tSuperBloc superBloc;
  // La liste chaînée des inodes
  struct sListeInodes listeInodes;
};

/* V2
*  Crée et retourne un super-bloc.
* Fonction non publique (static)
* Entrée : le nom du disque (ou du SF)
* Sortie : le super-bloc, ou NULL en cas de problème
*/
static tSuperBloc CreerSuperBloc(char nomDisque[]) {
	tSuperBloc superBloc = malloc(sizeof(struct sSuperBloc));
	if (superBloc == NULL) {
		 fprintf(stderr, "CreerSuperBloc : probleme creation\n");
		 return NULL;
	}
	
	int i = 0
	for (i; i < TAILLE_NOM_DISQUE && nomDisque[i] != '\0' ; i++) {
		superBloc->nomDisque[i] = nomDisque[i];
	}
	
	superBloc->nomDisque[i] = '\0';
	superBloc->dateDerModif = time(NULL);
	return superBloc;
}

/* V2
*  Détruit un super-bloc.
* Fonction non publique (static)
* Entrée : le super-bloc à détruire
* Sortie : aucune
*/
static void DetruireSuperBloc(tSuperBloc *pSuperBloc) {
  if (pSuperBloc != NULL && *pSuperBloc != NULL) {
  	free(*pSuperBloc);
  	*pSuperBloc = NULL;
  }
}

/* V2
*  Affiche le contenu d'un super-bloc.
* Fonction non publique (static)
* Entrée : le super-bloc à afficher
* Sortie : aucune
*/
static void AfficherSuperBloc(tSuperBloc superBloc) {
	if (superBloc == NULL) {
		printf("vide\n");
		return;
	}
	time_t dateDerModif = superBloc->dateDerModif;
	printf("taille bloc = %d, date der modif = %s", TAILLE_BLOC, ctime(&dateDerModif));
}

/* V2
 * Crée un nouveau système de fichiers.
 * Entrée : nom du disque à associer au système de fichiers créé
 * Retour : le système de fichiers créé, ou NULL en cas d'erreur
 */
tSF CreerSF (char nomDisque[]){
  tSF sf = malloc (sizeof(struct sSF));
  if (sf == NULL) {
  	fprintf(stderr, "CreerSF : probleme creation\n");
  	return NULL;
  }
  
  sf->superBloc = CreerSuperBloc(nomDisque);
  if (sf->superBloc == NULL) {
  	free(sf);
  	
  	return NULL;
  }
  sf->listeInodes.premier = NULL;
  sf->listeInodes.dernier = NULL;
  sf->listeInodes.nbInodes = 0;
  
  return sf;
}

/* V2
 * Détruit un système de fichiers et libère la mémoire associée.
 * Entrée : le SF à détruire
 * Sortie : aucune
 */
void DetruireSF(tSF *pSF) {
  if (pSF != NULL && *pSF != NULL) {
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
		printf("vide\n");
		return;
	}
	//affichage du nom du disque et du superbloc
  printf("SF de nom %s, super bloc:\n", sf->superBloc->nomDisque);
  AfficherSuperBloc(sf->superBloc);
  
  //affichage des inodes graces aux listes chainées 
  struct sLIsteInodesElement *courant = sf->listeInodes.premier;
  while (courant != NULL) {
  	AfficherInode(courant->inode);
  	courant = courant->suivant;
  }
  
}

/* V2
 * Ecrit un fichier d'un seul bloc dans le système de fichiers.
 * Entrées : le système de fichiers, le nom du fichier (sur disque) et son type dans le SF (simulé)
 * Sortie : le nombre d'octets effectivement écrits, -1 en cas d'erreur.
 */
long Ecrire1BlocFichierSF(tSF sf, char nomFichier[], natureFichier type) {
  if (sf == NULL || nomFichier == NULL) {
  	return -1;
  }
  tInode inode = CreerInode(sf->listeInodes.nbInodes, type);
  
  struct sListeInodesElement *nouvElement = malloc(sizeof(struct sListeInodesElement));
  nouvElement->inode = inode;
  nouvElement->suivant = NULL;
  
  
  sf->listeInodes.dernier->suivant = nouvElement;
  sf->listeInodes.dernier = nouvElement;
  sf->listeInodes.nbInodes++;
  
  long nbOctetsEcrits = EcrireDonneesInode1bloc(inode, sf->sListeInodesElement->inode, Taille(inode));
  
  return nbOctetsEcrits;
}






