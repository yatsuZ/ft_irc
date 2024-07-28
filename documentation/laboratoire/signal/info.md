### Fonction `signal`

La fonction `signal` est utilisée pour installer un gestionnaire de signaux. Elle permet de spécifier une fonction qui sera appelée lorsqu'un signal spécifique est reçu par le processus. C'est un mécanisme clé pour gérer les signaux asynchrones dans les programmes.

#### Prototype de la Fonction `signal`

```c
void (*signal(int signum, void (*handler)(int)))(int);
```

#### Paramètres

1. **`signum` (int)**:
   - **Description**: Le numéro du signal pour lequel vous souhaitez installer un gestionnaire.
   - **Type**: `int`
   - **Exemple**: `SIGINT`, `SIGTERM`, `SIGUSR1`, etc.

2. **`handler` (void (*)(int))**:
   - **Description**: Pointeur vers la fonction gestionnaire qui sera appelée lorsque le signal est reçu. La fonction gestionnaire doit avoir la signature `void handler(int signum)`.
   - **Type**: `void (*)(int)`
   - **Exemple**: Un pointeur vers une fonction personnalisée, par exemple `void my_handler(int signum)`.

#### Retour

- **Retourne l'ancienne valeur du gestionnaire de signaux**:
  - La fonction retourne un pointeur vers l'ancienne fonction gestionnaire pour le signal `signum`. Si le précédent gestionnaire était le gestionnaire par défaut ou si aucun gestionnaire n'était défini, le retour peut être `SIG_DFL` ou `SIG_IGN`.

#### Ce que fait la Fonction `signal`

- **Installation de Gestionnaire de Signaux**:
  - La fonction `signal` permet d'associer un signal à un gestionnaire personnalisé. Lorsque le signal est reçu, le gestionnaire est exécuté.
  - Par exemple, vous pouvez utiliser `signal` pour exécuter une fonction spécifique lorsque l'utilisateur appuie sur Ctrl+C (`SIGINT`) ou lorsque le processus reçoit un signal de terminaison (`SIGTERM`).

### Exemple de Code Utilisant `signal`

Voici un exemple en C++ montrant comment utiliser `signal` pour gérer les signaux `SIGINT` (généré par Ctrl+C) et `SIGTERM` (signal de terminaison). Dans cet exemple, nous installons des gestionnaires de signaux pour afficher un message avant que le programme se termine.

```cpp
#include <iostream>
#include <csignal>
#include <unistd.h>

// Gestionnaire pour SIGINT (Ctrl+C)
void handle_sigint(int signum) {
    std::cout << "Signal SIGINT reçu. Terminaison propre." << std::endl;
    exit(0); // Quitter proprement
}

// Gestionnaire pour SIGTERM
void handle_sigterm(int signum) {
    std::cout << "Signal SIGTERM reçu. Terminaison propre." << std::endl;
    exit(0); // Quitter proprement
}

int main() {
    // Installer les gestionnaires de signaux
    signal(SIGINT, handle_sigint);
    signal(SIGTERM, handle_sigterm);

    std::cout << "Programme en cours d'exécution. Appuyez sur Ctrl+C ou envoyez SIGTERM pour terminer." << std::endl;

    // Boucle infinie pour maintenir le programme en cours d'exécution
    while (true) {
        sleep(1);
    }

    return 0;
}
```

### Compilation et Exécution

Pour compiler le code, utilisez la commande suivante :

```sh
g++ -o signal_example signal_example.cpp
```

Ensuite, exécutez le programme :

```sh
./signal_example
```

### Conclusion

La fonction `signal` est utilisée pour installer des gestionnaires pour les signaux dans un programme. Vous pouvez associer un signal à une fonction gestionnaire pour contrôler le comportement du programme lorsqu'un signal est reçu. En cas de réception d'un signal comme `SIGINT` ou `SIGTERM`, le gestionnaire spécifié sera exécuté, permettant au programme de gérer proprement les événements asynchrones.