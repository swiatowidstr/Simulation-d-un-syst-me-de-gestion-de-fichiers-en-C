/**
 * ProgC - Projet Automne 25-26 : Gestion de systèmes de fichiers
 * VERSION 3
 * Fichier : inode.c
 * Module de gestion des inodes.
 **/
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "inode.h"
#include "bloc.h"

#define NB_BLOCS_DIRECTS 10

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

/* V1 & V3
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
	
	long taille = Taille(inode);
	
	//affichage de la taille en octets 
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
	
	unsigned char *contenu = malloc(inode->taille + 1);
	if (contenu == NULL) {
		perror("AfficherInode : malloc");
		return;
	}
	
	long lus = LireDonneesInode(inode, contenu, taille, 0);
	if (lus < 0) {
		free(contenu);
		return;
	}
	//on met un caractère qui indique la fin de la chaine pour pouvoir lire la chaine  
	contenu[lus] = '\0';
	printf("%s", contenu);
	free(contenu);														
	printf("\n");
}

/* V1
 * Copie dans un inode les taille octets situés à l’adresse contenu.
 * Si taille est supérieure à la taille d’un bloc, seuls les TAILLE_BLOC premiers octets doivent être copiés.
 * Entrées : l'inode, l'adresse de la zone à recopier et sa taille en octets
 * Retour : le nombre d'octets effectivement écrits dans l'inode ou -1 en cas d'erreur
 */
long LireDonneesInode1bloc(tInode inode, unsigned char *contenu, long taille) {
	if (contenu == NULL || inode == NULL || inode->blocDonnees[0] == NULL) {
		return -1;
	}
	long nbOctetsLus = LireContenuBloc(inode->blocDonnees[0], contenu, taille);
  
  //On met a jour la date
  inode->dateDerAcces = time(NULL);
  
  return nbOctetsLus;
}

/* V1
 * Copie à l'adresse contenu les taille octets stockés dans un inode.
 * Si taille est supérieure à la taille d’un bloc, seuls les TAILLE_BLOC premiers octets doivent être copiés.
 * Entrées : l'inode, l'adresse de la zone où recopier et la taille en octets de l'inode
 * Retour : le nombre d'octets effectivement lus dans l'inode ou -1 en cas d'erreur
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
	
	//on écrit dans le bloc
	nbOctetsEcrits = EcrireContenuBloc(inode->blocDonnees[0], contenu, nbOctetsEcrits);
  
  //on met a jour la taille si on a écrit quelque chose
  if (nbOctetsEcrits > 0) {
  	inode->taille = nbOctetsEcrits;
  }
  
  //On met a jour la date
  inode->dateDerAcces = time(NULL);
  inode->dateDerModif = time(NULL);
  inode->dateDerModifInode = time(NULL);
  return nbOctetsEcrits;
}


/* V3
 * Lit les données d'un inode avec décalage, et les stocke à une adresse donnée
 * Entrées : l'inode d'où les données sont lues, la zone où recopier ces données, la taille en octets
 * des données à lire et le décalage à appliquer (voir énoncé)
 * Sortie : le nombre d'octets effectivement lus, 0 si le décalage est au-delà de la taille
 */
long LireDonneesInode(tInode inode, unsigned char *contenu, long taille, long decalage) {
    if (inode == NULL || contenu == NULL) {
        return -1;
    }

    if (decalage >= inode->taille) {
        // décalage au-delà de la taille du fichier
        return 0;
    }

    // Ajuster la taille à lire si elle dépasse la fin de l'inode
    if (taille > inode->taille - decalage) {
        taille = inode->taille - decalage;
    }

    long nbOctetsLus = 0;
    long octetsRestants = taille;
		
		
    int numBloc = decalage / TAILLE_BLOC;
    int decalageDansBloc = decalage % TAILLE_BLOC;
    
    while (octetsRestants > 0 && numBloc < NB_BLOCS_DIRECTS) {
    	//on vérifie que le bloc existe;
    	if (inode->blocDonnees[numBloc] == NULL) {
    		break;
    	}
    	
    	//on calcule le nombre d'octets à lire dans le bloc
    	long octetsALire = TAILLE_BLOC - decalageDansBloc;
    	if (octetsALire > octetsRestants) {
    		octetsALire = octetsRestants;
    	}
    	
    	//on lit le blocavec le decalage
    	unsigned char *positionDansBloc = inode->blocDonnees[numBloc];
    	
    	for (long i = 0; i < octetsALire; i++) {
    		contenu[nbOctetsLus + i] = positionDansBloc[decalageDansBloc + i];
    	}
    	
    	nbOctetsLus += octetsALire;
    	octetsRestants -= octetsALire;
    	
    	numBloc++;
    	decalageDansBloc = 0;
    	
    }
    
    // Mise à jour de la date d'accès
    inode->dateDerAcces = time(NULL);

    return nbOctetsLus;
}


