#ifndef __WORKSTRING_H__
#define __WORKSTRING_H__

#include "util.h"

//Couleurs pour les printf en console
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

/** (Florian)
 * Permet de lire une chaine tapée dans la console.
 * 
 * @param chaine La chaine à lire
 * @return Renvoit la taille de la chaîne
 **/
int monLire(char chaine[BUFSIZ]);

/** (Florian)
 * Parcours le string ligne et extrait un sous string entre l'indice de départ et un délimiteur.
 * 
 * @param ligne String dans lequelle on va extraire notre sous string
 * @param string String que l'on souhaite extraire de ligne
 * @param start Indice de départ (on le renvoit pour pouvoir revenir dans la fonction avec un autre sous string a extraire)
 * @param delimiteur Le caractere a partir duquel on arrete d'extraire notre sous string
 **/
void recupereString(char ligne[BUFSIZ], char string[BUFSIZ], int* start, char delimiteur);

/** (Florian)
 * Permet de demander un a l'utilisateur de rentrer un paramètre, puis dans le stocker dans une HashMap.
 * 
 * @param nomParam Le nom de ce paramètre
 * @param mapParameters la HashMap des paramètres
 * @param appartenance Si le mot de laison doit etre un "vous" ou un "son"
 * @param nullable Si on peut envoyer un paramètre nul 
 **/
void demandeParam(char* nomParam, hashMapStringString* mapParameters, int appartenance, int nullable);

#endif