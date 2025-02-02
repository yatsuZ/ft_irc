# 4. Irssi

## Table des matières

- [4. Irssi](#4-irssi)
	- [Table des matières](#table-des-matières)
	- [Contexte](#contexte)
	- [Objectif](#objectif)
	- [Fonctionnement de Irssi](#fonctionnement-de-irssi)
	- [Protocole IRC](#protocole-irc)
		- [Références importantes :](#références-importantes-)
	- [Tableau des commandes que le serveur interprète](#tableau-des-commandes-que-le-serveur-interprète)

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

## Tableau des commandes que le serveur interprète

| Nom de la commande | Arguments nécessaires | Ce que ça fait | Liens vers sa documentation |
|--------------------|----------------------|----------------|----------------------------|
| `CAP`              | [commande]           | Permet de négocier des capacités supplémentaires avec le serveur, comme la prise en charge de certaines extensions IRC. | [IRC CAP Command](https://ircv3.net/specs/capability-negotiation-3.1.html) |
| `NICK`             | [nouveau-nom]        | Permet de définir ou de changer le pseudonyme de l'utilisateur. Si le pseudonyme est déjà pris, le serveur répondra par une erreur. | [IRC NICK Command](https://tools.ietf.org/html/rfc1459#section-2.3) |
| `USER`             | [username] [hostname] [server] [realname] | Permet à l'utilisateur de s'identifier auprès du serveur IRC. L'argument `realname` est souvent utilisé pour donner un nom ou une description supplémentaire. | [IRC USER Command](https://tools.ietf.org/html/rfc1459#section-2.4) |
| `PASS`             | [mot-de-passe]       | Permet à l'utilisateur de se connecter avec un mot de passe si le serveur nécessite une authentification. | [IRC PASS Command](https://tools.ietf.org/html/rfc1459#section-2.5) |
| `JOIN`             | [canal] [mots-de-passe] | Permet à l'utilisateur de rejoindre un canal. Le serveur doit répondre par un message indiquant que l'utilisateur a rejoint le canal. | [IRC JOIN Command](https://tools.ietf.org/html/rfc1459#section-2.5) |
| `PART`             | [canal]              | Permet à l'utilisateur de quitter un canal. Le serveur répondra en annonçant que l'utilisateur a quitté le canal. | [IRC PART Command](https://tools.ietf.org/html/rfc1459#section-2.6) |
| `PRIVMSG`          | [destinataire] [message] | Envoie un message privé à un utilisateur ou à un canal. Le serveur transmet ce message aux autres utilisateurs du canal ou à la personne spécifiée. | [IRC PRIVMSG Command](https://tools.ietf.org/html/rfc1459#section-2.3) |
| `PONG`             | [serveur]            | Réponse à un message `PING` envoyé par le serveur pour vérifier que la connexion est toujours active. Le client doit répondre par `PONG` pour maintenir la connexion. | [IRC PONG Command](https://tools.ietf.org/html/rfc1459#section-2.9) |
| `QUIT`             | [message]            | Permet à l'utilisateur de se déconnecter du serveur IRC. Le serveur répondra en annonçant que l'utilisateur a quitté le serveur. | [IRC QUIT Command](https://tools.ietf.org/html/rfc1459#section-2.7) |


