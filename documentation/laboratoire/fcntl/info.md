### Fonction `fcntl`

La fonction `fcntl` est utilisée pour manipuler des descripteurs de fichiers en permettant des opérations telles que le changement des attributs de fichier, la gestion des verrous, et plus encore. Cette fonction est polyvalente et fournit des fonctionnalités étendues pour la gestion des fichiers et des sockets.

#### Prototype de la Fonction `fcntl`

```c
int fcntl(int fd, int cmd, ... /* arg */);
```

#### Paramètres

1. **`fd` (int)**:
   - **Description**: Le descripteur de fichier que vous souhaitez manipuler.
   - **Type**: `int`
   - **Exemple**: Un descripteur de fichier ou de socket obtenu par une fonction comme `open()` ou `socket()`.

2. **`cmd` (int)**:
   - **Description**: La commande spécifiant l'opération à effectuer. Les commandes courantes incluent :
     - `F_DUPFD`: Duplique le descripteur de fichier.
     - `F_GETFD`: Obtient les attributs du fichier.
     - `F_SETFD`: Définit les attributs du fichier.
     - `F_GETFL`: Obtient les flags de fichier.
     - `F_SETFL`: Définit les flags de fichier.
   - **Type**: `int`
   - **Exemple**: `F_GETFL`, `F_SETFL`.

3. **`arg` (optional)**:
   - **Description**: Un argument optionnel utilisé en fonction de la commande. Par exemple, avec `F_SETFL`, c'est un ensemble de flags de fichier à définir.
   - **Type**: `int` ou `struct` (dépend de la commande)
   - **Exemple**: `O_NONBLOCK` pour définir la socket en mode non-bloquant.

#### Retour

- **En cas de succès**:
  - La valeur retournée dépend de la commande. Par exemple, pour `F_GETFL`, elle retourne les flags de fichier actuels. Pour `F_DUPFD`, elle retourne le nouveau descripteur de fichier dupliqué.

- **En cas d'échec**:
  - Retourne `-1` et définit `errno` pour indiquer l'erreur spécifique.

#### Ce que fait la Fonction `fcntl`

- **Manipulation de Descripteurs de Fichiers**:
  - `fcntl` permet de dupliquer des descripteurs de fichiers, de changer leurs attributs (comme définir des descripteurs en mode non-bloquant), et d'obtenir ou définir des flags et attributs spécifiques.

### Exemple de Code Utilisant `fcntl`

Voici un exemple de code en C++ illustrant comment utiliser `fcntl` pour définir une socket en mode non-bloquant :

```cpp
#include <iostream>
#include <fcntl.h>    // Pour fcntl
#include <unistd.h>   // Pour close
#include <sys/socket.h> // Pour socket
#include <netinet/in.h> // Pour sockaddr_in
#include <cstring>    // Pour memset

#define PORT 8080

int main() {
    // Créer une socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Erreur de création de la socket" << std::endl;
        return 1;
    }

    // Obtenir les flags actuels de la socket
    int flags = fcntl(sockfd, F_GETFL, 0);
    if (flags < 0) {
        std::cerr << "Erreur dans fcntl (F_GETFL)" << std::endl;
        close(sockfd);
        return 1;
    }

    // Définir la socket en mode non-bloquant
    if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) < 0) {
        std::cerr << "Erreur dans fcntl (F_SETFL)" << std::endl;
        close(sockfd);
        return 1;
    }

    std::cout << "Socket définie en mode non-bloquant" << std::endl;

    // Fermer la socket
    close(sockfd);
    return 0;
}
```

### Compilation et Exécution

Pour compiler ce code, utilisez la commande suivante dans votre terminal :

```sh
g++ -o fcntl_example fcntl_example.cpp
```

Ensuite, exécutez le programme :

```sh
./fcntl_example
```

### Conclusion

La fonction `fcntl` est une fonction polyvalente utilisée pour manipuler des descripteurs de fichiers et de sockets. Elle permet de dupliquer des descripteurs, d'obtenir et de définir des attributs et des flags, et de gérer des fonctionnalités avancées comme les verrous de fichiers. En cas de succès, la valeur retournée dépend de la commande exécutée; en cas d'échec, `-1` est retourné avec `errno` fournissant des détails sur l'erreur.