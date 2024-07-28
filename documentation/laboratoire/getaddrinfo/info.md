### Fonction `getaddrinfo`

La fonction `getaddrinfo` est utilisée pour obtenir des informations sur une adresse réseau (comme une adresse IP) à partir d'un nom de domaine ou d'une adresse IP et d'un service (comme un numéro de port). Elle est particulièrement utile pour créer des sockets réseau de manière portable et indépendante du protocole.

#### Prototype de la Fonction `getaddrinfo`

```c
int getaddrinfo(const char *__restrict__ __name, const char *__restrict__ __service, const struct addrinfo *__restrict__ __req, struct addrinfo **__restrict__ __pai);
```

#### Paramètres

1. **`__name` (const char *__restrict__)**:
   - **Description**: Le nom de domaine ou l'adresse IP pour lequel obtenir des informations d'adresse. Peut être `NULL` si vous ne spécifiez pas de nom de domaine ou d'adresse IP.
   - **Type**: `const char *`
   - **Exemple**: `"example.com"` ou `"127.0.0.1"`

2. **`__service` (const char *__restrict__)**:
   - **Description**: Le nom du service ou le numéro de port. Peut être `NULL` si vous ne spécifiez pas de service.
   - **Type**: `const char *`
   - **Exemple**: `"http"` ou `"80"`

3. **`__req` (const struct addrinfo *__restrict__)**:
   - **Description**: Un pointeur vers une structure `addrinfo` qui spécifie les critères pour la sélection des adresses. Peut être `NULL` pour utiliser les paramètres par défaut.
   - **Type**: `const struct addrinfo *`
   - **Exemple**:
     ```c
     struct addrinfo hints;
     memset(&hints, 0, sizeof(struct addrinfo));
     hints.ai_family = AF_UNSPEC;
     hints.ai_socktype = SOCK_STREAM;
     ```

4. **`__pai` (struct addrinfo **__restrict__)**:
   - **Description**: Un pointeur vers une variable de type `struct addrinfo *`. La fonction allouera une liste chaînée de structures `addrinfo` et affectera l'adresse de la première structure à cette variable.
   - **Type**: `struct addrinfo **`
   - **Exemple**:
     ```c
     struct addrinfo *result;
     ```

#### Retour

- **Retourne `0` en cas de succès**:
  - Si la fonction réussit, elle retourne `0` et `__pai` pointe vers la première structure `addrinfo` dans la liste chaînée des résultats.

- **Retourne une valeur non nulle en cas d'échec**:
  - En cas d'erreur, la fonction retourne une valeur non nulle et `__pai` est mis à `NULL`.
  - Les erreurs courantes incluent:
    - `EAI_AGAIN`: L'opération a échoué à cause d'une défaillance temporaire, essayez à nouveau.
    - `EAI_BADFLAGS`: Les drapeaux spécifiés dans `__req` ne sont pas valides.
    - `EAI_FAIL`: Une erreur non réversible s'est produite.
    - `EAI_FAMILY`: La famille d'adresses demandée n'est pas supportée.
    - `EAI_NONAME`: Le nom ou le service n'est pas connu.
    - `EAI_SOCKTYPE`: Le type de socket spécifié n'est pas supporté.

#### Ce que fait la Fonction `getaddrinfo`

- **Résolution de Nom**:
  - La fonction résout le nom de domaine ou l'adresse IP spécifié par `__name` en une ou plusieurs adresses réseau.

- **Résolution de Service**:
  - La fonction résout le nom de service ou le numéro de port spécifié par `__service` en un ou plusieurs numéros de port.

- **Allocation de Structures `addrinfo`**:
  - La fonction alloue une liste chaînée de structures `addrinfo` contenant les adresses résolues et les paramètres nécessaires pour créer des sockets.

### Exemple de Code Utilisant `getaddrinfo`

Voici un exemple de code en C++ illustrant comment utiliser `getaddrinfo` pour obtenir des informations d'adresse pour un serveur:

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

    freeaddrinfo(result); // Libérer la liste des adresses

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

La fonction `getaddrinfo` est une méthode pratique et flexible pour résoudre les noms de domaine et les adresses IP en structures d'adresses utilisables pour la création de sockets et l'établissement de connexions réseau. Elle simplifie le processus de manipulation des adresses réseau en gérant automatiquement les détails spécifiques aux protocoles et aux familles d'adresses.