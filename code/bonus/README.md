BOT IRC
	Programme indépendant du serveur
	qui opermet d'utiliser des fonctions du protocol IRC en autonomie.

	Le bot IRC se connecte au salon comme un utilisateur normal et peut 
	etre configuré pour donner le statut opérateur de salon IRC.
	Les bots IRC peuvent aussi etre configuré pour executer des commandes
	et actions customisées sur un channel.


TYPE DE BOT
	> BOT Interne:
		intégré direectement au code du serveur
		Malus: N'est pas une méthode conventionnelle d'IRC, 
				s'éloigne du principe d'IRC
	> BOT Externe:
		Programme indépendant fonctionnant comme un client 
		 qui se connecte au serveur IRC.
		Avantages:
			+ commme le programme est indépendant du serveur
			le bot peut etre démarré/arrêté sans affecter
			le serveur, les bugs/majs peuvent donc être 
			corrigé sans avoir a arrêter le serveur
			+ Permet d'avoir plusieurs instances de Bot
			 avec différentes configurations et commandes
			+ Tester le bot indépendamment du serveur
			+ Utilise ses propres ressources donc moins 
				lourd pour le serveur 


//////////////////////////////
CONFIGURATION DU BOT
	SET un fichier CONFIG (infos du bot + adresse ip + port)
	parse le fichier config
	socket() -> connect() (vers le serv)

Cas action_censure_msg
	Si un message utilisateur comporte une insulte
	Le bot doit le récéptionner avant réponse du serveur 
	et renvoyer le message en se passant pour l'utilisateur.
	PRIVMSG !user au lieu de PRIVMSG !bot
	PROBLEME => Comment empecher le serv d'envoyer PRIVMSG pour
	 permettre au bot de l'envoyer lui meme.


TO DO::
Reception et envoi des données
Implementation des actions