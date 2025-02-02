# 4. Irssi

## Table des matières

- [4. Irssi](#4-irssi)
	- [Table des matières](#table-des-matières)
	- [Contexte](#contexte)
	- [Objectif](#objectif)
	- [Fonctionnement de Irssi](#fonctionnement-de-irssi)
	- [Protocole IRC](#protocole-irc)
		- [Références importantes :](#références-importantes-)
		- [**Tableau des commandes client IRC et réponses du serveur**](#tableau-des-commandes-client-irc-et-réponses-du-serveur)
		- [**Explications supplémentaires**](#explications-supplémentaires)
		- [**Documentation utile**](#documentation-utile)

---

## Contexte

Le serveur IRC que nous utilisons est capable de recevoir des messages et d'interagir avec un client comme **Irssi**. Cependant, pour comprendre comment le client communique avec le serveur, il est essentiel de connaître les commandes de base envoyées par Irssi, telles que `CAP`, `NICK`, `USER`, et d'autres commandes IRC standard. Il est donc important de comprendre comment ces commandes sont interprétées par le serveur afin de gérer efficacement les interactions.

## Objectif

L'objectif de cette section est de créer un tableau répertoriant toutes les commandes que notre serveur IRC est capable d'interpréter, de spécifier leurs arguments nécessaires et de décrire leur fonction. Nous devons également ajouter des liens vers la documentation officielle ou d'autres ressources pour aider à mieux comprendre leur usage.

## Fonctionnement de Irssi

Le client Irssi fonctionne généralement de la manière suivante : 

1. **Se connecter au serveur IRC** : La première commande qu'Irssi utilise pour se connecter à un serveur est :
   ```
   /connect [ip] [port]
   ```
   Une fois connecté, Irssi commencera à envoyer diverses commandes IRC au serveur.

2. **Envoi de commandes** : Après la connexion, Irssi peut envoyer différentes commandes pour s'authentifier, rejoindre des canaux, envoyer des messages, etc.

3. **Réception des réponses** : Le serveur doit répondre aux commandes d'Irssi selon le protocole IRC. Par exemple, après une commande de type `NICK`, le serveur répondra généralement par une confirmation de l'assignation du pseudo ou un message d'erreur si le pseudo est déjà pris.

## Protocole IRC

Le **protocole IRC** (Internet Relay Chat) est un standard de communication pour la messagerie instantanée en temps réel. Il définit les règles de communication entre les clients IRC (comme Irssi) et les serveurs IRC. Le protocole est basé sur un ensemble de commandes et de réponses textuelles qui permettent l'échange d'informations entre utilisateurs et canaux.

Voici les points clés du protocole IRC :

1. **Établissement de la connexion** : Le client se connecte à un serveur IRC via un port dédié (habituellement le port 6660 à 6669). Une fois la connexion établie, le client s'identifie avec des commandes comme `NICK` (pour définir son pseudo) et `USER` (pour définir des informations sur l'utilisateur).

2. **Échange de messages** : Les messages sont envoyés via la commande `PRIVMSG` pour des messages privés ou `JOIN` pour rejoindre un canal. Ces messages sont acheminés par le serveur vers les destinataires appropriés.

3. **Maintien de la connexion** : Le serveur envoie périodiquement des messages `PING` pour vérifier que le client est toujours connecté. Le client doit répondre avec un message `PONG` pour confirmer sa disponibilité.

4. **Commandes de gestion des canaux** : Le serveur permet la création et la gestion de canaux via des commandes comme `JOIN` (pour rejoindre un canal), `PART` (pour quitter un canal), ou `TOPIC` (pour définir un sujet de canal).

5. **Réponses du serveur** : Le serveur répond à toutes les commandes par des messages normalisés, comprenant des informations comme des numéros de réponse (par exemple, `RPL_WELCOME` pour accueillir un utilisateur), ou des erreurs (par exemple, `ERR_NICKNAMEINUSE` si un pseudonyme est déjà pris).

6. **Modularité et extensions** : IRC permet l'extension de ses fonctionnalités de base par des mécanismes comme les **CAP** (capabilities), permettant la négociation de capacités supplémentaires (par exemple, la prise en charge de messages privés SSL ou de certaines fonctionnalités d'extensions de canaux).

Le protocole IRC est défini principalement par la **RFC 1459**, mais de nombreuses extensions ont été ajoutées au fil du temps pour améliorer ses fonctionnalités et sa flexibilité. Le protocole IRC est largement utilisé dans des services comme **IRCCloud**, **Freenode**, et d'autres réseaux IRC.

### Références importantes :
- [Wikipedia de irc](https://fr.wikipedia.org/wiki/Internet_Relay_Chat#Aspects_techniques)
- [IRC guide github](https://gist.github.com/ComputerTech312/bdb688b8af73df38b09be647f692285c)


### **Tableau des commandes client IRC et réponses du serveur**

| **Commande Client**                              | **Description**                                                                 | **Réponse du Serveur**                                                                                                     |
|--------------------------------------------------|---------------------------------------------------------------------------------|---------------------------------------------------------------------------------------------------------------------------|
| `CAP LS`                                         | Demande les fonctionnalités que le serveur supporte.                            | `:serveur CAP * LS :<capabilités>`                                                                                         |
| `CAP REQ :<capabilité>`                          | Demande d'activer une ou plusieurs fonctionnalités spécifiques.                  | `:serveur CAP * ACK :<capabilité>` ou `:serveur CAP * NAK :<capabilité>`                                                    |
| `CAP END`                                        | Indique que le client a terminé la négociation des fonctionnalités.             | Aucune réponse nécessaire.                                                                                                  |
| `NICK <pseudo>`                                  | Définit ou change le pseudonyme du client.                                       | `:serveur 001 <pseudo> :Bienvenue sur le réseau IRC, <pseudo>` ou `:serveur 433 * <pseudo> :Ce pseudo est déjà pris`        |
| `USER <utilisateur> <hote> <serveur> :<nom réel>`| Envoie des informations sur l'utilisateur.                                      | `:serveur 002 <pseudo> :Votre hôte est <serveur>, version X.X`                                                              |
| `PASS <mot-de-passe>`                            | Permet à l'utilisateur de se connecter avec un mot de passe si le serveur nécessite une authentification. | `:serveur 001 <pseudo> :Authentification réussie` ou `:serveur 464 * :Invalid password`                                    |
| `PING <token>`                                   | Vérifie si le serveur est actif.                                                | `:serveur PONG <serveur> <token>`                                                                                            |
| `PONG <serveur>`                                 | Réponse à un message `PING` envoyé par le serveur pour vérifier que la connexion est toujours active. | Aucune réponse nécessaire.                                                                                                  |
| `JOIN <canal>`                                   | Rejoint un canal IRC.                                                           | `:pseudo!utilisateur@hote JOIN :<canal>` et informations sur les utilisateurs du canal                                    |
| `PART <canal> :<message>`                        | Quitte un canal IRC.                                                            | `:pseudo!utilisateur@hote PART <canal> :<message>`                                                                          |
| `PRIVMSG <cible> :<message>`                     | Envoie un message privé à un utilisateur ou à un canal.                         | Le serveur transmet le message à la cible : `<cible>`.                                                                     |
| `NOTICE <cible> :<message>`                      | Envoie un message qui ne génère pas de réponse automatique (utilisé par exemple par un bot). | Le serveur transmet le message à la cible : `<cible>`.                                                                    |
| `QUIT :<message>`                                | Indique que le client quitte le serveur.                                        | `:pseudo!utilisateur@hote QUIT :<message>`                                                                                 |
| `MODE <cible> <flags>`                           | Change les modes d'un utilisateur ou d'un canal.                                | `:serveur MODE <cible> <flags>`                                                                                             |
| `WHO <masque>`                                   | Demande la liste des utilisateurs correspondant au masque.                      | Réponse sous forme de plusieurs lignes : `:serveur 352 <canal> <utilisateur> <hote> <serveur> <pseudo> H :<hopcount> <nom réel>` |
| `LIST [<canal>]`                                 | Liste les canaux existants (ou un canal spécifique).                            | `:serveur 322 <canal> <nombre_utilisateurs> :<sujet>` suivi de `:serveur 323 :Fin de /LIST`                                |
| `TOPIC <canal> :<sujet>`                         | Définit ou demande le sujet d'un canal.                                         | Si défini : `:pseudo!utilisateur@hote TOPIC <canal> :<sujet>` ; Si demandé : `:serveur 332 <canal> :<sujet>`                |

---

### **Explications supplémentaires**

1. **`CAP` (Capabilities)**  
   Cette commande est utilisée pour négocier des fonctionnalités avancées entre le client et le serveur. Vous pouvez l'ignorer ou la simplifier si vous ne supportez pas ces extensions.

2. **`NICK` et `USER`**  
   Ces deux commandes sont essentielles pour que le client soit identifié par le serveur. Elles doivent être gérées avant d'autoriser le client à interagir avec les autres utilisateurs ou canaux.

3. **Gestion des erreurs**  
   Si une commande n'est pas reconnue ou mal formée, le serveur doit répondre avec un code d'erreur comme :
   ```
   :serveur 421 <pseudo> <commande> :Commande inconnue
   ```

4. **Déconnexion (`QUIT`)**  
   Lorsqu'un client envoie un `QUIT`, informez les autres utilisateurs de sa déconnexion.

---

### **Documentation utile**
- **IRC Protocol Specification (RFC 1459)** : [RFC 1459](https://tools.ietf.org/html/rfc1459)
- **Modern IRC Protocol Documentation** : [Modern IRC Docs](https://modern.ircdocs.horse/)
- **IRCv3 Capabilities** : [IRCv3 Spec](https://ircv3.net/specs/core/capability-negotiation.html)
