# 3. Le cœur du programme  

Dans cette section, nous allons expliquer ce qu'est **poll** et ses variantes, comment choisir la méthode adaptée, comment les configurer, et détailler la méthode `exec()`.  

## Table des matières  

- [3. Le cœur du programme](#3-le-cœur-du-programme)
	- [Table des matières](#table-des-matières)
	- [Objectif](#objectif)
	- [Outils de multiplexage d'I/O](#outils-de-multiplexage-dio)
		- [Problématique](#problématique)
		- [Définition, utilité et caractéristiques](#définition-utilité-et-caractéristiques)
		- [Pourquoi le multiplexage d'I/O est utile ?](#pourquoi-le-multiplexage-dio-est-utile-)
		- [Exemple concret](#exemple-concret)
		- [Les différents outils](#les-différents-outils)
	- [La méthode `exec()`](#la-méthode-exec)
	- [Code source de `_paramPoll()` et `exec()`](#code-source-de-_parampoll-et-exec)
		- [Fonctionnement de `_paramPoll()`](#fonctionnement-de-_parampoll)
		- [Fonctionnement de `exec()`](#fonctionnement-de-exec)
	- [Tester](#tester)
		- [Alternatives envisagées](#alternatives-envisagées)
	- [Références](#références)

---

## Objectif  

- Expliquer ce qu'est un **outil de multiplexage d'I/O**, ses variantes, et pourquoi ils sont nécessaires.  
- Présenter les différents outils de multiplexage d'I/O (**poll**, **epoll**, etc.), leurs points forts et leurs faiblesses.  
- Décrire comment l'outil choisi est utilisé dans la méthode `exec()` et pourquoi il a été sélectionné.  

---

## Outils de multiplexage d'I/O  

### Problématique  

Lorsqu'un programme doit gérer de multiples connexions simultanément (ex. serveur web, chat), il est inefficace de créer un thread ou un processus par connexion. Cela consomme trop de ressources et limite la scalabilité.  

Les **outils de multiplexage d'I/O** permettent de surveiller plusieurs descripteurs de fichiers (sockets, fichiers, pipes, etc.) en une seule opération, rendant le programme plus efficace.  

---

### Définition, utilité et caractéristiques  

1. **Multiplexage**  
   - Signifie "gérer plusieurs choses en parallèle".  
   - Ici, cela désigne la capacité à surveiller plusieurs descripteurs d'I/O pour détecter ceux qui sont prêts (lecture, écriture, erreurs).  

2. **I/O (Input/Output)**  
   - Représente toutes les opérations d'entrée (lecture) et de sortie (écriture).  
   - Exemples :  
     - Lecture d'une socket réseau.  
     - Écriture dans un fichier.  
     - Communication entre processus via un pipe.  

---

### Pourquoi le multiplexage d'I/O est utile ?  

Le multiplexage d'I/O résout les problèmes suivants :  
- Éviter le blocage du programme sur des descripteurs non prêts.  
- Réduire le nombre de threads/processus nécessaires pour gérer plusieurs connexions.  
- Optimiser la gestion des ressources pour des applications à grande échelle.  

---

### Exemple concret  

Imaginez un serveur web gérant 1000 connexions simultanées :  
- **Sans multiplexage** :  
  - 1000 threads ou processus, chacun bloqué en attendant des données.  
  - Très coûteux en mémoire et CPU.  
- **Avec multiplexage** :  
  - Une seule boucle surveille les 1000 connexions.  
  - Le serveur agit uniquement quand une connexion est prête (lecture/écriture).  

---

### Les différents outils  

Voici un tableau comparatif des principaux outils de multiplexage d'I/O :  

| Outil       | Description                         | Avantages                                   | Inconvénients                            | Compatibilité           |  
|-------------|-------------------------------------|---------------------------------------------|------------------------------------------|-------------------------|  
| **`select`** | Premier outil historique           | Simple à utiliser, très compatible          | Limité à 1024 descripteurs, inefficace   | Tous les systèmes Unix  |  
| **`poll`**   | Amélioration de `select`           | Gère plus de descripteurs, syntaxe simple   | Moins performant pour un grand nombre    | Tous les systèmes Unix  |  
| **`epoll`**  | Spécifique à Linux, très performant| Scalabilité, supporte des millions de connexions | Syntaxe plus complexe, Linux uniquement | Linux                  |  
| **`kqueue`** | Alternative sur BSD/macOS          | Très performant, comparable à `epoll`      | Non disponible sur Linux                 | BSD, macOS             |  
| **`io_uring`** | Outil récent sur Linux            | Performances avancées, support moderne     | Nécessite un noyau récent, adoption lente| Linux (noyau récent)   |  

> **Note** : Pour ce projet, nous avons choisi `poll` car il est le mécanisme par défaut proposé dans le sujet. Cependant, nous avons envisagé d'utiliser `epoll` pour ses meilleures performances.  

---

## La méthode `exec()`  

Dans cette section, nous détaillons la méthode `exec()` utilisée dans le programme, ainsi que son rôle et son fonctionnement. Nous abordons également la méthode `_paramPoll()`.  

---

## Code source de `_paramPoll()` et `exec()`  

### Fonctionnement de `_paramPoll()`  

La méthode `_paramPoll()` initialise le premier descripteur, dédié au serveur, en paramétrant les événements à surveiller.  

Nous utilisons un **vecteur** pour stocker les structures `pollfd`, car il permet de gérer dynamiquement plusieurs descripteurs de clients connectés. La taille du vecteur peut être ajustée à tout moment, et il offre un accès facile aux informations de chaque descripteur.  

```cpp
void	Server::_paramPoll(void)
{
	// Structure pour poll
	struct pollfd server_pollfd;

	server_pollfd.fd = _socketfd;	// La socket du serveur
	server_pollfd.events = POLLIN;	// On surveille les événements de lecture (connexion entrante)
	server_pollfd.revents = 0;
	_fds.push_back(server_pollfd);
}
```

---

### Fonctionnement de `exec()`  

Une fois les attributs nécessaires configurés, la méthode `exec()` démarre une boucle infinie pour surveiller les événements réseau.  

```cpp
/// @brief Méthode qui est le cœur du programme
void	Server::exec(void)
{
	std::cout << getColorCode(YELLOW) << "Exécution du Serveur ..." << getColorCode(NOCOLOR) << std::endl;

	// Boucle principale
	while (true)
	{
		// Poll pour attendre un événement
		int ret = poll(this->_fds.data(), _fds.size(), -1); // Attente infinie pour des événements
		if (ret < 0)
			this->_throw_except("Erreur de la fonction poll()");
		// Vérification si la socket serveur est prête à accepter une connexion
		if (this->_fds[0].revents & POLLIN)
		{
			sockaddr_in client_addr;
			socklen_t client_len = sizeof(client_addr);
			int client_fd = accept(_socketfd, (struct sockaddr*)&client_addr, &client_len);
			if (client_fd < 0)
			{
				std::cerr << getColorCode(RED) << "Erreur d'acceptation de la connexion" << getColorCode(NOCOLOR) << std::endl;
				continue;
			}
			std::cout << getColorCode(GREEN) << "Connexion acceptée!" << getColorCode(NOCOLOR) << std::endl;
			close(client_fd);
		}
	}
	std::cout << getColorCode(YELLOW) << "Fin du Serveur" << getColorCode(NOCOLOR) << std::endl;
}
```

## Tester 


---

### Alternatives envisagées  

- **Approche avec `epoll`** :  
  Une branche expérimentale nommée `test_avec_epoll` implémente une version similaire avec `epoll`, qui est plus performant pour un grand nombre de connexions.  

- **Choix final** :  
  Nous avons retenu `poll` pour sa simplicité et sa compatibilité avec le sujet du projet.  

---

## Références  

1. [Page de manuel de `poll`](https://man7.org/linux/man-pages/man2/poll.2.html)  
2. [Page de manuel de `epoll`](https://man7.org/linux/man-pages/man7/epoll.7.html)  
3. [Guide sur le multiplexage d'E/S asynchrone par Julia Evans](https://jvns.ca/blog/2017/06/03/async-io-on-linux--select--poll--and-epoll/)  
4. [Tutoriel vidéo : Introduction à `select`, `poll`, et `epoll` sur Linux (YouTube)](https://www.youtube.com/watch?v=dEHZb9JsmOU)  
5. Documentation interne du projet.  

