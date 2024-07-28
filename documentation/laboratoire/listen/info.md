# listen

La fonction `listen` est utilisée dans les programmes réseau pour mettre une socket en état d'écoute, afin qu'elle puisse recevoir des connexions entrantes. Voici une explication détaillée de son rôle et de son fonctionnement :

### Fonction `listen`

#### Prototype

```c
int listen(int sockfd, int backlog);
```

#### Paramètres

1. **`sockfd`**:
   - Il s'agit du descripteur de fichier (ou socket) qui a été créé avec la fonction `socket` et lié à une adresse locale avec la fonction `bind`.
   - Ce descripteur de fichier doit correspondre à une socket de type `SOCK_STREAM` (pour TCP).

2. **`backlog`**:
   - Ce paramètre définit la longueur maximale de la file d'attente des connexions entrantes non encore acceptées.
   - Si des connexions arrivent lorsque la file d'attente est pleine, les nouvelles connexions peuvent être rejetées ou ignorées, selon le système.

#### Retour

- **0** : Si la mise en écoute a réussi.
- **-1** : En cas d'échec, et la variable globale `errno` est définie pour indiquer l'erreur spécifique.

### Rôle de `listen`

1. **Transition en Mode Écoute**:
   - La fonction `listen` configure la socket spécifiée pour qu'elle passe du mode inactif au mode écoute.
   - Cela signifie que la socket est prête à accepter les connexions entrantes via la fonction `accept`.

2. **Gestion des Connexions Entrantes**:
   - En spécifiant la valeur `backlog`, le programme indique combien de connexions peuvent être mises en file d'attente en attendant d'être acceptées.
   - Cela permet de gérer efficacement plusieurs connexions simultanées.

3. **Préparation à l'Acceptation**:
   - Après avoir appelé `listen`, le programme peut utiliser la fonction `accept` pour accepter les connexions entrantes de la file d'attente.
   - `listen` est une étape intermédiaire cruciale dans le cycle de vie d'une connexion serveur-client, car elle prépare la socket à accepter des connexions.

### Exemple de Cycle de Vie d'une Connexion Serveur

1. **Création de la Socket**:
   - Utilisation de `socket` pour créer une socket.

2. **Liaison de la Socket**:
   - Utilisation de `bind` pour attacher la socket à une adresse locale (et un port).

3. **Mise en Écoute**:
   - Utilisation de `listen` pour mettre la socket en état d'écoute.

4. **Acceptation des Connexions**:
   - Utilisation de `accept` pour accepter les connexions entrantes et créer de nouvelles sockets spécifiques à chaque connexion.

### Diagramme

Voici un diagramme simple pour illustrer l'utilisation de `listen` dans le cycle de vie d'une connexion serveur :

```text
socket() --> bind() --> listen() --> accept() --> read()/write() --> close()
```

### Exemple de Code Simplifié

```cpp
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 8080

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr << "Erreur de création de la socket" << std::endl;
        return 1;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Erreur de liaison de la socket" << std::endl;
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, 5) < 0) {
        std::cerr << "Erreur de mise en écoute" << std::endl;
        close(server_fd);
        return 1;
    }

    std::cout << "Serveur en écoute sur le port " << PORT << std::endl;

    sockaddr_in client_address;
    socklen_t client_len = sizeof(client_address);
    int client_fd = accept(server_fd, (struct sockaddr*)&client_address, &client_len);
    if (client_fd < 0) {
        std::cerr << "Erreur d'acceptation de la connexion" << std::endl;
        close(server_fd);
        return 1;
    }

    std::cout << "Connexion acceptée" << std::endl;

    close(client_fd);
    close(server_fd);

    return 0;
}
```

### Conclusion

La fonction `listen` joue un rôle crucial dans la préparation d'une socket serveur pour accepter les connexions entrantes. Elle configure la socket pour qu'elle puisse gérer efficacement les demandes de connexion entrantes en les plaçant dans une file d'attente jusqu'à ce qu'elles puissent être acceptées avec `accept`. Sans `listen`, une socket serveur ne peut pas répondre aux demandes de connexion des clients.