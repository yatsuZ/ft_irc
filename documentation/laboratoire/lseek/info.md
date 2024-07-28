### Description de la fonction `lseek`

La fonction `lseek` est utilisée pour déplacer le pointeur de lecture/écriture d'un fichier ouvert à une nouvelle position. Cela permet de lire ou d'écrire des données à une position spécifique dans le fichier.

### Syntaxe

```c
#include <unistd.h>

off_t lseek(int fd, off_t offset, int whence);
```

### Paramètres

- `int fd` : Le descripteur de fichier. Il s'agit d'un entier qui identifie de manière unique le fichier ouvert.
- `off_t offset` : Le déplacement en octets par rapport à la position spécifiée par `whence`.
- `int whence` : La position de référence à partir de laquelle le déplacement est effectué. Les valeurs possibles sont :
  - `SEEK_SET` : Le début du fichier.
  - `SEEK_CUR` : La position actuelle du pointeur de fichier.
  - `SEEK_END` : La fin du fichier.

### Retour

- La fonction retourne la nouvelle position du pointeur de fichier par rapport au début du fichier, en cas de succès.
- Si la fonction échoue, elle retourne `-1` et définit `errno` pour indiquer l'erreur.

### Utilisation

Voici un exemple de code C++98 qui utilise la fonction `lseek` pour déplacer le pointeur de fichier.

### Exemple de Code

```cpp
#include <iostream>
#include <fcntl.h>   // pour open
#include <unistd.h>  // pour lseek, read, close
#include <cerrno>    // pour errno
#include <cstring>   // pour strerror

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

int main() {
    // Ouvrir un fichier en lecture seule
    int fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        std::cerr << RED << "Erreur: Impossible d'ouvrir le fichier. " << strerror(errno) << NOCOLOR << std::endl;
        return 1;
    }

    // Déplacer le pointeur de fichier à 10 octets depuis le début
    off_t new_pos = lseek(fd, 10, SEEK_SET);
    if (new_pos == (off_t)-1) {
        std::cerr << RED << "Erreur: Impossible de déplacer le pointeur de fichier. " << strerror(errno) << NOCOLOR << std::endl;
        close(fd);
        return 1;
    }

    std::cout << GREEN << "Le pointeur de fichier a été déplacé à la position " << new_pos << NOCOLOR << std::endl;

    // Lire et afficher le contenu du fichier à partir de la nouvelle position
    char buffer[128];
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1) {
        std::cerr << RED << "Erreur: Impossible de lire le fichier. " << strerror(errno) << NOCOLOR << std::endl;
        close(fd);
        return 1;
    }

    buffer[bytes_read] = '\0';  // Assurer que le buffer est terminé par un nul
    std::cout << YELLOW << "Contenu lu: " << buffer << NOCOLOR << std::endl;

    // Fermer le fichier
    close(fd);

    return 0;
}
```

## Conclusion

La fonction lseek est un outil puissant pour manipuler les positions de lecture/écriture dans un fichier ouvert. Elle permet aux développeurs de gérer efficacement les accès aléatoires aux données, facilitant ainsi les opérations sur de grands fichiers ou les fichiers nécessitant des accès non séquentiels.

