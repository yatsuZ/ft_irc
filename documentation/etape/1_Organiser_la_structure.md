# 1 Organiser la structure

- [1 Organiser la structure](#1-organiser-la-structure)
	- [Objectif](#objectif)
	- [Fonctionement](#fonctionement)
	- [Comment faire](#comment-faire)
	- [Les prinipaux objet](#les-prinipaux-objet)
	- [Leur role](#leur-role)
	- [Comment ils interagisse entre eux](#comment-ils-interagisse-entre-eux)
	- [Ce qui sont capable de faire](#ce-qui-sont-capable-de-faire)

## Objectif

Ceci et la premiere etape du projet c'est de savoir comment organiser la structure du projet.
plus savoir comment sa marchera

## Fonctionement

De ce qu'on as compris pour lexecution du projet de cette maniere :
```bash
./ircserv <port> <password>
```
- port : Le numéro du port sur lequel votre serveur acceptera les connexions entrantes.
- password : Le mot de passe permettant de s’identifier auprès de votre serveur IRC, et qui devra être fourni par tout client IRC souhaitant s’y connecter

pour atctiver mais pour y acceder sa sera avec un service de client choisi (Nous avons choisi [Irssi](https://fr.wikipedia.org/wiki/Irssi)) cqr deja installer sur les pos de 42 et ce quon as vu assez simple dutilisation.

Donc maitnant c'est de savoir comment communiquer entre le serveur et le client et la structure dans le server.

documentation de [irssi](https://irssi.org/documentation/)

## Comment faire

Reflechir aux besoin et que devra faire notre serveur irc.
Reflechir aux different orbjet / class et leur methode et atrribut.

## Les prinipaux objet

Je dirais :
Le serveur
Les chanelle 
Les utilisateurs 
Les socket de comunication peut etre.

et c'est les principaux objet

## Leur role

## Comment ils interagisse entre eux

## Ce qui sont capable de faire 

a complter plus tard