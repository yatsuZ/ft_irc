# Le client irssi  
- [Le client irssi](#le-client-irssi)
	- [Objectif](#objectif)
	- [C'est quoi](#cest-quoi)
		- [Caractéristiques principales :](#caractéristiques-principales-)
	- [Comment l'installer](#comment-linstaller)
		- [Sous Linux (Debian/Ubuntu)](#sous-linux-debianubuntu)
		- [Sous Alpine Linux](#sous-alpine-linux)
		- [Sous macOS (via Homebrew)](#sous-macos-via-homebrew)
		- [Sous Windows (via WSL)](#sous-windows-via-wsl)
	- [Comment l'utiliser ?](#comment-lutiliser-)
		- [Lancer irssi](#lancer-irssi)
		- [Se connecter à un serveur IRC](#se-connecter-à-un-serveur-irc)
		- [Rejoindre un canal](#rejoindre-un-canal)
		- [Envoyer un message](#envoyer-un-message)
		- [Commandes utiles](#commandes-utiles)

## Objectif  

Ce document a pour but de présenter le client **irssi**, d'expliquer son utilité, et de montrer comment l'utiliser pour tester notre projet de serveur IRC.  

---

## C'est quoi

**irssi** est un client IRC (Internet Relay Chat) open source et en ligne de commande. Il est particulièrement apprécié pour sa légèreté, sa simplicité et sa flexibilité.  

### Caractéristiques principales :  
- Fonctionne dans un terminal, ce qui le rend léger et rapide.  
- Compatible avec la plupart des serveurs IRC, y compris ceux que nous développerons.  
- Extensible grâce à des scripts (en Perl ou d'autres langages).  
- Disponible sur la majorité des distributions Linux ainsi que sous macOS et Windows via des émulateurs comme WSL ou Cygwin.  

Pour notre projet, irssi servira à interagir avec le serveur que nous développons.  

---

## Comment l'installer  

### Sous Linux (Debian/Ubuntu)  
```bash  
sudo apt update  
sudo apt install irssi  
```  

### Sous Alpine Linux  
```bash  
apk add irssi  
```  

### Sous macOS (via Homebrew)  
```bash  
brew install irssi  
```  

### Sous Windows (via WSL)  
1. Installez WSL avec une distribution Linux (Ubuntu, par exemple).  
2. Dans le terminal WSL :  
   ```bash  
   sudo apt update  
   sudo apt install irssi  
   ```  

Pour plus de détails, consultez la documentation officielle d'irssi : [irssi.org](https://irssi.org).  

---

## Comment l'utiliser ?  

Une fois **irssi** installé, suivez ces étapes pour l'utiliser :  

### Lancer irssi  
Dans un terminal :  
```bash  
irssi  
```  

### Se connecter à un serveur IRC  
Pour se connecter au serveur que vous développez :  
```bash  
/connect <adresse_du_serveur> <port>  
```  
Exemple :  
```bash  
/connect localhost 6667  
```  

### Rejoindre un canal  
Une fois connecté au serveur, tapez :  
```bash  
/join #canal  
```  
Exemple :  
```bash  
/join #general  
```  

### Envoyer un message  
Pour envoyer un message dans le canal :  
```  
<votre_message>  
```  

### Commandes utiles  
| Commande            | Description                                  |  
|---------------------|----------------------------------------------|  
| `/quit`             | Quitter le client IRC.                      |  
| `/msg <user> <msg>` | Envoyer un message privé à un utilisateur.  |  
| `/who`              | Afficher la liste des utilisateurs connectés.|  

Pour tester les fonctionnalités de votre serveur, essayez de vous connecter, de créer un canal, d'y inviter des utilisateurs et d'envoyer des messages.  
