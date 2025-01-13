# 3. Le cœur du programme

Dans cette section, nous explorons le concept de **poll** et ses variantes, les méthodes pour choisir l'outil adapté, leur configuration, ainsi que le fonctionnement détaillé de la méthode `exec()`.

## Table des matières

- [3. Le cœur du programme](#3-le-cœur-du-programme)
	- [Table des matières](#table-des-matières)
	- [Objectif](#objectif)
	- [Outils de multiplexage d'I/O](#outils-de-multiplexage-dio)
		- [Problématique](#problématique)
		- [Définition et utilité](#définition-et-utilité)
		- [Pourquoi utiliser le multiplexage d'I/O ?](#pourquoi-utiliser-le-multiplexage-dio-)
		- [Exemple concret](#exemple-concret)
		- [Comparaison des outils](#comparaison-des-outils)
	- [La méthode `exec()`](#la-méthode-exec)
		- [Initialisation avec `_paramPoll()`](#initialisation-avec-_parampoll)
		- [Fonctionnement de `exec()`](#fonctionnement-de-exec)
	- [Explications et tests](#explications-et-tests)
		- [Explications](#explications)
		- [Tester le programme](#tester-le-programme)
		- [Alternatives envisagées](#alternatives-envisagées)

---

## Objectif

- Présenter les outils de multiplexage d'I/O (**poll**, **epoll**, etc.), leurs caractéristiques, avantages et inconvénients.
- Décrire leur rôle dans le programme, notamment au sein de la méthode `exec()`.
- Expliquer pourquoi `poll` a été choisi pour ce projet.

---

## Outils de multiplexage d'I/O

### Problématique

Lorsqu'un programme doit gérer plusieurs connexions simultanément (par exemple, un serveur web ou une application de chat), créer un thread ou un processus par connexion est inefficace. Cela consomme beaucoup de ressources et limite la scalabilité.

Les outils de multiplexage d'I/O permettent de surveiller plusieurs descripteurs de fichiers (sockets, fichiers, pipes, etc.) dans une seule opération, rendant le programme plus performant.

### Définition et utilité

1. **Multiplexage** :
   - Gérer plusieurs descripteurs simultanément.
   - Identifier lesquels sont prêts pour une opération d'entrée ou de sortie.

2. **I/O (Input/Output)** :
   - Opérations de lecture et d'écriture.
   - Exemples :
     - Lecture depuis une socket réseau.
     - Écriture dans un fichier.
     - Communication via un pipe.

### Pourquoi utiliser le multiplexage d'I/O ?

Le multiplexage d'I/O résout plusieurs problèmes :
- Empêche le blocage du programme sur des descripteurs non prêts.
- Réduit le nombre de threads/processus nécessaires.
- Améliore la gestion des ressources pour les applications à grande échelle.

### Exemple concret

Un serveur web gérant 1000 connexions simultanées :
- **Sans multiplexage** :
  - 1000 threads ou processus sont créés, chacun bloqué en attente de données.
  - Consommation excessive de mémoire et CPU.
- **Avec multiplexage** :
  - Une seule boucle surveille les 1000 connexions.
  - Le serveur agit uniquement lorsque des connexions sont prêtes (lecture/écriture).

### Comparaison des outils

| Outil       | Description                         | Avantages                                   | Inconvénients                            | Compatibilité           |
|-------------|-------------------------------------|---------------------------------------------|------------------------------------------|-------------------------|
| **`select`** | Premier outil historique           | Simple, très compatible                     | Limité à 1024 descripteurs, inefficace   | Tous les systèmes Unix  |
| **`poll`**   | Amélioration de `select`           | Gère plus de descripteurs, syntaxe simple   | Moins performant pour un grand nombre    | Tous les systèmes Unix  |
| **`epoll`**  | Spécifique à Linux, très performant| Scalabilité, supporte des millions de connexions | Syntaxe plus complexe, Linux uniquement | Linux                  |
| **`kqueue`** | Alternative sur BSD/macOS          | Très performant, comparable à `epoll`      | Non disponible sur Linux                 | BSD, macOS             |
| **`io_uring`** | Outil récent sur Linux            | Performances avancées, support moderne     | Nécessite un noyau récent, adoption lente| Linux (noyau récent)   |

> **Note** : `poll` a été choisi pour ce projet car il est compatible avec la majorité des systèmes Unix et répond aux exigences du sujet.

---

## La méthode `exec()`

### Initialisation avec `_paramPoll()`

La méthode `_paramPoll()` configure le descripteur du serveur pour surveiller les connexions entrantes. Les descripteurs sont stockés dans un vecteur pour une gestion dynamique.

```cpp
void Server::_paramPoll(void)
{
    struct pollfd server_pollfd;
    server_pollfd.fd = _socketfd; // Descripteur de la socket du serveur
    server_pollfd.events = POLLIN; // Surveiller les événements de lecture
    server_pollfd.revents = 0;
    _all_pollfd.push_back(server_pollfd);
}
```

### Fonctionnement de `exec()`

La méthode `exec()` est le cœur du programme. Elle surveille les événements réseau et gère les connexions entrantes, les échanges de messages et les déconnexions.

```cpp
void Server::exec(void)
{
    Action action_a_faire = NOACTION;
    pollfd current_pollfd;

    while (true)
    {
        int ret = poll(_all_pollfd.data(), _all_pollfd.size(), 5); // Surveiller les événements
        if (ret < 0)
            throw std::runtime_error("Erreur de la fonction poll()");

        if (_all_pollfd[0].revents & POLLIN)
            connect(); // Nouvelle connexion

        for (size_t i = 1; i < _all_pollfd.size(); i++)
        {
            current_pollfd = _all_pollfd[i];

            if (current_pollfd.revents & POLLIN)
            {
                char buffer[1];
                ssize_t check = recv(current_pollfd.fd, buffer, sizeof(buffer), MSG_PEEK | MSG_DONTWAIT);

                if (check == 0)
                    disconnect(i--, current_pollfd); // Déconnexion
                else
                    action_a_faire = link(current_pollfd); // Échange de messages
            }

            if (action_a_faire == SHUTDOWN)
                return;
        }
    }
}
```

---

## Explications et tests

### Explications

- `exec()` utilise `poll` pour surveiller les descripteurs.
- Les événements détectés déclenchent des actions spécifiques :
  - **Connexion** : Ajouter un nouveau client à la liste.
  - **Déconnexion** : Retirer le client de la liste et fermer le descripteur.
  - **Échange** : Transférer des messages entre clients.

### Tester le programme

1. Lancer le serveur.
2. Depuis un autre terminal ou machine sur le même réseau :
   ```bash
   nc <ip_du_serveur> <port>
   ```
3. Envoyer des messages et observer leur retransmission.

### Alternatives envisagées

- **Utilisation de `epoll`** :
  - Plus performant pour un grand nombre de connexions.
  - Limité à Linux.
- **Approche avec `kqueue`** :
  - Idéal pour macOS et BSD.
  - Non compatible avec Linux.