/* V3
 * Ecrit dans un inode, avec décalage, ls données stockées à une adresse donnée
 * Entrées : l'inode où écrire le contenu, l'adesse de la zone depuis laquelle lire les données, la taille en octets
 * de ces données et le décalage à appliquer (voir énoncé)
 * Sortie : le nombre d'octets effectivement écrits, ou -1 en cas d'erreur
 */
 
 
long EcrireDonneesInode(tInode inode, unsigned char *contenu, long taille, long decalage) {
    if (contenu == NULL || inode == NULL || taille <= 0) {
        return -1;
    }
    
    long tailleMax = TAILLE_BLOC * NB_BLOCS_DIRECTS;
    
    // Si le décalage dépasse la taille maximale, erreur
    if (decalage >= tailleMax) {
        return 0;
    }
    
    // Si décalage + taille dépasse la capacité, réduire la taille
    if (decalage + taille > tailleMax) {
        taille = tailleMax - decalage;
    }
    
    // IMPORTANT : Créer tous les blocs nécessaires jusqu'au dernier bloc qu'on va utiliser
    int premierBloc = 0;
    int dernierBloc = (decalage + taille - 1) / TAILLE_BLOC;
    
    for (int i = premierBloc; i <= dernierBloc; i++) {
        if (inode->blocDonnees[i] == NULL) {
            inode->blocDonnees[i] = CreerBloc();
            if (inode->blocDonnees[i] == NULL) {
                return -1;
            }
        }
    }
    
    long nbOctetsEcrits = 0;
    long octetsRestants = taille;
    unsigned char *ptrContenu = contenu;
    
    int numBloc = decalage / TAILLE_BLOC;
    int decalageDansBloc = decalage % TAILLE_BLOC;
    
    while (octetsRestants > 0 && numBloc < NB_BLOCS_DIRECTS) {
        // Le bloc existe déjà (créé ci-dessus)
        
        // Calculer le nombre d'octets à écrire dans ce bloc
        long octetsAEcrireDansCeBloc = TAILLE_BLOC - decalageDansBloc;
        if (octetsAEcrireDansCeBloc > octetsRestants) {
            octetsAEcrireDansCeBloc = octetsRestants;
        }
        
        // Écrire dans le bloc à partir du décalage interne
        for (long i = 0; i < octetsAEcrireDansCeBloc; i++) {
            inode->blocDonnees[numBloc][decalageDansBloc + i] = ptrContenu[i];
        }
        
        // Avancer le pointeur de contenu
        ptrContenu += octetsAEcrireDansCeBloc;
        nbOctetsEcrits += octetsAEcrireDansCeBloc;
        octetsRestants -= octetsAEcrireDansCeBloc;
        
        // Passer au bloc suivant
        numBloc++;
        decalageDansBloc = 0;
    }
    
    // Mettre à jour la taille totale
    long nouvelleTaille = decalage + nbOctetsEcrits;
    if (nouvelleTaille > inode->taille) {
        inode->taille = nouvelleTaille;
    }
    
    // Mettre à jour les dates
    time_t now = time(NULL);
    inode->dateDerAcces = now;
    inode->dateDerModif = now;
    inode->dateDerModifInode = now;
    
    return nbOctetsEcrits;
}

/* V3
 * Sauvegarde toutes les informations contenues dans un inode dans un fichier (sur disque,
 * et préalablement ouvert en écriture et en mode binaire)
 * Entrées : l'inode concerné, l'identificateur du fichier
 * Sortie : 0 en cas de succès, -1 en cas d'erreur
 */
