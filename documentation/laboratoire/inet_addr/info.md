# inet_addr


## Description

La fonction `inet_addr` est utilisée pour convertir une adresse IPv4 en notation décimale pointée (ex: "192.168.1.1") en une représentation binaire compatible avec le protocole réseau (de type `in_addr_t`). Cette conversion est nécessaire pour utiliser les adresses IP dans les appels système et les structures de données réseau.

## Explication des paramètres et des retours

### Paramètre

- `const char* cp` : C'est une chaîne de caractères représentant l'adresse IP en notation décimale pointée (par exemple, "192.168.1.1").

### Retour

- `in_addr_t inet_addr(const char* cp)` : La fonction retourne une représentation binaire de l'adresse IP en type `in_addr_t`. Si l'adresse IP est invalide, la fonction retourne `INADDR_NONE`.

## Explications détaillées

### Conversion d'une adresse IP

La fonction `inet_addr` prend une adresse IP sous forme de chaîne de caractères et la convertit en un format binaire. Ce format binaire est requis pour les opérations réseau au niveau du système.

### Vérification de la validité

Si la conversion échoue, la fonction retourne `INADDR_NONE`, ce qui signifie que l'adresse IP fournie est invalide. Il est important de vérifier ce retour pour s'assurer que l'adresse IP est correcte avant de l'utiliser dans des opérations réseau.

### Affichage de l'adresse IP

Le code ci-dessus montre comment convertir une adresse IP en format binaire, puis comment la reconvertir en une chaîne de caractères lisible pour vérifier la conversion.

## Conclusion

La fonction `inet_addr` est utile pour convertir des adresses IP en format texte en une représentation binaire utilisable dans les opérations réseau en C++98. Cette fonction est simple à utiliser mais doit être manipulée avec précaution pour vérifier la validité des adresses IP.