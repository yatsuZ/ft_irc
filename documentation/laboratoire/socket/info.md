# socket

La fonction socket est utilisée pour créer un descripteur de socket dans les systèmes de type Unix, y compris Linux et macOS.
Voici une explication détaillée des paramètres et du retour de cette fonction :

## Déclaration de la Fonction
```cpp
int socket(int domain, int type, int protocol);
```

## Paramètres

1. domain (ou AF_INET dans ce cas) :

- Définit le domaine de communication.
- AF_INET : Utilisé pour la communication sur des réseaux IPv4.
- D'autres domaines incluent AF_INET6 pour IPv6, AF_UNIX pour les sockets de domaine UNIX, etc.

2. type (ou SOCK_STREAM dans ce cas) :

- Spécifie le type de socket.
- SOCK_STREAM : Indique que la socket est un flux de données, typiquement utilisé pour TCP. Cela garantit une connexion fiable et ordonnée.
- D'autres types incluent SOCK_DGRAM pour les sockets de datagrammes (typiquement utilisés pour UDP), SOCK_RAW pour les sockets brutes, etc.

3. protocol (ou 0 dans ce cas) :

- Définit le protocole à utiliser avec la socket.
- 0 : Permet au système d'utiliser le protocole par défaut associé au type de socket. Pour SOCK_STREAM, cela se traduit généralement par le protocole TCP.
- Si vous souhaitez spécifier un protocole particulier, vous pouvez utiliser des valeurs comme IPPROTO_TCP pour TCP ou IPPROTO_UDP pour UDP.

## Retour

La fonction socket retourne un descripteur de socket qui est un entier.

- Si le descripteur est positif (≥ 0) : Cela signifie que la socket a été créée avec succès, et le descripteur peut être utilisé pour les opérations suivantes (liaison, écoute, acceptation, lecture, écriture, etc.).

- Si la fonction échoue : Elle retourne -1 et définit la variable globale errno pour indiquer la raison de l'échec. Les erreurs courantes peuvent inclure des problèmes de mémoire, des paramètres invalides, ou un manque de ressources système.


## Ce Que Fait socket

1. Création de la Socket :

- La fonction crée un point de communication pour les processus qui veulent échanger des données.
- Elle réserve des ressources système nécessaires pour que les opérations de communication puissent se dérouler.

2. Configuration de la Socket :

- Le domaine, le type et le protocole déterminent comment les données seront envoyées et reçues à travers la socket.
- AF_INET et SOCK_STREAM avec un protocole de 0 configurent la socket pour utiliser TCP sur IPv4.