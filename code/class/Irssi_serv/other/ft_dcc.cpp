/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dcc.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 00:48:54 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/16 22:33:46 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

/// @brief Dans le protocole IRC, \x01 est utilisé pour délimiter les commandes spéciales appelées CTCP (Client-To-Client Protocol). donc on verifie sa 
/// @param cmd ma strucutre de commande que jai recu
/// @return vrai si commence et termine par le char \x01
bool Irssi_serv::_is_CTCP(Cmd_irssi & cmd)
{
	std::string msg = cmd.get_message();

	return msg.size() > 1 && msg[0] == '\x01' && msg[msg.size() - 1] == '\x01';
}

/// @brief DCC (Direct Client-to-Client) est un sous-protocole CTCP permettant des connexions directes entre utilisateurs IRC. 
///        Il est utilisé pour l'envoi de fichiers (DCC SEND) et les discussions privées (DCC CHAT), évitant ainsi de passer par le serveur IRC.(cest le client qui dispose de sa)
/// @param cmd ma strucutre de commande que jai recu
/// @return vrai si le msg est un CTCP et commence par DCC
bool Irssi_serv::_is_DCC(Cmd_irssi & cmd)
{
	std::string msg = cmd.get_message();

	// Vérifier si le message est encadré par \x01
	if (_is_CTCP(cmd))
	{
		// Enlever les \x01 et vérifier si ça commence par "DCC "
		std::string clean_msg = msg.substr(1, msg.size() - 2);
		return clean_msg.rfind("DCC ", 0) == 0;  // Vérifie si "DCC " est au début
	}
	return false;
}

/// @return retorune la commande cmd sans les /x01
std::string Irssi_serv::_clean_dcc_cmd(Cmd_irssi & cmd)
{
	std::string msg = cmd.get_message();
	if (msg.length() < 2)
		return (msg);
	return (msg = msg.substr(1, msg.length() - 2), msg);
}

static	std::vector<std::string>	rafinement_des_param_dcc(std::string & param_dcc)
{
	std::vector<std::string> separete_by_space_and_quote = ft_split(param_dcc, " \"\'");
	std::vector<std::string> list_param_dcc;
	std::string				to_add = "";
	bool quote = false;
	for (size_t i = 0; i < separete_by_space_and_quote.size(); i++)
	{
		if (separete_by_space_and_quote[i] == "\"")
			quote = !quote;
		else if (quote || (!quote && separete_by_space_and_quote[i] != " "))
			to_add += separete_by_space_and_quote[i];
		if (!quote && to_add.empty() == false)
		{
			list_param_dcc.push_back(to_add);
			to_add = "";
		}
	}
	if (to_add.empty() == false)
		list_param_dcc.push_back(to_add);
	return (list_param_dcc);
}

bool	Irssi_serv::_ft_dcc(std::string param_dcc, UserHuman & emeteur , ssize_t index_emeteur, ssize_t index_recepteur, pollfd & emeteur_pollfd, UserHuman & recepteur)
{
	std::cout << RED + "DCC REQUEST." + NOCOLOR << std::endl;
	// std::cout << RED + "MSG = \"" << PINK << param_dcc << "\"" << NOCOLOR << std::endl;
	
	std::vector<std::string> list_param_dcc = rafinement_des_param_dcc(param_dcc);
	// std::cout << YELLOW + "RAFINEMENT = " << NOCOLOR << list_param_dcc << std::endl;

	Dcc test(list_param_dcc, index_emeteur, index_recepteur);
	if (test.get_valide_dcc() == false)
		return (send_message(NOTICE(this->get_name(), emeteur.get_nick(), "Error in creation of dcc request."), emeteur_pollfd), false);
	else if (test.get_type() == SEND_DCC)
	{
		if (emeteur.add_request_send_file(test) == false)
		return (send_message(NOTICE(this->get_name(), emeteur.get_nick(), "DCC request already in progress, for the file \"" + test.get_file_name() + "\"."), emeteur_pollfd), false);
		/*TCP CONNEXION*/
		_tcp_conexion(test, emeteur, emeteur_pollfd);
	}
	else if (test.get_type() == GET_DCC)// JE ne pass pas par ici car je n'arive pas a recuoere DCC get
	{// chercher dans le tableaux des requette // faire la transmission de fichier et suprimer du tableau
		Dcc send_request = recepteur.pop_request_dcc(test);
		if (send_request.get_valide_dcc() == false)
			return (send_message(NOTICE(this->get_name(), emeteur.get_nick(), "No DCC request issued by " + recepteur.get_nick() + " for the file \"" + test.get_file_name() + "\""), emeteur_pollfd), false);
		if (_transfer_file(send_request, recepteur, _all_pollfd[recepteur.get_index_pollfd()]) == false)
			return (send_message(NOTICE(this->get_name(), emeteur.get_nick(), "Faillure transfer files"), emeteur_pollfd), false);

	}
	else /*type de dcc comande inreconnue*/
		return (send_message(NOTICE(this->get_name(), emeteur.get_nick(), "unrecognized dcc request."), emeteur_pollfd), false);
	return (true);
}

