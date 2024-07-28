# send

#### Prototype

```c
ssize_t send(int sockfd, const void *buf, size_t len, int flags);
```

#### Paramètres

1. **`sockfd`**:
   - Le descripteur de fichier de la socket sur laquelle les données seront envoyées.
   - Doit être une socket connectée, typiquement obtenue via `accept` pour un serveur.

2. **`buf`**:
   - Un pointeur vers le tampon contenant les données à envoyer.

3. **`len`**:
   - La taille en octets des données à envoyer.

4. **`flags`**:
   - Les indicateurs qui modifient le comportement de la fonction `send`.
   - `0` signifie aucun indicateur spécial.
   - D'autres indicateurs peuvent être utilisés, comme `MSG_DONTWAIT` pour ne pas bloquer l'appel, `MSG_OOB` pour envoyer des données hors bande, etc.

#### Retour

- **Nombre d'octets envoyés** : Si l'appel réussit.
- **-1** : En cas d'échec, et la variable globale `errno` est définie pour indiquer l'erreur spécifique.

### Explication du Code

1. **Création de la Socket Serveur**:
   - `int server_fd = socket(AF_INET, SOCK_STREAM, 0);`
     - Crée une socket TCP/IP.

2. **Configuration de l'Adresse**:
   - `sockaddr_in address;`
     - Définit l'adresse du serveur.

3. **Liaison de la Socket**:
   - `bind(server_fd, (struct sockaddr*)&address, sizeof(address));`
     - Associe la socket à l'adresse locale spécifiée.

4. **Mise en Écoute**:
   - `listen(server_fd, 5);`
     - Configure la socket pour écouter les connexions entrantes.

5. **Acceptation d'une Connexion Entrante**:
   - `int client_fd = accept(server_fd, (struct sockaddr*)&client_address, &client_len);`
     - Accepte une connexion entrante et renvoie une nouvelle socket pour la communication avec le client.

6. **Envoi de Données au Client**:
   - `ssize_t bytes_sent = send(client_fd, message, strlen(message), 0);`
     - Utilise `send` pour envoyer le message au client.

7. **Fermeture des Sockets**:
   - `close(client_fd);`
     - Ferme la socket client.
   - `close(server_fd);`
     - Ferme la socket serveur.

### Conclusion

La fonction `send` permet d'envoyer des données sur une socket connectée. Dans cet exemple, un serveur simple accepte une connexion client et utilise `send` pour envoyer un message. Le code gère également les erreurs potentielles lors de la création de la socket, de la liaison, de la mise en écoute, de l'acceptation de la connexion et de l'envoi des données. Les couleurs sont utilisées pour améliorer la lisibilité des messages de succès et d'erreur.