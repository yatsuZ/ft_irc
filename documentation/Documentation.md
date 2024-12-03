# Documentation

Ce fichier contient toutes les sources utiles à la création du projet.

## Table of Contents / Sommaire
- [Documentation](#documentation)
	- [Table of Contents / Sommaire](#table-of-contents--sommaire)
	- [C'est quoi un Serveur](#cest-quoi-un-serveur)
		- [différent type de serveur](#différent-type-de-serveur)
		- [Détails supplémentaires](#détails-supplémentaires)
	- [Serveur IRC](#serveur-irc)
	- [Le Client](#le-client)
		- [Les différents clients pour IRC](#les-différents-clients-pour-irc)
	- [Liste de toutes les fonctions externes autorisées](#liste-de-toutes-les-fonctions-externes-autorisées)
	- [Qu'est-ce qu'un processus](#quest-ce-quun-processus)
	- [C'est quoi un socket](#cest-quoi-un-socket)
	- [Commande `nc`](#commande-nc)
		- [Syntaxe Générale](#syntaxe-générale)
		- [Options Principales](#options-principales)
		- [Exemples](#exemples)
	- [Les fichier .ipp](#les-fichier-ipp)
		- [Pourquoi utiliser des fichiers `.ipp` ?](#pourquoi-utiliser-des-fichiers-ipp-)
		- [Utilisation typique](#utilisation-typique)

## C'est quoi un Serveur

![dessin de à quoi ressemble un serveur](./illusatrion/representationServeur.png)

Un serveur est un ordinateur ou un système informatique qui fournit des ressources, des données, des services ou des programmes à d'autres ordinateurs, appelés clients, sur un réseau. Les serveurs jouent un rôle crucial dans les réseaux informatiques, qu'ils soient locaux (LAN) ou à grande échelle (WAN), y compris l'internet.

### différent type de serveur

| Type de Serveur            | Fonction Principale                                                                                                                 | Exemples de Logiciels                  |
|----------------------------|-------------------------------------------------------------------------------------------------------------------------------------|----------------------------------------|
| Serveur Web                | Héberger des sites web et fournir du contenu web aux navigateurs clients.                                                           | Apache, Nginx, Microsoft IIS           |
| Serveur de Base de Données | Stocker, gérer et fournir des données aux applications.                                                                             | MySQL, PostgreSQL, Oracle              |
| Serveur de Fichiers        | Stocker et gérer des fichiers, permettant aux clients d'accéder, de sauvegarder et de partager des fichiers.                        | FTP, NFS, SMB/CIFS                     |
| Serveur de Messagerie      | Gérer l'envoi, la réception et le stockage des emails.                                                                              | Microsoft Exchange, Postfix, Sendmail  |
| Serveur d'Applications     | Héberger des applications et fournir des services logiques à d'autres applications.                                                 | Apache Tomcat, JBoss, WebSphere        |
| Serveur de Jeu             | Héberger des jeux vidéo en ligne et permettre à plusieurs joueurs de se connecter et de jouer ensemble.                             | Minecraft Server, Steam Server         |
| Serveur Proxy              | Servir d'intermédiaire pour les requêtes entre les clients et d'autres serveurs, améliorant la sécurité et les performances.        | Squid, HAProxy                         |
| Serveur DNS                | Traduire les noms de domaine en adresses IP.                                                                                        | BIND, Microsoft DNS                    |
| Serveur DHCP               | Attribuer dynamiquement des adresses IP aux clients sur un réseau.                                                                  | isc-dhcp-server, Microsoft DHCP Server |
| Serveur FTP                | Gérer le transfert de fichiers entre ordinateurs via le protocole FTP.                                                              | vsftpd, FileZilla Server               |
| Serveur LDAP               | Gérer et fournir des services d'annuaire pour stocker les informations sur les utilisateurs, les groupes, et les ressources réseau. | OpenLDAP, Microsoft Active Directory   |
| Serveur de Streaming       | Diffuser des médias audio et vidéo en temps réel aux clients.                                                                       | Wowza, Red5, Icecast                   |
| Serveur de Sauvegarde      | Effectuer et gérer les sauvegardes de données critiques.                                                                            | Bacula, Amanda, Veeam                  |
| Serveur HTTP           | Héberger des sites web et fournir du contenu web via le protocole HTTP.                                                             | Apache HTTP Server, Nginx ...      |
| **Serveur IRC**                | Héberger et gérer des discussions en temps réel via le protocole IRC (Internet Relay Chat).                                         | UnrealIRCd, ircd, InspIRCd             |

### Détails supplémentaires

- **Serveur Web** : Essentiel pour héberger des sites web accessibles via des navigateurs.
- **Serveur de Base de Données** : Crucial pour les applications nécessitant des opérations de stockage et de gestion de données.
- **Serveur de Fichiers** : Utile pour le partage et la gestion de fichiers dans des environnements collaboratifs.
- **Serveur de Messagerie** : Indispensable pour les communications par email.
- **Serveur d'Applications** : Fournit une plateforme pour exécuter des applications métiers.
- **Serveur de Jeu** : Permet aux joueurs de se connecter et de jouer ensemble en ligne.
- **Serveur Proxy** : Améliore la sécurité et les performances en agissant comme intermédiaire.
- **Serveur DNS** : Facilite la navigation internet en traduisant les noms de domaine en adresses IP.
- **Serveur DHCP** : Simplifie la gestion des adresses IP sur un réseau.
- **Serveur FTP** : Spécialisé dans le transfert de fichiers via le protocole FTP.
- **Serveur LDAP** : Gère les informations d'annuaire pour les utilisateurs et les ressources réseau.
- **Serveur de Streaming** : Diffuse du contenu multimédia en temps réel.
- **Serveur de Sauvegarde** : Assure la protection des données en effectuant des sauvegardes régulières.
- **Serveur IRC** : Permet d'héberger et de gérer des discussions en temps réel, couramment utilisé pour les discussions en groupe ou les communautés en ligne.

## Serveur IRC

[Consulter ceci pour savoir ce qu'es un Serveur IRC ?](./Serveur_IRC.md)

## Le Client

Après avoir expliqué le rôle du serveur, il est important de se pencher sur les **clients**. Un client est une application ou un système utilisé pour se connecter à un serveur et interagir avec lui.

### Les différents clients pour IRC

Pour un serveur IRC, voici quelques exemples de clients :

- **mIRC** : Un client IRC populaire sous Windows, avec une interface simple et de nombreuses fonctionnalités.
- **HexChat** : Multi-plateforme et open source, idéal pour une utilisation intuitive.
- **irssi** : Client IRC en ligne de commande, adapté pour les utilisateurs avancés.
- **WeeChat** : Client IRC modulaire, conçu pour être extensible et personnalisable.
- **The Lounge** : Client IRC moderne accessible via un navigateur web.

> Dans ce projet, nous devons développer uniquement le **serveur**, pas le client. Pour tester et interagir avec le serveur, nous utiliserons le client [**irssi**](./Serveur_IRC.md).  

## Liste de toutes les fonctions externes autorisées

Consultez le manuel de chaque fonction pour comprendre son fonctionnement.

| Compris | Nom de la fonction                                        | En-tête de la bibliothèque | Description brève                                                                                                |
|---------|-----------------------------------------------------------|----------------------------|------------------------------------------------------------------------------------------------------------------|
|    ✔️    | [socket](./laboratoire/socket/main.cpp)                   | `<sys/socket.h>`            | Crée un nouveau socket.                                                                                         |
|    ✔️    | [close](./laboratoire/close/main.cpp)                     | `<unistd.h>`                | Ferme un descripteur de fichier.                                                                                |
|    ✔️    | [setsockopt](./laboratoire/setsockopt/main.cpp)           | `<sys/socket.h>`            | Modifie les options associées à un socket.                                                                      |
|    ✔️    | [getsockname](./laboratoire/getsockname/main.cpp)         | `<sys/socket.h>`            | Récupère le nom local d'un socket.                                                                              |
|    ✔️    | [getprotobyname](./laboratoire/getprotobyname/main.cpp)   | `<netdb.h>`                 | Récupère les informations sur un protocole réseau à partir de son nom.                                          |
|    ✔️    | [gethostbyname](./laboratoire/gethostbyname/main.cpp)   | `<netdb.h>`                 | Récupère les informations sur un hôte réseau à partir de son nom.                                          |
|    ✔️    | [getaddrinfo](./laboratoire/getaddrinfo/main.cpp)         | `<netdb.h>`                 | Résout un nom d'hôte et un service (port) en une liste d'adresses réseau.                                       |
|    ✔️    | [freeaddrinfo](./laboratoire/freeaddrinfo/main.cpp)       | `<netdb.h>`                 | Libère la mémoire allouée par getaddrinfo.                                                                      |
|    ✔️    | [bind](./laboratoire/bind/main.cpp)                       | `<sys/socket.h>`            | Associe une adresse à un socket.                                                                                |
|    ✔️    | [connect](./laboratoire/connect/main.cpp)                 | `<sys/socket.h>`            | Établit une connexion avec un socket.                                                                           |
|    ✔️    | [listen](./laboratoire/listen/main.cpp)                   | `<sys/socket.h>`            | Met un socket en mode écoute pour les connexions entrantes.                                                     |
|    ✔️    | [accept](./laboratoire/accept/main.cpp)                   | `<sys/socket.h>`            | Accepte une connexion sur un socket.                                                                            |
|    ✔️    | [htons](./laboratoire/htons/main.cpp)                     | `<arpa/inet.h>`            | Convertit un entier court (16 bits) de l'ordre de l'hôte vers l'ordre du réseau (big-endian).                    |
|    ✔️    | [htonl](./laboratoire/htonl/main.cpp)                     | `<arpa/inet.h>`            | Convertit un entier long (32 bits) de l'ordre de l'hôte vers l'ordre du réseau (big-endian).                     |
|    ✔️    | [ntohs](./laboratoire/ntohs/main.cpp)                     | `<arpa/inet.h>`            | Convertit un entier court (16 bits) de l'ordre du réseau (big-endian) vers l'ordre de l'hôte.                    |
|    ✔️    | [ntohl](./laboratoire/ntohl/main.cpp)                     | `<arpa/inet.h>`            | Convertit un entier long (32 bits) de l'ordre du réseau (big-endian) vers l'ordre de l'hôte.                     |
|    ✔️    | [inet_addr](./laboratoire/inet_addr/main.cpp)   | `<arpa/inet.h>`             | Convertit une adresse IPv4 de la notation en point décimal en une structure binaire en notation réseau.       |
|    ✔️    | [inet_ntoa](./laboratoire/inet_ntoa/main.cpp)   | `<arpa/inet.h>`             | Convertit une adresse IPv4 en notation réseau en une chaîne de caractères en notation en point décimal.       |
|    ✔️    | [send](./laboratoire/send/main.cpp)                       | `<sys/socket.h>`            | Envoie des données sur un socket.                                                                               |
|    ✔️    | [recv](./laboratoire/recv/main.cpp)                       | `<sys/socket.h>`            | Reçoit des données depuis un socket.                                                                            |
|    ✔️    | [signal](./laboratoire/signal/main.cpp)                   | `<signal.h>`                | Définit un gestionnaire de signal pour un signal spécifique.                                                    |
|    ✔️    | [sigaction](./laboratoire/sigaction/main.cpp)   | `<signal.h>`                | Modifie l'action associée à un signal spécifique.                                                              |
|    ✔️    | [fcntl](./laboratoire/fcntl/main.cpp)                     | `<fcntl.h>`                 | Modifie les attributs d'un descripteur de fichier.                                                              |
|    ✔️    | **[poll](./laboratoire/poll/main.cpp)**                       | `<poll.h>`                 | Surveille plusieurs descripteurs de fichiers pour des événements d'entrée-sortie.                                |
|    ✔️    | [lseek](./laboratoire/lseek/main.cpp)           | `<unistd.h>`                | Déplace le pointeur de lecture/écriture dans un fichier ouvert.                                                |
|    ✔️    | [fstat](./laboratoire/fstat/main.cpp)           | `<sys/stat.h>`              | Récupère les informations sur un fichier ouvert.                                                               |

Légende :

- 🤔 = pas compris l'utilite ou le fonctionement.
- ✔️ = compris.
- ❌ = pas enocre documenté.
- 🤨 = un peut compris mais pas à 100%.
- 🛑 = Probleme pas possible dexecuter du à l'os

## Qu'est-ce qu'un processus

En informatique, un processus est une instance d'un programme en cours d'exécution. Il comprend le code du programme, ses données, son espace d'adressage mémoire et les ressources système nécessaires à son fonctionnement. Un processus peut être créé, exécuté, suspendu, repris et terminé, et il peut interagir avec d'autres processus et les ressources système.

## C'est quoi un socket

En informatique, un socket est un point de terminaison pour la communication entre deux machines sur un réseau. Il permet à un processus d'envoyer et de recevoir des données sur le réseau en utilisant des protocoles de communication tels que TCP ou UDP.

## Commande `nc`

### Syntaxe Générale

La commande `nc` (Netcat) est utilisée pour lire et écrire des données sur des connexions réseau en utilisant les protocoles TCP ou UDP.

### Options Principales

- `-l` : Écouter des connexions entrantes.
- `-p` : Spécifier le port local à utiliser.
- `-u` : Utiliser le protocole UDP au lieu de TCP.
- `-v` : Mode verbeux. Affiche des informations supplémentaires sur ce qui se passe.
- `-w` : Spécifier un délai d'attente en secondes.

### Exemples

- Écouter des connexions sur le port 1234 :
  ```sh
  nc -l -p 1234
  ```

- Se connecter à un serveur sur le port 1234 :
  ```sh
  nc 192.168.1.1 1234
  ```

---

## Les fichier .ipp

Les fichiers `.ipp` sont des fichiers spécifiques à C++ utilisés pour définir des fonctions ou des méthodes de classes dans le cadre de modèles (**templates**). Ils servent à résoudre un problème lié à la séparation des déclarations et des définitions lorsque l’on travaille avec des templates.

### Pourquoi utiliser des fichiers `.ipp` ?
En C++, les définitions de templates doivent être visibles au moment de la compilation. Cela signifie qu’on ne peut pas séparer les déclarations (dans un `.hpp`) et les définitions (dans un `.cpp`) comme pour les classes ou les fonctions ordinaires. Pour organiser le code, les développeurs utilisent souvent des fichiers `.ipp` pour contenir les définitions des templates.

### Utilisation typique
- **Fichier `.hpp`** : Contient les déclarations des templates.
- **Fichier `.ipp`** : Contient les définitions des templates.
- **Inclusion** : Le fichier `.ipp` est inclus à la fin du fichier `.hpp` (ou dans le `.cpp` si nécessaire).

Exemple :  

**my_template.hpp**  
```cpp
#ifndef MY_TEMPLATE_HPP
#define MY_TEMPLATE_HPP

#include <iostream>

template <typename T>
class MyTemplate {
public:
    MyTemplate(T value);
    void display() const;
private:
    T _value;
};

#include "my_template.ipp" // Inclusion du fichier .ipp
#endif
```

**my_template.ipp**  
```cpp
template <typename T>
MyTemplate<T>::MyTemplate(T value) : _value(value) {}

template <typename T>
void MyTemplate<T>::display() const {
    std::cout << _value << std::endl;
}
```

Ainsi, le fichier `.ipp` améliore la lisibilité et permet de structurer le code proprement tout en respectant les exigences des templates.