bool	Irssi_serv::_tcp_conexion(Dcc & send_request, UserHuman & author_send, pollfd & emeteur_pollfd)
{
	std::cout << "Faire la connexion tcp." << std::endl;

	// 1. Créer un socket
	int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_fd < 0) {
		perror("socket");
		send_message(NOTICE(this->get_name(), author_send.get_nick(), "Erreur lors de la création du socket pour DCC."), emeteur_pollfd);
		return false;
	}

	// 2. Préparer la structure d'adresse du serveur
	sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = send_request.get_host();
	serv_addr.sin_port = htons(send_request.get_port()); // Utiliser le port de l'objet DCC

	// 3. Lier le socket à l'adresse et au port spécifiés
	if (bind(listen_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		perror("bind");
		close(listen_fd);
		send_message(NOTICE(this->get_name(), author_send.get_nick(), "Erreur lors de la liaison du socket pour DCC."), emeteur_pollfd);
		return false;
	}

	// 4. Écouter les connexions entrantes
	if (listen(listen_fd, 1) < 0) { // Autoriser une seule connexion entrante pour ce transfert
		perror("listen");
		close(listen_fd);
		send_message(NOTICE(this->get_name(), author_send.get_nick(), "Erreur lors de l'écoute sur le socket pour DCC."), emeteur_pollfd);
		return false;
	}

	std::cout << YELLOW << "DCC SEND : Écoute sur le port " << send_request.get_port() << NOCOLOR << std::endl;

	// Stocker le descripteur de fichier du socket d'écoute dans l'objet Dcc afin que _transfer_file puisse l'utiliser.
	// Vous devrez ajouter une variable membre et des méthodes setter/getter dans la classe Dcc pour cela.
	// Exemple (ajouter à Dcc.h) :
	// private:
	//     int _listen_fd;
	// public:
	//     void set_listen_fd(int fd) { _listen_fd = fd; }
	//     int get_listen_fd() const { return _listen_fd; }
	//
	// Et dans Dcc.cpp (le constructeur pourrait l'initialiser à -1) :
	// Dcc::Dcc(...) : ..., _listen_fd(-1) {}

	// Ensuite, dans cette fonction :
	// send_request.set_listen_fd(listen_fd);

	// Pour simplifier, nous supposerons que vous avez ajouté cela à la classe Dcc.

	return true;
}


bool	Irssi_serv::_transfer_file(Dcc & send_request, UserHuman & author_send, pollfd & author_send_pollfd)
{

	std::cout << "Faire le transfert de fichier." << std::endl;

	// 1. Récupérer le descripteur de fichier du socket d'écoute depuis l'objet Dcc
	// En supposant que vous avez implémenté get_listen_fd() dans la classe Dcc
	int listen_fd = send_request.get_listen_fd() ; // Décommentez cette ligne après avoir ajouté la méthode

	// Espace réservé si vous ne l'avez pas encore ajouté :
	int temp_listen_fd = -1; // Vous devrez stocker et récupérer cela correctement.
	listen_fd = temp_listen_fd;

	if (listen_fd == -1) {
		send_message(NOTICE(this->get_name(), author_send.get_nick(), "Erreur : Socket d'écoute introuvable pour DCC."), author_send_pollfd);
		return false;
	}

	// 2. Accepter la connexion entrante du destinataire
	sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	int client_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &client_len);
	if (client_fd < 0) {
		perror("accept");
		send_message(NOTICE(this->get_name(), author_send.get_nick(), "Erreur lors de l'acceptation de la connexion DCC."), author_send_pollfd);
		close(listen_fd); // Fermer le socket d'écoute
		return false;
	}
	close(listen_fd); // Fermer le socket d'écoute après avoir accepté la connexion

	std::cout << YELLOW << "DCC SEND : Connexion acceptée du destinataire." << NOCOLOR << std::endl;

	// 3. Ouvrir le fichier à envoyer
	std::ifstream file(send_request.get_file_name().c_str(), std::ios::binary | std::ios::ate);    // std::ifstream file(send_request.get_file_name().c_str(), std::ios::binary);
	if (!file.is_open()) {
		std::cerr << "Erreur lors de l'ouverture du fichier : " << send_request.get_file_name() << std::endl;
		send_message(NOTICE(this->get_name(), author_send.get_nick(), "Erreur lors de l'ouverture du fichier \"" + send_request.get_file_name() + "\" pour DCC."), author_send_pollfd);
		close(client_fd);
		return false;
	}

	// 4. Envoyer les données du fichier
	char buffer[4096]; // Choisir une taille de tampon appropriée
	// size_t bytes_read;
	while (file.read(buffer, sizeof(buffer))) {
		ssize_t bytes_sent = send(client_fd, buffer, file.gcount(), 0);
		if (bytes_sent < 0) {
			perror("send");
			send_message(NOTICE(this->get_name(), author_send.get_nick(), "Erreur lors de l'envoi des données du fichier pour DCC."), author_send_pollfd);
			file.close();
			close(client_fd);
			return false;
		}
	}

	// Gérer les données restantes
	if (file.gcount() > 0) {
		ssize_t bytes_sent = send(client_fd, buffer, file.gcount(), 0);
		if (bytes_sent < 0) {
			perror("send");
			send_message(NOTICE(this->get_name(), author_send.get_nick(), "Erreur lors de l'envoi des données de fichier restantes pour DCC."), author_send_pollfd);
			file.close();
			close(client_fd);
			return false;
		}
	}

	// 5. Fermer le fichier et la connexion
	file.close();
	close(client_fd);

	std::cout << YELLOW << "DCC SEND : Transfert de fichier terminé." << NOCOLOR << std::endl;
	return (true);
}
