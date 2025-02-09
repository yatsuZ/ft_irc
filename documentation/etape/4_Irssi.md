# 4. Irssi et le Protocole IRC

## Table des matières

- [4. Irssi et le Protocole IRC](#4-irssi-et-le-protocole-irc)
  - [Table des matières](#table-des-matières)
  - [Contexte](#contexte)
  - [Objectif](#objectif)
  - [Fonctionnement de Irssi](#fonctionnement-de-irssi)
  - [Protocole IRC](#protocole-irc)
    - [Définition de RFC](#définition-de-rfc)
    - [RFC du protocole IRC](#rfc-du-protocole-irc)
    - [Définition de RPL](#définition-de-rpl)
  - [Format des messages IRC](#format-des-messages-irc)
    - [Structure du message IRC](#structure-du-message-irc)
    - [Réponses IRC : Codes RPL et erreurs](#réponses-irc--codes-rpl-et-erreurs)
      - [Exemples de réponses RPL](#exemples-de-réponses-rpl)
      - [Exemples d'erreurs](#exemples-derreurs)
    - [Tableau des commandes client IRC et réponses du serveur](#tableau-des-commandes-client-irc-et-réponses-du-serveur)
    - [Explications supplémentaires](#explications-supplémentaires)
    - [Documentation utile](#documentation-utile)

---

## Contexte

Le serveur IRC que nous utilisons est capable de recevoir des messages et d'interagir avec un client comme **Irssi**. Toutefois, pour comprendre comment le client communique avec le serveur, il est crucial de connaître les commandes de base envoyées par Irssi, telles que `CAP`, `NICK`, `USER`, et d'autres commandes IRC standard. Connaître ces commandes et leur traitement par le serveur IRC est essentiel pour gérer efficacement les interactions.

---

## Objectif

L'objectif de cette section est de clarifier comment les commandes envoyées par Irssi interagissent avec le serveur IRC. Nous fournirons également un tableau répertoriant les commandes que le serveur peut interpréter, les arguments nécessaires, et une description de leur fonction. En outre, nous inclurons des liens vers la documentation officielle pour aider à mieux comprendre leur usage.

---

## Fonctionnement de Irssi

Irssi fonctionne généralement comme suit :

1. **Connexion au serveur IRC** :  
   La première commande qu'Irssi utilise pour se connecter à un serveur IRC est :
   ```
   /connect [ip] [port]
   ```
   Une fois connecté, Irssi commencera à envoyer diverses commandes au serveur.

2. **Envoi de commandes** :  
   Après la connexion, Irssi peut envoyer des commandes pour s'authentifier, rejoindre des canaux, envoyer des messages, etc. Cela inclut des commandes comme `NICK`, `USER`, `JOIN`, `PRIVMSG`, etc.

3. **Réception des réponses** :  
   Le serveur IRC doit répondre aux commandes d'Irssi selon le protocole IRC. Par exemple, après une commande de type `NICK`, le serveur répond généralement par une confirmation de l'assignation du pseudo ou par un message d'erreur si le pseudo est déjà pris.

---

## Protocole IRC

### Définition de RFC

Une **RFC** (Request for Comments) sont publiées par l'[IETF](https://fr.wikipedia.org/wiki/Internet_Engineering_Task_Force) (Internet Engineering Task Force) est un document officiel qui décrit des spécifications techniques, des protocoles, ou des procédures utilisées sur Internet. Dans le contexte d'IRC, une RFC définit la manière dont les clients IRC et les serveurs doivent communiquer, en détaillant les commandes, les messages, et les codes de réponse utilisés.

Les RFC sont couramment utilisées pour normaliser les interactions entre systèmes et garantir qu'ils puissent comprendre et traiter les messages de manière cohérente. Elles ne se limitent pas uniquement à IRC, mais sont également employées pour définir d'autres protocoles importants tels que :

- HTTP (RFC 7230 et suivantes, spécifiant la communication entre clients et serveurs web),
- SMTP (RFC 5321, définissant l'envoi de courriers électroniques),
- TCP/IP (RFC 793 pour TCP et RFC 791 pour IP, régissant la communication de bas niveau sur Internet),
- DNS (RFC 1035, décrivant la résolution des noms de domaine),
- et bien d'autres encore.
---

### RFC du protocole IRC

Le protocole IRC est principalement défini dans plusieurs RFCs, dont les plus importantes sont :

- **[RFC 1459](https://tools.ietf.org/html/rfc1459)** : Spécification originale du protocole IRC, définissant les bases des communications entre clients et serveurs IRC.
- **[RFC 2812](https://tools.ietf.org/html/rfc2812)** : Mise à jour de la RFC 1459, précisant les messages et commandes utilisés entre client et serveur.
- **[RFC 2813](https://tools.ietf.org/html/rfc2813)** : Décrit le fonctionnement des serveurs IRC et leurs interactions.

Ces RFCs spécifient les commandes, la syntaxe des messages, les codes de réponse, et les erreurs possibles dans les communications entre clients et serveurs IRC.

---

### Définition de RPL

Les **RPL (Reply)** sont des codes numériques envoyés par un serveur IRC pour informer un client de l'état de la connexion ou des actions effectuées. Ils sont utilisés dans les réponses du serveur pour signaler un état particulier, comme une connexion réussie, la liste des utilisateurs d'un canal, ou un message d'erreur.

Exemples :
- **`001 RPL_WELCOME`** : Message de bienvenue après une connexion réussie.
- **`353 RPL_NAMREPLY`** : Liste des utilisateurs d'un canal.

Ces réponses permettent au client de comprendre l'état actuel du serveur et d'afficher des informations utiles à l'utilisateur.

---

## Format des messages IRC

### Structure du message IRC

Le format des messages IRC suit une structure bien définie :

```
[prefix] <commande> <paramètres> :<message> <CRLF>
```

1. **[prefix]** :  
   - Un préfixe est utilisé pour indiquer l'émetteur du message. Cela peut être le nom du serveur (`:irc.server.com`) ou le pseudo de l'utilisateur (`:nickname`).
   - Le préfixe est précédé d'un `:` et peut être omis dans certaines réponses du serveur.

2. **<commande>** :  
   - La commande IRC elle-même (par exemple `NICK`, `USER`, `JOIN`, `PRIVMSG`, etc.).

3. **<paramètres>** :  
   - Les paramètres associés à la commande, comme un pseudo pour `NICK`, un canal pour `JOIN`, ou un message pour `PRIVMSG`.

4. **:<message>** :  
   - Un message texte qui peut être inclus dans certaines commandes, comme dans `PRIVMSG` pour envoyer un message à un utilisateur ou un canal.

5. **<CRLF>** :  
   - Chaque message IRC se termine par un **CRLF** (Carriage Return + Line Feed), soit les caractères `\r` et `\n`.
   - Le **CR** (Carriage Return) est un retour chariot, qui déplace le curseur au début de la ligne, tandis que le **LF** (Line Feed) fait avancer le curseur à la ligne suivante. Cette séquence est utilisée pour signaler la fin du message et permettre au serveur ou au client de traiter correctement chaque ligne de message.

---

### Réponses IRC : Codes RPL et erreurs

Les réponses IRC suivent également un format structuré, où le serveur envoie des codes de réponse numériques (RPL) pour signaler l'état des commandes reçues. Les erreurs sont aussi indiquées par des codes d'erreur numériques.

#### Exemples de réponses RPL

| Code  | Nom                | Signification                               |
|-------|--------------------|---------------------------------------------|
| 001   | RPL_WELCOME        | Message de bienvenue après la connexion     |
| 002   | RPL_YOURHOST       | Informations sur le serveur                 |
| 003   | RPL_CREATED        | Date de création du serveur                 |
| 004   | RPL_MYINFO         | Informations sur la version du serveur      |
| 353   | RPL_NAMREPLY       | Liste des utilisateurs d'un canal           |

#### Exemples d'erreurs

| Code  | Nom                  | Signification                              |
|-------|----------------------|--------------------------------------------|
| 401   | ERR_NOSUCHNICK       | L'utilisateur demandé n'existe pas         |
| 403   | ERR_NOSUCHCHANNEL    | Le canal demandé n'existe pas              |
| 431   | ERR_NONICKNAMEGIVEN  | Aucun pseudo fourni                        |
| 432   | ERR_ERRONEUSNICKNAME | Pseudo invalide                            |
| 433   | ERR_NICKNAMEINUSE    | Pseudo déjà utilisé                        |

---

### Tableau des commandes client IRC et réponses du serveur

| Commande  | Arguments                                       | Description                                           | Réponses du serveur                  |
|-----------|-------------------------------------------------|-------------------------------------------------------|--------------------------------------|
| `NICK`    | `<nickname>`                                    | Définit ou change le pseudo                           | `001`, `433`                         |
| `USER`    | `<username> <hostname> <servername> <realname>` | Identifie l'utilisateur                               | `001`, `002`, `003`, `004`           |
| `JOIN`    | `<#channel>`                                    | Rejoint un canal                                      | `353`, `366`                         |
| `PART`    | `<#channel>`                                    | Quitte un canal                                       | `403` (si canal inexistant)          |
| `PRIVMSG` | `<target> <message>`                            | Envoie un message privé                               | `401` (si utilisateur inexistant)    |
| `NOTICE`  | `<target> <message>`                            | Envoie un message sans notification sonore            | -                                    |
| `PING`    | `<server1> [<server2>]`                         | Vérifie la connexion avec le serveur                  | `PONG`                               |
| `PONG`    | `<server>`                                      | Réponse au PING                                       | -                                    |
| `QUIT`    | `[message]`                                     | Déconnecte l'utilisateur                              | -                                    |
| `TOPIC`   | `<#channel> [<topic>]`                          | Change ou affiche le sujet du canal                   | `403`, `331`, `332`                  |
| `WHOIS`   | `<nickname>`                                    | Affiche des informations sur un utilisateur           | `318`, `301`, `311`, `312`, `313`    |
| `MODE`    | `<target> [<mode>]`                             | Modifie les paramètres d'un utilisateur ou d'un canal | `324`, `329`, `330`                  |
| `CAP`     | `<subcommand>`                                  | Gère les capacités du client IRC                      | `CAP * LS`, `CAP * ACK`, `CAP * NAK` |

### Explications supplémentaires

Certaines commandes nécessitent des explications supplémentaires :
- **`NICK`** : Si le pseudo est déjà pris, le serveur renvoie `433 ERR_NICKNAMEINUSE`.
- **`USER`** : Cette commande est obligatoire pour s'identifier après la connexion. Elle permet d'envoyer des informations sur l'utilisateur.
- **`JOIN`** : Si le canal n'existe pas, il est automatiquement créé.
- **`PRIVMSG`** : Utilisée pour envoyer un message à un utilisateur ou à un canal. Si l'utilisateur n'existe pas, une erreur `401 ERR_NOSUCHNICK` est renvoyée.
- **`PING/PONG`** : Utilisé pour maintenir la connexion entre le client et le serveur. Le serveur répond à chaque `PING` par un `PONG`.
- **WHOIS** : Permet d'afficher des informations sur un utilisateur, comme son pseudo, son host, ses modes, etc. Les codes de réponse comme `311` donnent les informations de base (pseudo, nom réel), tandis que `318` marque la fin de la réponse.
- **MODE** : Utilisé pour changer des paramètres de canal ou d'utilisateur, tels que les modes de canal (`+o`, `+v` pour donner des rôles) ou les modes d'utilisateur (`+i` pour invisible, `+o` pour opérateur).
- **CAP** : Gère les capacités du client IRC, permettant d'activer ou de désactiver certaines fonctionnalités comme les extensions de messages, les UTF-8, etc. La commande `CAP * LS` permet de lister les capacités disponibles, et `CAP * ACK` permet de les activer.

---

### Documentation utile

- [RFC 2812 - IRC Client Protocol](https://tools.ietf.org/html/rfc2812)
- [Liste complète des réponses IRC](https://www.alien.net.au/irc/irc2numerics.html)