int SauvegarderInode(tInode inode, FILE *fichier) {
  if (fichier == NULL || inode == NULL) {
  	return -1;
  }

  size_t nbEcrits;
  //on retourne -1 si il y a une erreur avec une des sauvegardes en vérifiant si quelque chose a été écrit
  //on sauvegarde les informations de l'inode 
  nbEcrits = fwrite(&(inode->numero), sizeof(inode->numero), 1, fichier);
  if (nbEcrits != 1) return -1;
  nbEcrits = fwrite(&(inode->type), sizeof(inode->type), 1, fichier);
  if (nbEcrits != 1) return -1;
  nbEcrits = fwrite(&(inode->taille), sizeof(inode->taille), 1, fichier);
  if (nbEcrits != 1) return -1;
  
  //on sauvegarde les informations contenues dans les blocs
  long octetsRestants = inode->taille;
  //on vérifie qu'il reste des octets a sauvegarder avant de les écrire
  //car la fonction SauvegarderBloc a besoin d'une taille d'octets a sauvegarder en paramètre
  for (int i = 0; i < NB_BLOCS_DIRECTS && octetsRestants > 0; i++) {
  	if (inode->blocDonnees[i] != NULL) {
  		long tailleBloc;
  		if (octetsRestants > TAILLE_BLOC) {
  			tailleBloc = TAILLE_BLOC;
  		}
  		else {
  			tailleBloc = octetsRestants;
  		}
  		
  		//si SauvegarderBloc renvoie 0 c'est que tout s'est bien passé
  		if (SauvegarderBloc(inode->blocDonnees[i], tailleBloc, fichier) != 0) {
  			return -1;
  		}
  		octetsRestants -= tailleBloc;
  	}
  }
  
  //sauvegarde des informations concernant les dates de modif et d'acces
  nbEcrits = fwrite(&(inode->dateDerAcces), sizeof(inode->dateDerAcces), 1, fichier);
  if (nbEcrits != 1) return -1;
  nbEcrits = fwrite(&(inode->dateDerModif), sizeof(inode->dateDerModif), 1, fichier);
  if (nbEcrits != 1) return -1;
  nbEcrits = fwrite(&(inode->dateDerModifInode), sizeof(inode->dateDerModifInode), 1, fichier);
  if (nbEcrits != 1) return -1;
  return 0;
}

/* V3
 * Charge toutes les informations d'un inode à partir d'un fichier (sur disque,
 * et préalablement ouvert en lecture et en mode binaire)
 * Entrées : l'inode concerné, l'identificateur du fichier
 * Sortie : 0 en cas de succès, -1 en cas d'erreur
 */
int ChargerInode(tInode *pInode, FILE *fichier) {
  if (fichier == NULL || pInode == NULL) {
  	return -1;
  }
  
  size_t nbLus;
  
  //on lit les indormations de base
  nbLus = fread(&((*pInode)->numero), sizeof((*pInode)->numero), 1, fichier);
  if (nbLus != 1) return -1;
  
  nbLus = fread(&((*pInode)->type), sizeof((*pInode)->type), 1, fichier);
  if (nbLus != 1) return -1;
  
  nbLus = fread(&((*pInode)->taille), sizeof((*pInode)->taille), 1, fichier);
  if (nbLus != 1) return -1;
  
  
  //on lit les blocs de l'inode
  long octetsRestants = (*pInode)->taille;
  for (int i = 0; i < NB_BLOCS_DIRECTS && octetsRestants > 0; i++) {
  	if ((*pInode)->blocDonnees[i] == NULL) {
  		(*pInode)->blocDonnees[i] = CreerBloc();
  		if((*pInode)->blocDonnees[i] == NULL) {
  			return -1;
  		}
  		
  		long tailleBloc;
  		if (octetsRestants > TAILLE_BLOC) {
  			tailleBloc = TAILLE_BLOC;
  		}
  		else {
  			tailleBloc = octetsRestants;
  		}
  		
  		//si ChargerBloc renvoie 0 c'est que tout s'est bien passé
  		if (ChargerBloc((*pInode)->blocDonnees[i], tailleBloc, fichier) != 0) {
  			return -1;
  		}
  		
  		octetsRestants -= tailleBloc;
  	}
  }
  
  //on lit les dates
  nbLus = fread(&((*pInode)->dateDerAcces), sizeof((*pInode)->dateDerAcces), 1, fichier);
  if (nbLus != 1) return -1;
  nbLus = fread(&((*pInode)->dateDerModif), sizeof((*pInode)->dateDerModif), 1, fichier);
  if (nbLus != 1) return -1;
  nbLus = fread(&((*pInode)->dateDerModifInode), sizeof((*pInode)->dateDerModifInode), 1, fichier);
  if (nbLus != 1) return -1;
  return 0;
}





