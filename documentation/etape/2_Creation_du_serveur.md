# 2. Création du serveur

Dans cette section, nous allons définir les fonctionnalités du serveur, son utilité et son fonctionnement. Nous détaillerons également les concepts clés comme les sockets et les fonctions utilisées pour implémenter le serveur.

## Table des matières

- [2. Création du serveur](#2-création-du-serveur)
	- [Table des matières](#table-des-matières)
	- [Objectif](#objectif)
	- [Qu'est-ce qu'un serveur](#quest-ce-quun-serveur)
		- [C'est quoi un socket](#cest-quoi-un-socket)
	- [Les fonctions utilisées](#les-fonctions-utilisées)
	- [Comment cela fonctionne](#comment-cela-fonctionne)
	- [Résumé des étapes avec ton projet](#résumé-des-étapes-avec-ton-projet)

## Objectif

L'objectif de cette section est de :
1. Définir les fonctionnalités du serveur, ses responsabilités et son rôle dans le projet.
2. Présenter les fonctions clés utilisées pour créer et gérer le serveur.
3. Expliquer, étape par étape, comment le serveur fonctionne.
4. CRee mes propre exception
## Qu'est-ce qu'un serveur

Un serveur est une application ou un système informatique qui répond aux demandes d'autres programmes ou appareils, appelés *clients*. 

Dans ce projet, le serveur sera implémenté sous forme d'une classe. Son rôle principal sera :
1. D'ouvrir une socket pour établir une communication avec les clients. (Voir [explication de la fonction socket](./../laboratoire/socket/info.md)).
2. D'écouter les connexions entrantes à l'aide de la fonction `listen`.
3. De gérer les échanges de données grâce à des fonctions comme `poll` et `send`.

En résumé, le serveur agit comme un intermédiaire entre les clients et l'application principale.

### C'est quoi un socket

Un *socket* est un canal de communication permettant d'échanger des données entre deux machines sur un réseau. Pour créer un socket, il faut définir :
1. **Le domaine de communication** : par exemple, `AF_INET` pour IPv4.
2. **Le type de socket** : par exemple, `SOCK_STREAM` pour une communication fiable.
3. **Le protocole** : souvent `0` pour utiliser le protocole par défaut associé au type de socket.

Dans ce projet, nous utiliserons ces paramètres pour établir une connexion entre le serveur et les clients.

## Les fonctions utilisées

Voici les principales fonctions utilisées pour implémenter le serveur :

1. **socket** : Pour créer un socket.
2. **bind** : Pour associer le socket à une adresse et un port.
3. **listen** : Pour écouter les connexions entrantes.
4. **accept** : Pour accepter une connexion d'un client.
5. **poll** ou équivalent : Pour gérer plusieurs connexions simultanément.
6. **send** et **recv** : Pour envoyer et recevoir des données.

D'autres fonctions pourraient être ajoutées en fonction des besoins du projet.

## Comment cela fonctionne

Le fonctionnement du serveur repose sur plusieurs étapes :
1. Création d'un socket avec les paramètres appropriés.
2. Association du socket à une adresse et un port avec `bind`.
3. Mise en écoute des connexions entrantes avec `listen`.
4. Gestion des connexions et des échanges de données.

Cette section sera détaillée une fois le code terminé et testé.

## Résumé des étapes avec ton projet
- Créer le socket : Appelle socket().
- Configurer l'adresse : Utilise sockaddr_in pour définir l'adresse et le port.
- Associer le socket à l'adresse : Appelle bind().
- Mettre en écoute : Appelle listen().
- Accepter des connexions : Appelle accept() dans une boucle pour gérer plusieurs clients.
- Communiquer : Utilise send() et recv() pour échanger des messages.
- Gérer les connexions multiples : Implémente un gestionnaire (threads, select(), etc.).
- Nettoyer : Ferme les sockets correctement.
