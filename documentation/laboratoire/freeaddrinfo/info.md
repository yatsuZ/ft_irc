### Fonction `freeaddrinfo`

La fonction `freeaddrinfo` est utilisée pour libérer la mémoire allouée par une précédente appel à `getaddrinfo`. Lorsque vous avez terminé d'utiliser les structures d'adresse obtenues par `getaddrinfo`, vous devez appeler `freeaddrinfo` pour éviter les fuites de mémoire.

#### Prototype de la Fonction `freeaddrinfo`

```c
void freeaddrinfo(struct addrinfo *res);
```

#### Paramètres

- **`res` (struct addrinfo *)**:
  - **Description**: Un pointeur vers la première structure `addrinfo` de la liste chaînée qui a été allouée par `getaddrinfo`.
  - **Type**: `struct addrinfo *`

#### Ce que fait la Fonction `freeaddrinfo`

- **Libération de Mémoire**:
  - La fonction `freeaddrinfo` libère la mémoire allouée pour la liste chaînée de structures `addrinfo`. Cela inclut toutes les structures individuelles et les informations associées (comme les noms de service et les adresses IP) qui ont été allouées par `getaddrinfo`.

### Exemple de Code Utilisant `getaddrinfo` et `freeaddrinfo`

Voici un exemple de code en C++ illustrant comment utiliser `getaddrinfo` pour obtenir des informations d'adresse et `freeaddrinfo` pour libérer la mémoire allouée :

```cpp
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main() {
    const char *hostname = "example.com"; // Nom de domaine du serveur
    const char *port = "80"; // Port du service

    // Structure pour stocker les résultats de getaddrinfo
    struct addrinfo hints;
    struct addrinfo *result, *rp;

    // Effacer la structure hints pour éviter des comportements imprévisibles
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    // Permet IPv4 ou IPv6
    hints.ai_socktype = SOCK_STREAM; // Utiliser une socket de type stream (TCP)
    hints.ai_flags = 0;
    hints.ai_protocol = 0;          // Tout protocole

    // Obtenir la liste des adresses
    int s = getaddrinfo(hostname, port, &hints, &result);
    if (s != 0) {
        std::cerr << "Erreur dans getaddrinfo: " << gai_strerror(s) << std::endl;
        exit(EXIT_FAILURE);
    }

    // Boucle à travers toutes les adresses retournées et essayer de se connecter à une
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        int sockfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sockfd == -1)
            continue;

        if (connect(sockfd, rp->ai_addr, rp->ai_addrlen) != -1) {
            std::cout << "Connexion réussie à " << hostname << " sur le port " << port << std::endl;
            close(sockfd);
            break; // Succès
        }

        close(sockfd);
    }

    if (rp == NULL) {
        std::cerr << "Impossible de se connecter à " << hostname << " sur le port " << port << std::endl;
        exit(EXIT_FAILURE);
    }

    // Libérer la liste des adresses
    freeaddrinfo(result);

    return 0;
}
```

### Compilation et Exécution

Pour compiler ce code, utilisez la commande suivante dans votre terminal :

```sh
g++ -o client_getaddrinfo_example client_getaddrinfo_example.cpp
```

Ensuite, exécutez le programme :

```sh
./client_getaddrinfo_example
```

### Conclusion

La fonction `freeaddrinfo` est utilisée pour libérer la mémoire allouée par `getaddrinfo`. Elle prend en paramètre un pointeur vers la première structure `addrinfo` de la liste chaînée. Cela permet de nettoyer proprement toutes les structures et les informations associées allouées par `getaddrinfo`, évitant ainsi les fuites de mémoire.