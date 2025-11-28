/**
 * ProgC - Projet Automne 25-26 : Gestion de systèmes de fichiers
 * VERSION 3
 * Fichier : bloc.c
 * Module de gestion des blocs de données.
 **/

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "bloc.h"

// Dans le .h : typedef unsigned char *tBloc;

/* V1
 * Crée et retourne un nouveau bloc de données.
 * Entrée : Aucune
 * Retour : le bloc créé ou NULL en cas de problème
 */
tBloc CreerBloc (void) {
  tBloc bloc = malloc(TAILLE_BLOC * sizeof(unsigned char));
  
  if (bloc == NULL) {
  	fprintf(stderr, "CreerBloc : probleme creation\n");
  	return NULL;
  }
  
  return bloc;
}

/* V1
 * Détruit un bloc de données.
 * Entrée : le bloc à détruire (libération mémoire allouée)
 * Retour : aucun
 */
void DetruireBloc(tBloc *pBloc){

  if (pBloc == NULL || *pBloc == NULL) {
  	return;
  }
  
  free(*pBloc);
  *pBloc = NULL;
}

/* V1
 * Copie dans un bloc les taille octets situés à l’adresse contenu.
 * Si taille est supérieure à la taille d’un bloc, seuls les TAILLE_BLOC premiers octets doivent être copiés.
 * Entrées : le bloc, l'adresse du contenu à copier et sa taille en octets
 * Retour : le nombre d'octets effectivement écrits dans le bloc
 */
long EcrireContenuBloc(tBloc bloc, unsigned char *contenu, long taille){

  if (bloc == NULL || contenu == NULL || taille <= 0) {
  	return 0;
  }
  
  long octetsEcrits = 0;
  
  for (long i = 0; i < taille && i < TAILLE_BLOC; i++) {
  	bloc[i] = contenu[i];
  	octetsEcrits++;
  }
  
  return octetsEcrits;
}

/* V1
 * Copie à l'adresse contenu, les taille octets stockés dans un bloc.
 * Si taille est supérieure à la taille d’un bloc, seuls les TAILLE_BLOC premiers octets doivent être copiés.
 * Entrées : le bloc, l'adresse contenu à laquelle recopier et la taille en octets du bloc
 * Retour : le nombre d'octets effectivement lus dans le bloc
 */
long LireContenuBloc(tBloc bloc, unsigned char *contenu, long taille){

	//on peut faire pareil que dans la fonction EcrireContenuBloc en changeant bloc en contenu
  if (bloc == NULL || contenu == NULL || taille <= 0) {
  	return 0;
  }
  
  long octetsLus = 0;
  
  for (long i = 0; i < taille && i < TAILLE_BLOC; i++) {
  	contenu[i] = bloc[i];
  	octetsLus++;
  }
  
  return octetsLus;
}

/* V3
 * Sauvegarde les données d'un bloc en les écrivant dans un fichier (sur disque).
 * Entrées : le bloc à sauvegarder, sa taille en octets, le nom du fichier cible
 * Retour : 0 en cas de succès, -1 en cas d'erreur
 */
int SauvegarderBloc(tBloc bloc, long taille, FILE *fichier){
  if (fichier == NULL) {
  	return -1;
  }
  //pour ne pas écrire plus qu'un bloc en taille
  if (taille > TAILLE_BLOC) {
  	taille = TAILLE_BLOC;
  }
  
  //on écrit les données du bloc
  size_t octetsEcrits = fwrite(bloc.contenu, taille, 1, fichier);
  if (octetsEcrits != (size_t)taille) {
  	return -1;
  }
  
  return 0;
}

/* V3
 * Charge dans un bloc les données lues dans un fichier (sur disque).
 * Entrées : le bloc dans lequel charger, la taille en octets du fichier contenant les données, son nom (sur le disque))
 * Retour : 0 en cas de succès, -1 en cas d'erreur
 */
int ChargerBloc(tBloc bloc, long taille, FILE *fichier){
	if(fichier == NULL) {
		return -1	;
	}
	
	//pour ne pas lire plus qu'un bloc
	if(taille > TAILLE_BLOC) {
		taille = TAILLE_BLOC;
	}
	//on lit les données du fichier pour les mettre dans un bloc
	size_t octetsLus = fread(bloc.contenu, taille, 1, fichier);
	if( octetsLus != (size_t)taille) {
		return -1;
	}
	return 0;
}






