# Cahier des charges

Samira Come travailleir pouilleux d'esclave xD

JE rigole ce fichier permet de faire le cahier des charges et dire ce qu'il faut faire.

## Table of Contents / Sommaire
- [Cahier des charges](#cahier-des-charges)
	- [Table of Contents / Sommaire](#table-of-contents--sommaire)
	- [1. **Contexte et Objectif**](#1-contexte-et-objectif)
	- [2. **Règles d'Équipe**](#2-règles-déquipe)
		- [Règle 1 : **Commentaires et Lisibilité**](#règle-1--commentaires-et-lisibilité)
		- [Règle 2 : **Organisation des Fichiers**](#règle-2--organisation-des-fichiers)
		- [Règle 3 : **Méthodes et Communication**](#règle-3--méthodes-et-communication)
	- [3. **Étapes de Développement**](#3-étapes-de-développement)
		- [3.1. **Étape 1 : Parsing des Arguments**](#31-étape-1--parsing-des-arguments)
		- [3.2. **Étape 2 : Initialisation du Serveur**](#32-étape-2--initialisation-du-serveur)
		- [3.3. **Étape 3 : Gestion des Connexions Client**](#33-étape-3--gestion-des-connexions-client)
		- [3.4. **Étape 4 : Gestion des Canaux IRC**](#34-étape-4--gestion-des-canaux-irc)
		- [3.5. **Étape 5 : Communication Client-Serveur**](#35-étape-5--communication-client-serveur)
		- [3.6. **Étape 6 : Gestion des Erreurs et Sécurité**](#36-étape-6--gestion-des-erreurs-et-sécurité)
		- [3.7. **Étape 7 : Tests et Validation**](#37-étape-7--tests-et-validation)
		- [3.8. **Étape 8 : Documentation et Rendu**](#38-étape-8--documentation-et-rendu)
	- [4. **Partie Bonus (Optionnelle)**](#4-partie-bonus-optionnelle)


## 1. **Contexte et Objectif**
Le projet vise à développer un serveur IRC en C++98. Le serveur permettra aux clients IRC de se connecter, de rejoindre des canaux, d'échanger des messages, et d'utiliser des commandes spécifiques à IRC.

## 2. **Règles d'Équipe**

![Team work gif](./illusatrion/teamwork-go-team.gif)

### Règle 1 : **Commentaires et Lisibilité**
- **Commenter le code** : Chaque membre de l'équipe doit commenter son code de manière exhaustive. Chaque fonction, méthode, et classe doit être documentée pour expliquer clairement son objectif, ses paramètres et sa logique.

- **Lisibilité du code** : La priorité absolue est de garantir un code clair et compréhensible pour tous les membres de l'équipe. Le code doit être structuré de manière à faciliter sa maintenance et son évolution.

### Règle 2 : **Organisation des Fichiers**
- **Organisation par classe** : Chaque classe doit être rangée dans son propre dossier. Ce dossier contiendra le fichier header (.h ou .hpp) ainsi que le fichier d'implémentation (.cpp, .ipp, ou .tpp) correspondant.

- **Structure des dossiers** : Les dossiers doivent être nommés de manière claire et cohérente pour refléter la fonction ou le domaine d'application des classes qu'ils contiennent.

### Règle 3 : **Méthodes et Communication**
- **Création de méthodes et de classes** : Les méthodes et les classes doivent être conçues de manière simple et compréhensible, avec des noms explicites qui reflètent leur fonction. Le découpage du code en méthodes et classes doit respecter le principe de responsabilité unique pour faciliter la réutilisation et le débogage.

- **Communication** : Chaque membre de l'équipe doit informer les autres dès qu'il effectue un changement significatif dans le code ou ajoute une nouvelle fonctionnalité. Une communication constante est essentielle pour assurer la cohésion du projet et éviter les doublons ou les conflits.

## 3. **Étapes de Développement**

### 3.1. **Étape 1 : Parsing des Arguments**
- **Description** : La première étape consiste à vérifier les arguments fournis lors du lancement du serveur.
- **Tâches** :
  1. **Récupération des arguments** : Récupérer les arguments `port` et `password` passés à l'exécution du serveur.
  2. **Vérification des arguments** :
     - S'assurer que le nombre d'arguments est correct.
     - Vérifier que le `port` est un numéro valide.
     - Vérifier que le `password` n'est pas vide.
  3. **Gestion des erreurs** :
     - Si un argument est invalide, lever une exception ou afficher un message d'erreur approprié, puis terminer le programme.

### 3.2. **Étape 2 : Initialisation du Serveur**
- **Description** : Mettre en place le serveur en le configurant pour écouter les connexions entrantes sur le port spécifié.
- **Tâches** :
  1. **Création du socket** : Utiliser `socket()` pour créer un socket d'écoute.
  2. **Bind du socket** : Associer le socket à l'adresse IP et au port spécifié à l'aide de `bind()`.
  3. **Mise en écoute** : Configurer le socket pour qu'il écoute les connexions entrantes avec `listen()`.
  4. **Configurer le serveur pour accepter les connexions multiples** : Préparer le serveur pour gérer plusieurs clients simultanément en mode non-bloquant.

### 3.3. **Étape 3 : Gestion des Connexions Client**
- **Description** : Gérer les connexions entrantes des clients IRC.
- **Tâches** :
  1. **Acceptation des connexions** : Utiliser `accept()` pour accepter les nouvelles connexions.
  2. **Authentification des clients** :
     - Recevoir et vérifier le mot de passe fourni par le client.
     - Si le mot de passe est incorrect, refuser la connexion.
  3. **Gestion des utilisateurs** :
     - Gérer les `nickname` et `username` fournis par les clients.
     - Stocker les informations des clients connectés (adresse IP, port, nickname, etc.).

### 3.4. **Étape 4 : Gestion des Canaux IRC**
- **Description** : Implémenter la création et la gestion des canaux de discussion.
- **Tâches** :
  1. **Rejoindre un canal** : Permettre à un client de créer ou rejoindre un canal avec la commande `JOIN`.
  2. **Gestion des messages** : Diffuser les messages envoyés dans un canal à tous les membres du canal.
  3. **Commandes de gestion des canaux** :
     - Implémenter les commandes `KICK`, `INVITE`, `TOPIC`, et `MODE` pour les administrateurs de canal.

### 3.5. **Étape 5 : Communication Client-Serveur**
- **Description** : Assurer la communication entre le client et le serveur via TCP/IP.
- **Tâches** :
  1. **Envoi et réception des messages** : Utiliser `send()` et `recv()` pour échanger des messages entre le serveur et les clients.
  2. **Non-Blocking IO** : S'assurer que toutes les opérations d'IO (lecture, écriture, etc.) sont non-bloquantes.
  3. **Utilisation de `poll()` ou équivalent** : Implémenter `poll()` pour surveiller les différents descripteurs de fichier (FD) et gérer les événements (nouvelle connexion, message reçu, etc.).

### 3.6. **Étape 6 : Gestion des Erreurs et Sécurité**
- **Description** : Mettre en place des mécanismes pour gérer les erreurs et assurer la sécurité du serveur.
- **Tâches** :
  1. **Gestion des erreurs de connexion** : Gérer les erreurs lors des connexions et des communications (timeout, connexion interrompue, etc.).
  2. **Validation des entrées** : Valider toutes les entrées utilisateur pour éviter les attaques courantes (e.g., injection de commandes).
  3. **Logs** : Implémenter un système de logs pour suivre les actions du serveur et les événements importants (connexions, erreurs, etc.).

### 3.7. **Étape 7 : Tests et Validation**
- **Description** : Valider le bon fonctionnement du serveur à l'aide de tests.
- **Tâches** :
  1. **Tests unitaires** : Écrire des tests pour chaque fonction critique (parsing des arguments, gestion des canaux, etc.).
  2. **Tests de charge** : Simuler plusieurs clients se connectant en même temps pour tester la robustesse du serveur.
  3. **Tests de conformité** : Utiliser un client IRC de référence pour vérifier que le serveur respecte les spécifications IRC.

### 3.8. **Étape 8 : Documentation et Rendu**
- **Description** : Préparer la documentation et rendre le projet.
- **Tâches** :
  1. **Documentation du code** : Ajouter des commentaires et documenter les fonctions pour faciliter la compréhension du code.
  2. **README** : Rédiger un fichier README expliquant comment compiler, exécuter et tester le serveur.
  3. **Rendu Git** : Pousser le projet sur le dépôt Git en s'assurant que tous les fichiers nécessaires (code, Makefile, README) sont présents et conformes.

## 4. **Partie Bonus (Optionnelle)**
- **Envoi de fichiers** : Ajouter une fonctionnalité permettant l'envoi de fichiers entre les clients via le serveur.
- **Bot IRC** : Développer un bot IRC capable d'interagir automatiquement avec les utilisateurs.
