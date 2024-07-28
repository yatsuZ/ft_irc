# sigaction

## Description

La fonction `sigaction` permet de définir une action à entreprendre lorsqu'un signal spécifique est reçu par le processus. Elle est plus puissante et flexible que la fonction `signal`, car elle permet de spécifier des options supplémentaires et de manipuler les masques de signaux.

## Exemple de Code

```cpp
#include <iostream>
#include <csignal>
#include <cstring>

// Définir les couleurs
#define NOCOLOR "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define PURPLE "\033[35m"

// Gestionnaire de signal
void signal_handler(int signal_num) {
    std::cout << RED << "Signal reçu: " << signal_num << NOCOLOR << std::endl;
}

int main() {
    struct sigaction sa;

    // Initialiser la structure sigaction à zéro
    std::memset(&sa, 0, sizeof(sa));

    // Spécifier le gestionnaire de signal
    sa.sa_handler = signal_handler;

    // Spécifier les signaux à intercepter
    if (sigaction(SIGINT, &sa, NULL) != 0) {
        std::cerr << RED << "Erreur: Impossible d'intercepter SIGINT." << NOCOLOR << std::endl;
        return 1;
    }

    std::cout << GREEN << "Appuyez sur Ctrl+C pour envoyer SIGINT" << NOCOLOR << std::endl;

    // Boucle infinie pour garder le programme en cours d'exécution
    while (true) {}

    return 0;
}
```

## Explication des paramètres et des retours

### Paramètres

- `int signum` : Le numéro du signal à intercepter (par exemple, `SIGINT`).
- `const struct sigaction *act` : Pointeur vers une structure `sigaction` qui spécifie l'action à associer au signal.
- `struct sigaction *oldact` : Pointeur vers une structure `sigaction` où l'ancienne action associée au signal sera stockée. Peut être `NULL` si l'ancienne action n'est pas nécessaire.

### Retour

- `int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact)` : La fonction retourne 0 en cas de succès, et -1 en cas d'erreur (avec `errno` définie pour indiquer l'erreur).

## Explications détaillées

### Gestion des signaux

La fonction `sigaction` est utilisée pour définir comment un programme doit réagir lorsqu'il reçoit un signal spécifique. Cela inclut des signaux comme `SIGINT` (généralement généré par `Ctrl+C`), `SIGTERM`, etc.

### Structure `sigaction`

La structure `sigaction` est utilisée pour spécifier l'action à prendre lorsqu'un signal est reçu. Elle inclut plusieurs membres importants, tels que:
- `sa_handler` : Pointeur vers la fonction de gestion des signaux.
- `sa_mask` : Masque de signaux à bloquer pendant l'exécution du gestionnaire de signaux.
- `sa_flags` : Options de comportement pour le gestionnaire de signaux.

### Installation d'un gestionnaire de signaux

L'exemple de code montre comment installer un gestionnaire pour le signal `SIGINT`. Lorsque ce signal est reçu (par exemple, lorsque l'utilisateur appuie sur `Ctrl+C`), la fonction `signal_handler` sera appelée.

### Vérification de l'interception

Il est important de vérifier si l'appel à `sigaction` réussit, en vérifiant le retour de la fonction. Si elle échoue, elle retourne -1, et il faut gérer cette erreur de manière appropriée.

### Conclusion

La fonction `sigaction` est une méthode puissante et flexible pour gérer les signaux en C++98. Elle permet de définir des actions spécifiques pour divers signaux, facilitant ainsi le contrôle et la gestion des interruptions et autres événements asynchrones dans un programme.