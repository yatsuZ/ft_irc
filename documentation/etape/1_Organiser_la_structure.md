# 1. Organiser la structure

- [1. Organiser la structure](#1-organiser-la-structure)
	- [Objectif](#objectif)
	- [Fonctionnement](#fonctionnement)
	- [Comment faire](#comment-faire)
	- [Les principaux objets](#les-principaux-objets)
	- [Leur rôle](#leur-rôle)
	- [Comment ils interagissent entre eux](#comment-ils-interagissent-entre-eux)
	- [Ce qu'ils sont capables de faire](#ce-quils-sont-capables-de-faire)
	- [Le tester](#le-tester)
		- [Avec `nc`](#avec-nc)
		- [Avec `irssi`](#avec-irssi)
	- [Fin](#fin)

## Objectif

La première étape du projet est de définir comment organiser la structure du projet et comprendre son fonctionnement.

## Fonctionnement

Voici ce que nous avons compris pour l'exécution du projet :

```bash
./ircserv <port> <password>
```

- **port** : Le numéro du port sur lequel votre serveur acceptera les connexions entrantes.
- **password** : Le mot de passe permettant de s’identifier auprès de votre serveur IRC, et qui devra être fourni par tout client IRC souhaitant s’y connecter.

Pour activer et accéder au serveur, nous utiliserons un client IRC. Nous avons choisi [Irssi](https://fr.wikipedia.org/wiki/Irssi), qui est déjà installé sur les postes de 42 et est simple d’utilisation.

**Documentation utile** : [Irssi Documentation](https://irssi.org/documentation/)

## Comment faire

- Réfléchir aux besoins du serveur IRC et définir ses fonctionnalités principales.
- Concevoir les différents objets/classes ainsi que leurs méthodes et attributs.

## Les principaux objets

Nous avons identifié les classes suivantes :
- **Serveur**
- **Utilisateur**  

Possiblement :
- **Channel**
- **Bot**
- **Fichier**

## Leur rôle

- **Serveur** : La classe principale, contenant les utilisateurs et les channels.
- **Utilisateur** : Représente chaque utilisateur connecté au serveur.
- **Channel** : (si implémenté) Représente les canaux de discussion.
- **Bot** : (optionnel) Un bot pour automatiser certaines tâches.
- **Fichier** : (optionnel) Gère les échanges de fichiers.

## Comment ils interagissent entre eux

La structure ressemblerait à un triangle :
- Le **Serveur** contient une liste (ou un vecteur) d’**Utilisateurs** et de **Channels**.
- Chaque **Utilisateur** a une liste de **Channels** auxquels il appartient.
- Chaque **Channel** a une liste d’**Utilisateurs** connectés.

## Ce qu'ils sont capables de faire

Pour plus de détails sur les fonctionnalités attendues, consultez : [Cahier des charges](./../Cahier_des_charges.md).

## Le tester

### Avec `nc`

1. Exécutez le programme comme montré précédemment.
2. Depuis un PC dans le même réseau que le serveur, lancez la commande suivante :
   ```bash
   nc <ip> <port>
   ```
3. Vous pourrez alors envoyer des données au serveur sous forme de bytes.

### Avec `irssi`

Cette méthode est en cours de développement.

## Fin