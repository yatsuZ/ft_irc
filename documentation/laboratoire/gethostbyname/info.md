# gethostbyname

## Description

La fonction `gethostbyname` est utilisée pour résoudre un nom d'hôte en une ou plusieurs adresses IP. Elle permet de récupérer des informations sur un hôte spécifique, telles que ses alias, son adresse IP, et son nom officiel.

## Explication des paramètres et des retours

### Paramètre

- `const char* hostname` : C'est le nom d'hôte que vous souhaitez résoudre. Par exemple, "www.example.com".

### Retour

- `struct hostent* gethostbyname(const char* name)` : La fonction retourne un pointeur vers une structure `hostent` contenant les informations sur l'hôte. Si la résolution échoue, elle retourne `NULL`.

### Structure `hostent`

- `h_name` : Nom officiel de l'hôte.
- `h_aliases` : Liste des alias pour cet hôte.
- `h_addrtype` : Type d'adresse (par exemple, AF_INET pour IPv4).
- `h_length` : Longueur des adresses.
- `h_addr_list` : Liste des adresses IP pour cet hôte.

## Explications détaillées

### Résolution de l'adresse IP

La fonction `gethostbyname` effectue une recherche DNS pour résoudre le nom d'hôte en une ou plusieurs adresses IP. Elle remplit une structure `hostent` avec les informations obtenues.

### Affichage des informations

Le code ci-dessus affiche les informations suivantes :
- Le nom officiel de l'hôte.
- Les alias associés à l'hôte.
- Les adresses IP de l'hôte.

Les différentes parties de l'information sont affichées en couleur pour faciliter la lecture.

## Conclusion

La fonction `gethostbyname` est une méthode simple pour résoudre des noms d'hôtes en adresses IP en C++98. Elle est utile pour les applications nécessitant la communication réseau et la résolution DNS. Toutefois, notez que cette fonction est obsolète dans les normes plus récentes et devrait être remplacée par des fonctions plus modernes comme `getaddrinfo` dans les nouvelles applications.
