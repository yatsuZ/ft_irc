### Fonction `getsockname`

La fonction `getsockname` est utilisée pour obtenir l'adresse locale d'une socket, c'est-à-dire l'adresse et le port qui ont été associés à la socket via `bind()`. Cette fonction est souvent utilisée après avoir lié une socket à une adresse pour déterminer quel est le port local attribué par le système si le port n'a pas été spécifié explicitement.

#### Prototype de la Fonction `getsockname`

```c
int getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```

#### Paramètres

1. **`sockfd` (int)**:
   - **Description**: Le descripteur de fichier de la socket dont vous voulez obtenir l'adresse locale.
   - **Type**: `int`
   - **Exemple**: Une socket précédemment créée et liée avec `socket()` et `bind()`, par exemple, `int sockfd = socket(AF_INET, SOCK_STREAM, 0);`.

2. **`addr` (struct sockaddr *)**:
   - **Description**: Un pointeur vers une structure `sockaddr` dans laquelle l'adresse locale sera stockée. Vous devrez caster ce pointeur vers une structure plus spécifique comme `sockaddr_in` pour IPv4.
   - **Type**: `struct sockaddr *`
   - **Exemple**: `struct sockaddr_in local_address;`

3. **`addrlen` (socklen_t *)**:
   - **Description**: Un pointeur vers une variable contenant la taille de la structure `sockaddr`. Cette variable sera mise à jour pour contenir la taille de l'adresse renvoyée.
   - **Type**: `socklen_t *`
   - **Exemple**: `socklen_t addr_len = sizeof(local_address);`

#### Retour

- **Retourne `0` en cas de succès**:
  - Si l'adresse locale est obtenue avec succès, `getsockname` retourne `0`.

- **Retourne `-1` en cas d'échec**:
  - En cas d'erreur, `getsockname` retourne `-1` et définit `errno` pour indiquer l'erreur spécifique.

#### Ce que fait la Fonction `getsockname`

- **Obtenir l'Adresse Locale**:
  - La fonction `getsockname` permet de récupérer l'adresse locale (IP et port) actuellement associée à la socket spécifiée. Cela est utile pour déterminer le port local attribué automatiquement par le système ou pour obtenir des informations sur l'interface réseau utilisée.

### Exemple de Code Utilisant `getsockname`

Voici un exemple de code en C++ illustrant comment utiliser `getsockname` pour obtenir l'adresse locale d'une socket après l'avoir liée à un port :

```cpp
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 8080

int main() {
    // Créer une socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Erreur de création de la socket" << std::endl;
        return 1;
    }

    // Configurer l'adresse et le port du serveur
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY); // Adresse IP du serveur
    server_address.sin_port = htons(PORT); // Port du serveur

    // Associer la socket à l'adresse et au port spécifiés
    if (bind(sockfd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        std::cerr << "Erreur dans bind" << std::endl;
        close(sockfd);
        return 1;
    }

    // Obtenir l'adresse locale associée à la socket
    struct sockaddr_in local_address;
    socklen_t addr_len = sizeof(local_address);
    if (getsockname(sockfd, (struct sockaddr*)&local_address, &addr_len) < 0) {
        std::cerr << "Erreur dans getsockname" << std::endl;
        close(sockfd);
        return 1;
    }

    std::cout << "Adresse locale : " << inet_ntoa(local_address.sin_addr) << std::endl;
    std::cout << "Port local : " << ntohs(local_address.sin_port) << std::endl;

    // Fermer la socket
    close(sockfd);
    return 0;
}
```

### Compilation et Exécution

Pour compiler ce code, utilisez la commande suivante dans votre terminal :

```sh
g++ -o getsockname_example getsockname_example.cpp
```

Ensuite, exécutez le programme :

```sh
./getsockname_example
```

### Conclusion

La fonction `getsockname` est utilisée pour obtenir l'adresse locale associée à une socket. Elle prend comme paramètres le descripteur de la socket, un pointeur vers une structure `sockaddr` pour stocker l'adresse, et un pointeur vers une variable de taille pour la structure. Elle retourne `0` en cas de succès et `-1` en cas d'échec, avec `errno` définissant l'erreur spécifique. Utiliser cette fonction vous permet de déterminer l'adresse IP et le port local attribués à une socket, ce qui est utile pour des diagnostics et pour des configurations réseau dynamiques.