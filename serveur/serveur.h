#ifndef __SERVEUR_H__
#define __SERVEUR_H__

#include "../util/util.h"

/** (Florian)
 * Permet d'envoyer un code de retour au client
 * 
 * @param codeRetour Le code a emettre
 **/
void envoieRetour(int codeRetour);

/** (Florian)
 * Extrait de la requête les différents parametres de cette derniere dans une HashMap
 * 
 * @param requete La requete recu
 * @param mapParameters La map dans laquelle on stockera les parametres de la requete
 * @return Renvoit 1 si on a récupéré quelquechose, 0 sinon
 **/
int extraitRequete(char *requete, hashMapStringString* mapParameters);

/** (Florian)
 * Vérifie si la requete passé en parametre est bien une requete GET
 * 
 * @param requete La requete recu
 * @return Renvoit 1 si c'est une requete GET, 0 sinon
 **/
int isRequeteGet(char *requete);

/* Initialisation.
 * Creation du serveur.
 * renvoie 1 si �a c'est bien pass� 0 sinon
 */
int Initialisation();

/* Initialisation.
 * Creation du serveur en pr�cisant le service ou num�ro de port.
 * renvoie 1 si �a c'est bien pass� 0 sinon
 */
int InitialisationAvecService(char *service);


/* Attends qu'un client se connecte.
 * renvoie 1 si �a c'est bien pass� 0 sinon
 */
int AttenteClient();

/* Recoit un message envoye par le client.
 * retourne le message ou NULL en cas d'erreur.
 * Note : il faut liberer la memoire apres traitement.
 */
char *Reception();

/* Envoie un message au client.
 * Attention, le message doit etre termine par \n
 * renvoie 1 si �a c'est bien pass� 0 sinon
 */
int Emission(char *message);

/* Recoit des donnees envoyees par le client.
 * renvoie le nombre d'octets re�us, 0 si la connexion est ferm�e,
 * un nombre n�gatif en cas d'erreur
 */
int ReceptionBinaire(char *donnees, size_t tailleMax);

/* Envoie des donn�es au client en pr�cisant leur taille.
 * renvoie le nombre d'octets envoy�s, 0 si la connexion est ferm�e,
 * un nombre n�gatif en cas d'erreur
 */
int EmissionBinaire(char *donnees, size_t taille);


/* Ferme la connexion avec le client.
 */
void TerminaisonClient();

/* Arrete le serveur.
 */
void Terminaison();

#endif
