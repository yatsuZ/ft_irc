### Options de la Fonction `setsockopt`

La fonction `setsockopt` permet de configurer diverses options pour une socket en utilisant le paramètre `optname`. Voici une explication des options courantes que vous pouvez définir avec `setsockopt`, ainsi que leur utilisation :

#### 1. **`SO_REUSEADDR`**

- **Description**: Permet à une socket de réutiliser une adresse locale qui est dans un état de délai d'attente (TIME_WAIT). C'est utile pour les serveurs qui redémarrent rapidement et veulent réutiliser le même port sans attendre que le précédent temps d'attente expire.
- **Niveau**: `SOL_SOCKET`
- **Valeur**: Un entier non nul (généralement 1) pour activer l'option.
- **Exemple d'utilisation**:
  ```cpp
  int optval = 1;
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
  ```

#### 2. **`SO_KEEPALIVE`**

- **Description**: Active les messages de keepalive pour vérifier si la connexion est toujours active. Ceci est utilisé pour détecter les connexions mortes dans les protocoles basés sur TCP.
- **Niveau**: `SOL_SOCKET`
- **Valeur**: Un entier non nul pour activer l'option (généralement 1).
- **Exemple d'utilisation**:
  ```cpp
  int optval = 1;
  setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &optval, sizeof(optval));
  ```

#### 3. **`SO_RCVBUF`**

- **Description**: Détermine la taille du tampon de réception pour les données entrantes. Cela affecte la quantité de données que la socket peut recevoir avant que les données ne soient mises en attente.
- **Niveau**: `SOL_SOCKET`
- **Valeur**: Un entier indiquant la taille du tampon en octets.
- **Exemple d'utilisation**:
  ```cpp
  int optval = 8192; // Taille du tampon de réception en octets
  setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &optval, sizeof(optval));
  ```

#### 4. **`SO_SNDBUF`**

- **Description**: Détermine la taille du tampon d'envoi pour les données sortantes. Cela affecte la quantité de données que la socket peut envoyer avant que le système ne bloque pour attendre que de l'espace devienne disponible.
- **Niveau**: `SOL_SOCKET`
- **Valeur**: Un entier indiquant la taille du tampon en octets.
- **Exemple d'utilisation**:
  ```cpp
  int optval = 8192; // Taille du tampon d'envoi en octets
  setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &optval, sizeof(optval));
  ```

#### 5. **`SO_BROADCAST`**

- **Description**: Permet l'envoi de messages de diffusion (broadcast) sur une socket. Par défaut, les sockets ne permettent pas l'envoi de messages de diffusion.
- **Niveau**: `SOL_SOCKET`
- **Valeur**: Un entier non nul pour activer l'option (généralement 1).
- **Exemple d'utilisation**:
  ```cpp
  int optval = 1;
  setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(optval));
  ```

#### 6. **`IP_TTL`**

- **Description**: Définit la durée de vie (TTL) des paquets IP envoyés par la socket. TTL spécifie combien de sauts (ou routeurs) un paquet peut traverser avant d'être rejeté.
- **Niveau**: `IPPROTO_IP`
- **Valeur**: Un entier spécifiant le nombre de sauts (TTL).
- **Exemple d'utilisation**:
  ```cpp
  int optval = 64; // TTL de 64
  setsockopt(sockfd, IPPROTO_IP, IP_TTL, &optval, sizeof(optval));
  ```

#### 7. **`TCP_NODELAY`**

- **Description**: Désactive le mécanisme de Nagle pour une socket TCP. Lorsque cette option est activée, les données sont envoyées immédiatement, même si cela signifie envoyer de petits paquets.
- **Niveau**: `IPPROTO_TCP`
- **Valeur**: Un entier non nul pour activer l'option (généralement 1).
- **Exemple d'utilisation**:
  ```cpp
  int optval = 1;
  setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &optval, sizeof(optval));
  ```

### Résumé

La fonction `setsockopt` vous permet de configurer divers aspects du comportement des sockets en spécifiant un niveau (`level`) et un nom d'option (`optname`). Les options courantes comme `SO_REUSEADDR` et `SO_KEEPALIVE` affectent le comportement général des sockets, tandis que d'autres options comme `SO_RCVBUF` et `SO_SNDBUF` contrôlent la taille des tampons. Le bon usage de ces options permet d'optimiser la performance et la fiabilité des communications réseau.