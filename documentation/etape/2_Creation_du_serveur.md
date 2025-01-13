# 2. Création du serveur

Dans cette section, nous allons définir les fonctionnalités du serveur, son utilité et son fonctionnement. Nous détaillerons également les concepts clés comme les sockets et les fonctions utilisées pour implémenter le serveur.

## Table des matières

- [2. Création du serveur](#2-création-du-serveur)
  - [Table des matières](#table-des-matières)
  - [Objectif](#objectif)
    - [Qu'est-ce qu'un serveur](#quest-ce-quun-serveur)
    - [C'est quoi un socket](#cest-quoi-un-socket)
  - [Structure et rôle de la classe `Server`](#structure-et-rôle-de-la-classe-server)
    - [Brève description](#brève-description)
    - [Présentation du fichier `server.hpp`](#présentation-du-fichier-serverhpp)
    - [Constructeur Paramétré](#constructeur-paramétré)
    - [Définition de chaque Attribut](#définition-de-chaque-attribut)
    - [Paramétrage des Attributs](#paramétrage-des-attributs)
      - [**`_sock_addr_serv_in`** (type `sockaddr_in`)](#_sock_addr_serv_in-type-sockaddr_in)
      - [**Méthode `_bind_and_listen()`**](#méthode-_bind_and_listen)
      - [**`_all_pollfd`**](#_all_pollfd)
  - [Conclusion](#conclusion)


## Objectif

L'objectif de cette section est de :  
1. Définir ce qu'est un serveur et présenter les principaux outils nécessaires à sa création.  
2. Identifier les différents attributs essentiels pour construire un serveur et expliquer leur utilité.  
3. Montrer comment initialiser ces attributs afin de poser les bases du fonctionnement du serveur.  

### Qu'est-ce qu'un serveur  

Un serveur est une application ou un système informatique conçu pour répondre aux demandes d'autres programmes ou appareils, appelés *clients*.

Dans ce projet, le serveur sera implémenté sous forme d'une classe. Son rôle principal est de :  
1. Ouvrir une socket pour établir une communication avec les clients. (Voir [explication de la fonction socket](./../laboratoire/socket/info.md)).  
2. Écouter les connexions entrantes à l'aide de la fonction `listen`.  
3. Gérer les échanges de données à l'aide de fonctions comme `poll`, `epoll` et `send`.  

En résumé, le serveur agit comme un pont entre les clients et l'application principale, facilitant les échanges de données.  

### C'est quoi un socket  

Un *socket* est une interface permettant de communiquer entre deux machines sur un réseau. Il agit comme un canal d'échange de données.  

Pour créer un socket, il est nécessaire de spécifier :  
1. **Le domaine de communication** : par exemple, `AF_INET` pour utiliser le protocole IPv4.  
2. **Le type de socket** : par exemple, `SOCK_STREAM` pour une communication fiable basée sur le protocole TCP.  
3. **Le protocole** : souvent `0`, ce qui sélectionne automatiquement le protocole par défaut en fonction du type de socket choisi.  

Dans ce projet, ces paramètres seront utilisés pour établir une connexion stable entre le serveur et les clients.  

## Structure et rôle de la classe `Server`

### Brève description  
La classe `Server` est le cœur de notre application. Elle gère :  
- L'initialisation du serveur (attributs, sockets, paramètres réseau).  
- La configuration et l'écoute des connexions clients.  
- La gestion des échanges de données via des mécanismes comme `poll`.  

Elle encapsule toutes les fonctionnalités nécessaires pour établir une communication fiable et efficace entre le serveur et les clients.  

### Présentation du fichier `server.hpp`  
Le fichier `server.hpp` contient la définition de la classe `Server`, ses attributs, ses méthodes, et une exception personnalisée pour gérer les erreurs d'initialisation.  

Voici le contenu du fichier :  

```hpp
#define ADDRESSE_IP_IN "127.0.0.1"
#define REUSEADDR_OPTION 1
#define BUFFER_SIZE 1024
#define MAX_EVENTS 10


/// @brief Exception pour toutes erreurs provenant soit de l'initialisation de la classe Serveur ou provenant de la méthode Exec
class Init_serv_error : public std::exception
{
	private:
		const std::string	_msg;
	public :
		Init_serv_error(std::string msg): _msg(msg)
		{}
		virtual ~Init_serv_error() throw() {}
		virtual const char* what(void) const throw()
		{
			return (this->_msg.c_str());
		}
};

/// @brief Class Serveur : la classe principale qui gère tout, y compris la gestion des connexions et des échanges de données.
class Server
{
private:

	const std::string			_name;				// Nom du serveur
	const uint16_t 				_port;				// Port d'écoute du serveur
	const std::string			_mot_de_passe;		// Mot de passe du serveur IRC
	const int					_socketfd;			// Le descripteur de la socket
	sockaddr_in					_sock_addr_serv_in;	// Adresse de la socket du serveur
	std::vector<struct pollfd> 	_all_pollfd;				// Vecteur de pollfd pour gérer plusieurs connexions

	uint16_t 		_is_a_legit_port(std::string &argv1);
	std::string		_is_a_legit_mdp(std::string &argv2);
	int				_init_socket(void);
	void 			_bind_and_listen(void);
	void			_throw_except(const std::string &msg);
	void			_paramPoll(void);
	Server();

public:
	Server(std::string argv1, std::string argv2);
	~Server();

	std::string					get_name(void) const {return _name;}
	std::string					get_mdp(void) const {return _mot_de_passe;}
	uint16_t 					get_port(void) const{return _port;}
	int							get_socketfd(void) const{return _socketfd;}
	sockaddr_in					get_socke_addr_serv(void) const{return _sock_addr_serv_in;}
	std::vector<struct pollfd>	get_pollfds(void) const {return this->_all_pollfd;}

	void	exec(void);
};

/// @brief Affiche tout les attributs de tout les pollfd du vecteur
std::ostream & operator<<(std::ostream &o, std::vector<struct pollfd> const &pollfds);
/// @brief Affiche tout les attributs de la class serveur
std::ostream & operator<<( std::ostream & o, Server const & serv);
```

Le programme peut être résumé en deux grandes parties :

1. **Initialisation** (grâce au constructeur paramétré)
2. **Exécution** (grâce à la méthode `exec`, qui constitue le cœur du programme)

### Constructeur Paramétré

Le constructeur paramétré a pour but d'initialiser les attributs de la classe et de configurer les éléments essentiels comme le port, la socket et les descripteurs de fichiers (fd). En cas de problème lors de l'initialisation ou de la configuration, le programme s'arrête pour éviter des erreurs à l'exécution.

Voici le constructeur paramétré :

```cpp
Server::Server(std::string argv1, std::string argv2):
_name("Nom du Serveur"),						// Initialisation du nom du serveur
_port(this->_is_a_legit_port(argv1)),			// Initialisation du port
_mot_de_passe(this->_is_a_legit_mdp(argv2)),	// Initialisation du mot de passe
_socketfd(this->_init_socket())					// Initialisation du descripteur de fichier de la socket
{
	// Paramétrage de l'adresse de la socket d'entrée du serveur
	this->_sock_addr_serv_in.sin_family = AF_INET;
	this->_sock_addr_serv_in.sin_addr.s_addr = inet_addr(ADDRESSE_IP_IN);
	this->_sock_addr_serv_in.sin_port = htons(this->get_port()); // Port en format réseau (big-endian)

	// Paramétrage du port et de la socket
	this->_bind_and_listen();

	// Initialisation et paramétrage de `poll`
	this->_paramPoll();
	
	std::cout << getColorCode(GREEN) << "Construction terminée" << getColorCode(NOCOLOR) << std::endl;
}
```

### Définition de chaque Attribut

>> Pour voir le code exact de chaque méthode, référez-vous au fichier : [Serveur.cpp](./../../code/class/Server/Server.cpp)

- **`_name`** : Cet attribut est simple à définir, il s'agit simplement d'une chaîne de caractères constante représentant le nom du serveur.

- **`_port`** : L'attribut `_port` est défini grâce à la méthode suivante :
  
  ```cpp
  /// @brief Vérifie que `argv1` est un port valide et retourne sa valeur en `uint16_t`. Si ce n'est pas un port valide, une exception est lancée. Un bon port est compris entre 1 et 65535.
  /// @param argv1 Le premier argument qui est un port sous forme de chaîne de caractères.
  /// @return `uint16_t` Le port extrait de `argv1`.
  uint16_t Server::_is_a_legit_port(std::string &argv1);
  ```

  Cette méthode prend en entrée une chaîne de caractères et vérifie si elle représente un nombre valide compris entre 1 et 65535, ce qui correspond à la plage de ports légitimes. Si ce n'est pas le cas, une exception est levée.

- **`_mot_de_passe`** : Cet attribut est défini grâce à la méthode suivante :

  ```cpp
  /// @brief Vérifie que le deuxième argument est un mot de passe valide. Un bon mot de passe ne doit contenir que des caractères alphanumériques sans séparateurs.
  /// @param argv2 Le deuxième argument, censé être le mot de passe.
  /// @return Le mot de passe sous forme de chaîne de caractères.
  std::string Server::_is_a_legit_mdp(std::string &argv2);
  ```

  Cette méthode vérifie que le mot de passe passé en argument ne contient que des caractères alphanumériques. Si ce n'est pas le cas, une exception peut être levée pour signaler une erreur.

- **`_socketfd`** : L'attribut `_socketfd` est défini grâce à la méthode suivante :

  ```cpp
  /// @brief Initialise le descripteur de fichier de la socket.
  /// @return Le descripteur de fichier de la socket.
  int Server::_init_socket()
  {
      int socketfd = socket(AF_INET, SOCK_STREAM, 0);
      if (socketfd < 0)
          _throw_except("Erreur lors de la création du socket");
      return socketfd;
  }
  ```

  Cette méthode crée une socket de type `SOCK_STREAM` (c'est-à-dire un flux de données TCP) avec la famille d'adresses `AF_INET` (IPv4). Si la création de la socket échoue (si le descripteur de fichier est inférieur à zéro), une exception est levée. Sinon, elle retourne le descripteur de fichier de la socket.

  **Explication de la fonction `socket()`** :
  La fonction `socket()` est utilisée pour créer une nouvelle socket. Elle prend trois paramètres :
  - **`AF_INET`** : spécifie que la socket est utilisée pour des communications réseau en IPv4.
  - **`SOCK_STREAM`** : indique que la socket est de type TCP, ce qui permet une communication fiable et ordonnée entre les hôtes.
  - **`0`** : spécifie le protocole à utiliser. En l'absence de spécification, le système choisit le protocole par défaut pour le type de socket (TCP dans ce cas).
  
  Si la création de la socket échoue, la fonction retourne une valeur négative, ce qui entraîne le lancement d'une exception pour signaler l'erreur.

### Paramétrage des Attributs

Dans le code, certains attributs sont initialisés automatiquement grâce aux mécanismes internes de C++, mais il est important de les configurer correctement. C'est le cas pour les attributs `_sock_addr_serv_in` et `_all_pollfd`.

#### **`_sock_addr_serv_in`** (type `sockaddr_in`)

Cet attribut est un objet de type `sockaddr_in`, qui est une structure utilisée pour stocker l'adresse et le port d'une socket en IPv4. Voici comment il est configuré dans le constructeur :

```cpp
// Paramétrage de l'adresse de la socket d'entrée du serveur
this->_sock_addr_serv_in.sin_family = AF_INET; // Indique que la famille d'adresses est IPv4
this->_sock_addr_serv_in.sin_addr.s_addr = inet_addr(ADDRESSE_IP_IN); // Adresse IP du serveur (ici "127.0.0.1")
this->_sock_addr_serv_in.sin_port = htons(this->get_port()); // Port en format réseau (big-endian)
```

- **`sin_family`** : Ce champ définit la famille d'adresses. `AF_INET` signifie qu'on utilise IPv4.
- **`sin_addr.s_addr`** : Ce champ stocke l'adresse IP du serveur. Ici, `inet_addr(ADDRESSE_IP_IN)` convertit l'adresse IP de type chaîne de caractères (par exemple, `"127.0.0.1"`) en format binaire.
- **`sin_port`** : Ce champ contient le numéro de port sur lequel le serveur va écouter. La fonction `htons()` convertit le port en format réseau (big-endian).

Ce paramétrage permet à la socket de se lier à une adresse IP et à un port spécifiques, et d'écouter les connexions entrantes.

#### **Méthode `_bind_and_listen()`**

Cette méthode configure la socket pour accepter les connexions entrantes et les gérer de manière appropriée. Voici le contenu de la méthode et son explication :

```cpp
/// @brief Configure le port et les sockets
void Server::_bind_and_listen()
{
    const sockaddr *sock_addr_serv_in_ptr = reinterpret_cast<const sockaddr *>(&this->_sock_addr_serv_in);

    // Configure l'option SO_REUSEADDR
    int opt = REUSEADDR_OPTION;
    // Cela permet de dire que le port peut être désactivé rapidement et réutilisé
    if (setsockopt(this->_socketfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
        _throw_except("Erreur lors de la configuration de SO_REUSEADDR.");

    // Configure la socket en mode non-bloquant
    if (fcntl(this->_socketfd, F_SETFL, O_NONBLOCK) < 0)
        _throw_except("Erreur lors de la mise en mode non-bloquant de la socket.");

    // Associe la socket fd à la structure de sockaddr_in
    if (bind(this->_socketfd, sock_addr_serv_in_ptr, sizeof(this->_sock_addr_serv_in)) < 0)
        _throw_except("Erreur lors de l'association de l'adresse à la socket.");
    std::cout << "Adresse associée à la socket avec succès." << std::endl;

    // Indique au fd d'écouter l'entrée sur le port
    if (listen(this->_socketfd, SOMAXCONN) < 0)
        _throw_except("Erreur lors de la mise en écoute de la socket.");
    std::cout << "Socket en écoute sur le port " << this->get_port() << "." << std::endl;
}
```

**Explication détaillée :**

1. **Option `SO_REUSEADDR`** :  
   Cette option permet à la socket de réutiliser une adresse de manière plus rapide. Elle est utile lorsque le serveur est redémarré et que le port qu'il utilise est encore marqué comme "occupé" par le système. En activant `SO_REUSEADDR`, on permet au serveur de récupérer rapidement ce port sans attendre qu'il soit libéré par le système.

   - **`setsockopt()`** : Cette fonction permet de configurer les options de la socket. Si l'option `SO_REUSEADDR` ne peut pas être appliquée, une exception est levée.

2. **Mode non-bloquant** :  
   La fonction `fcntl()` est utilisée pour mettre la socket en mode non-bloquant. Cela signifie que les opérations sur la socket (comme `accept()`) ne bloqueront pas l'exécution du programme. Cela permet au serveur de continuer à exécuter d'autres tâches sans attendre indéfiniment qu'une connexion arrive.

   - **`O_NONBLOCK`** : Ce drapeau indique que les opérations de la socket doivent être non-bloquantes.

3. **Association de la socket à une adresse (`bind()`)** :  
   La fonction `bind()` lie la socket à une adresse spécifique (ici, l'adresse IP et le port définis dans `_sock_addr_serv_in`). Cela permet à la socket d'écouter sur un port spécifique pour les connexions entrantes.

   - Si cette opération échoue, une exception est levée avec le message "Erreur lors de l'association de l'adresse à la socket".

4. **Mise en écoute (`listen()`)** :  
   Une fois que la socket est correctement liée à une adresse, la fonction `listen()` indique au système que la socket doit écouter les connexions entrantes. La deuxième valeur (`SOMAXCONN`) spécifie le nombre maximal de connexions en attente dans la file d'attente. Si cette opération échoue, une exception est levée.

   - **`SOMAXCONN`** : Cette constante définit la taille maximale de la file d'attente pour les connexions en attente.

#### **`_all_pollfd`**

L'attribut `_all_pollfd` est utilisé pour gérer les descripteurs de fichiers dans le cadre de la gestion des connexions multiples via des mécanismes de *polling*. Cependant, la configuration et le choix de la méthode de *polling* (telles que `poll()`, `select()`, ou `epoll()`) nécessitent une discussion plus approfondie sur leur fonctionnement et leurs avantages respectifs. Nous aborderons ces aspects dans un fichier ultérieur, car l'objectif ici est de se concentrer sur l'initialisation des attributs et des paramètres du serveur. 

## Conclusion

Dans ce fichier, nous avons exploré les principales utilités du serveur, ainsi que l'initialisation de ses attributs. Nous avons détaillé le rôle de chaque attribut et expliqué comment ils sont configurés lors de la création du serveur. 

Dans le prochain fichier Markdown, nous approfondirons l'utilisation de ces attributs pour mettre en place le programme d'écoute du serveur. Nous discuterons également des différentes options de gestion des descripteurs de fichiers, en comparant `poll` et `epoll`, leurs avantages, inconvénients, ainsi que d'autres alternatives possibles.
