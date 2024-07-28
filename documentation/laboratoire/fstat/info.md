# fstat

## Description

La fonction `fstat` est utilisée pour obtenir des informations sur un fichier ouvert, telles que sa taille, ses permissions, et ses horodatages. Elle remplit une structure `stat` avec les détails du fichier.

## Syntaxe

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int fstat(int fd, struct stat *buf);
```

## Paramètres

- `int fd` : Le descripteur de fichier. Il s'agit d'un entier qui identifie de manière unique le fichier ouvert.
- `struct stat *buf` : Un pointeur vers une structure `stat` où les informations sur le fichier seront stockées.

## Retour

- **Succès** : Retourne `0`.
- **Échec** : Retourne `-1` et définit `errno` pour indiquer l'erreur.

## Structure `stat`

La structure `stat` contient plusieurs champs fournissant des informations détaillées sur le fichier. Voici les membres les plus couramment utilisés :

```c
struct stat {
    dev_t     st_dev;     // Identifiant de périphérique contenant le fichier
    ino_t     st_ino;     // Numéro d'inœud
    mode_t    st_mode;    // Mode de protection (et type de fichier)
    nlink_t   st_nlink;   // Nombre de liens matériels
    uid_t     st_uid;     // UID du propriétaire
    gid_t     st_gid;     // GID du propriétaire
    dev_t     st_rdev;    // Identifiant de périphérique (si c'est un périphérique spécial)
    off_t     st_size;    // Taille totale en octets
    blksize_t st_blksize; // Taille de bloc pour E/S du système de fichiers
    blkcnt_t  st_blocks;  // Nombre de blocs alloués
    time_t    st_atime;   // Heure du dernier accès
    time_t    st_mtime;   // Heure de la dernière modification
    time_t    st_ctime;   // Heure du dernier changement d'état
};
```

### Membres Importants

- `st_size` : Taille du fichier en octets.
- `st_mode` : Mode de protection et type de fichier (utiliser des macros comme `S_ISREG` pour vérifier le type de fichier).
- `st_atime` : Heure du dernier accès.
- `st_mtime` : Heure de la dernière modification.
- `st_ctime` : Heure du dernier changement d'état.

## Exemple de Code

Voici un exemple de code C++98 qui utilise la fonction `fstat` pour obtenir des informations sur un fichier ouvert.

```cpp
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <cerrno>
#include <cstring>

int main() {
    // Ouvrir un fichier en lecture seule
    int fd = open("info.md", O_RDONLY);
    if (fd == -1) {
        std::cerr << "Erreur: Impossible d'ouvrir le fichier. " << strerror(errno) << std::endl;
        return 1;
    }

    struct stat fileStat;
    if (fstat(fd, &fileStat) == -1) {
        std::cerr << "Erreur: Impossible d'obtenir les informations du fichier. " << strerror(errno) << std::endl;
        close(fd);
        return 1;
    }

    std::cout << "Taille du fichier: " << fileStat.st_size << " octets" << std::endl;
    std::cout << "Dernier accès: " << ctime(&fileStat.st_atime);
    std::cout << "Dernière modification: " << ctime(&fileStat.st_mtime);
    std::cout << "Dernier changement d'état: " << ctime(&fileStat.st_ctime);

    // Fermer le fichier
    close(fd);

    return 0;
}
```

## Conclusion

La fonction `fstat` est un outil essentiel pour obtenir des informations sur des fichiers ouverts, permettant aux programmes de gérer et d'analyser les fichiers de manière efficace. En utilisant la structure `stat`, les développeurs peuvent accéder à des détails importants sur les fichiers et les utiliser selon leurs besoins.
