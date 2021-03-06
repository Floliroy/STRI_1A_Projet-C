#ifndef __USER_H__
#define __USER_H__

#include "util.h"

/** (Florian)
 * Cherche un utilisateur par son nom et son prénom dans la HashMap<utilisateur,String> passé en paramètre.
 * 
 * @param map La HashMap dans laquelle on cherche l'utilisateur (dans mainServeur.c : mapUtilisateurs)
 * @param nom Le nom de l'utilisateur recherché
 * @param prenom Le prenom de l'utilisateur recherché
 * @return Renvoit l'utilisateur recherché, NULL si on ne trouve rien
 **/
utilisateur* getUserWithNomPrenom(hashMapUserString* map, char* nom, char* prenom);

/** (Florian)
 * Cherche un utilisateur par son nom et son prénom dans la HashMap<utilisateur,String> passé en paramètre.
 * 
 * @param map La HashMap dans laquelle on cherche l'utilisateur (dans mainServeur.c : mapUtilisateurs)
 * @param login Le login de l'utilisateur recherché
 * @return Renvoit l'utilisateur recherché, NULL si on ne trouve rien
 **/
utilisateur* getUserWithLogin(hashMapUserString* map, char* login);

/** (Florian)
 * Cherche la position du curseur dans un fichier .csv pour être au début de la ligne de l'utilisateur recherché.
 * 
 * @param nomParam Le nom de l'utilisateur recherché
 * @param prenomParam Le prenom de l'utilisateur recherché
 * @param fichier Le nom du fichier où l'on va chercher l'utilisateur
 * @return Position du curseur.
 **/
int getUserLineWithNomPrenom(char* nomParam, char* prenomParam, char* fichier);

/** (Florian)
 * Regarde si l'utilisateur passé en paramètre est administrateur.
 * 
 * @param mapUtilisateurs La HashMap<utilisateur,String> mapUtilisateurs de mainServeur.c
 * @param user L'utilisateur dont on souhaite connaitre les droits admin
 * @return 1 s'il est admin, 0 sinon
 **/
int isUserAdmin(hashMapUserString mapUtilisateurs, utilisateur* user);

/** (Florian)
 * Vérifie si un mot de passe correspond bien au login donné.
 * 
 * @param mapUtilisateurs La HashMap<utilisateur,String> mapUtilisateurs de mainServeur.c
 * @param login Le login de l'utilisateur
 * @param password Le mote de passe que l'on souhaite tester
 * @return 1 si le mot de passe est valide, 0 sinon
 **/
int isMotDePasseValide(hashMapUserString mapUtilisateurs, char* login, char* password);

/** (Florian)
 * Cherche un utilisateur par son nom et son prénom dans le fichier csv et renvoit s'il est admin ou non.
 * 
 * @param nomParam Le nom de l'utilisateur recherché
 * @param prenomParam Le prenom de l'utilisateur recherché
 * @return 1 s'il est admin, 0 sinon
 **/
int isUserAdminWithNomPrenomInCsvFile(char* nomParam, char* prenomParam);

#endif