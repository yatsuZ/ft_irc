# Utilisation de la fonction `poll` en C++98

## Description

La fonction `poll` est utilisée pour surveiller plusieurs descripteurs de fichiers afin de voir si l'un d'entre eux est prêt pour une opération d'E/S (lecture, écriture, ou des événements exceptionnels). Elle est souvent utilisée pour implémenter des serveurs qui doivent gérer plusieurs connexions réseau simultanément.

## Syntaxe

```c
#include <poll.h>

int poll(struct pollfd *fds, nfds_t nfds, int timeout);
```

## Paramètres

- `struct pollfd *fds` : Un tableau de structures `pollfd` décrivant les descripteurs de fichiers à surveiller et les événements d'intérêt.
- `nfds_t nfds` : Le nombre d'éléments dans le tableau `fds`.
- `int timeout` : La durée d'attente en millisecondes. Les valeurs possibles sont :
  - `timeout > 0` : La fonction attend jusqu'à ce que l'un des descripteurs soit prêt ou que le délai soit écoulé.
  - `timeout == 0` : La fonction retourne immédiatement après avoir vérifié les descripteurs.
  - `timeout < 0` : La fonction attend indéfiniment jusqu'à ce qu'un descripteur soit prêt.

## Retour

- La fonction retourne le nombre de descripteurs prêts pour une opération d'E/S.
- Si la fonction échoue, elle retourne `-1` et définit `errno` pour indiquer l'erreur.
- Si le délai d'attente est écoulé et qu'aucun descripteur n'est prêt, elle retourne `0`.

## Structure `pollfd`

La structure `pollfd` est utilisée pour décrire les descripteurs de fichiers à surveiller et les événements d'intérêt.

```c
struct pollfd {
    int fd;         // Descripteur de fichier à surveiller
    short events;   // Événements à surveiller
    short revents;  // Événements qui se sont produits
};
```

### Membres de `pollfd`

- `int fd` : Le descripteur de fichier à surveiller. Si `fd` est négatif, l'entrée est ignorée.
- `short events` : Un masque des événements à surveiller. Les valeurs possibles sont :
  - `POLLIN` : Données disponibles en lecture.
  - `POLLOUT` : Prêt pour l'écriture.
  - `POLLPRI` : Données urgentes disponibles en lecture.
- `short revents` : Un masque des événements qui se sont effectivement produits. Les valeurs possibles incluent tous ceux de `events` ainsi que :
  - `POLLERR` : Erreur sur le descripteur de fichier.
  - `POLLHUP` : Suspension du descripteur de fichier.
  - `POLLNVAL` : Descripteur de fichier non valide.

## Exemple de Code

Voici un exemple simple utilisant `poll` pour surveiller l'entrée standard (stdin) pour la lecture.

```cpp
#include <iostream>
#include <poll.h>
#include <unistd.h> // pour STDIN_FILENO

int main() {
    struct pollfd fds[1];
    fds[0].fd = STDIN_FILENO;  // Surveiller l'entrée standard
    fds[0].events = POLLIN;    // Surveiller les données disponibles en lecture

    int timeout = 5000;  // Attendre jusqu'à 5 secondes

    std::cout << "Attente d'une entrée pendant 5 secondes..." << std::endl;

    int ret = poll(fds, 1, timeout);

    if (ret == -1) {
        std::cerr << "Erreur lors de l'appel à poll." << std::endl;
        return 1;
    } else if (ret == 0) {
        std::cout << "Délai d'attente écoulé. Aucun événement détecté." << std::endl;
    } else {
        if (fds[0].revents & POLLIN) {
            std::cout << "Données disponibles en lecture sur l'entrée standard." << std::endl;
        }
    }

    return 0;
}
```

## Conclusion

La fonction `poll` est un outil puissant pour surveiller plusieurs descripteurs de fichiers simultanément. Elle permet aux applications de gérer efficacement les E/S sans avoir à utiliser des techniques de sondage (polling) inefficaces. En comprenant les structures `pollfd` et les différentes valeurs possibles pour les événements, les développeurs peuvent créer des applications robustes et réactives.