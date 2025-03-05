/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reponse_numeric_serv.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:17:09 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/05 19:16:33 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define CRLF "\r\n"

// SPECIAL MSG
#define NOTICE(server_name, nick, msg) (":" + server_name + " NOTICE " + nick + " :*** " + msg + CRLF)
#define SELF_QUIT_MSG(msg) ("QUIT :" + msg + CRLF)
#define OTHER_QUIT_MSG(nick, username, hostname, msg) (":" + nick + "!~" + username + "@" + hostname + " QUIT :" + msg + CRLF)
#define PRIVMSG_REP(nick, username, hostname, target, msg) (":" + nick + "!~" + username + "@" + hostname + " PRIVMSG " + target + " :" + msg + CRLF)
#define NICKMASK(nick, hostname, ip) (nick + "!~" + hostname + "@" + ip)
// RPL (Réponses numériques)

// RPL_WELCOME
#define RPL_WELCOME(server_name, nick, user, host_ip) (":" + server_name + " 001 " + nick + " :Welcome to the Internet Relay Network " + nick + "!" + user + "@" + host_ip + CRLF)
// RPL_YOURHOST 
#define RPL_YOURHOST(server_name, nick, version) (":" + server_name + " 002 " + nick + " :Your host is " + server_name + ", running version " + version + CRLF)
//RPL_USER (custoisé par sam pour reponse de cmd user)
#define RPL_USER(server_name, nick, username, realname) (":" + server_name + " 003 " + nick + " :you are now registered as " + username + ", " + realname + CRLF)
//RPL_MODE
// #define RPL_MODE(server_name, nick, command, m) (":" + server_name + )
//RPL_WHOISUSER
#define RPL_WHOISUSER(server_name, nick, nickname, username, host, realname) (":" + server_name + " 311 " + nick + " " + nickname + " " + username + " " + host + " * :" + realname + CRLF)
// #RPL_ENDOFWHOIS
#define RPL_ENDOFWHOIS(server_name, nick) (":" + server_name + " 318 " + nick + " :End of /WHOIS" + CRLF)
// #RPL_JOIN
#define RPL_JOIN(nick, hostname, ip, channel_name) (":" + nick + "!~" + hostname + "@" + ip + " JOIN :" + channel_name + CRLF)
// #RPL_JOIN_K (avec clé)
#define RPL_JOIN_K(nick, hostname, ip, channel_name, key) (":" + nick + "!~" + hostname + "@" + ip + " JOIN :" + channel_name + key + CRLF)
// #RPL_TOPIC
#define RPL_TOPIC(server_name, nick, channel_name, topic) (":" + server_name + " 332 " + nick + " " + channel_name + " :" + topic + CRLF)
// #RPL_NAMEREPLY
#define RPL_NAMEREPLY(server_name, nick, channel_name, list_user) (":" + server_name + " 353 " + nick + " = " + channel_name + " :" + list_user + CRLF)
// #RPL_ENDOFNAMES
#define RPL_ENDOFNAMES(server_name, nick, channel_name) (":" + server_name + " 366 " + nick + " " + channel_name + " :End of /NAMES list" + CRLF)
// RPL_CHANNELMODEIS
#define RPL_CHANNELMODEIS(server_name, nick, channel_name, list_mode) (":" + server_name + " 324 " + nick + " " + channel_name + " +" + list_mode + CRLF)
// RPL_UMODEIS
# define RPL_UMODEIS(server_name, nick, list_mode) (":" + server_name + " 221 " + nick + " +" + list_mode + CRLF)
// RPL_CHANONINVITE
#define RPL_CHANONINVITE(nick, hostname, ip, channel_name, arg) (":" + nick + "!~" + hostname + "@" + ip + " MODE " + channel_name + " " + arg + CRLF)
// RPL_INVISIBLE
#define RPL_INVISIBLE(nick, target, arg) (":" + nick + " MODE " + target + " :" + arg)

//--------------------- ERR (Erreurs numériques)
// ERR_NOSUCHNICK
#define ERR_NOSUCHNICK(server_name, nick) (":" + server_name + " 401 " + nick + ": No such nick" + CRLF)
// ERR_NOSUCHCHANNEL
#define ERR_NOSUCHCHANNEL(server_name, nick, target) (":" + server_name + " 403 " + nick + " " + target + " :No such channel" + CRLF)
// ERR_CANNOTSENDTOCHAN
#define ERR_CANNOTSENDTOCHAN(server_name, channelname) (":" + server_name + " 404 " + channelname + " :Cannot send to channel" + CRLF)
// ERR_NOORIGIN
#define ERR_NOORIGIN(server_name, nickname) (":" + server_name + " 409 " + nickname + " :No origin specified" + CRLF)
// ERR_INVALIDCAPCMD
#define ERR_INVALIDCAPCMD(server_name, subcommand) (":" + server_name + " 410 " + subcommand + " :Invalid CAP command" + CRLF)
// ERR_UNKNOWNCOMMAND
#define ERR_UNKNOWNCOMMAND(server_name, command) (":" + server_name + " 421 " + command + " :Unknown command \"" + command + "\"" + CRLF)
// ERR_NONICKNAMEGIVEN
#define ERR_NONICKNAMEGIVEN(server_name) (":" + server_name + " 431 :No nickname given" + CRLF)
// ERR_ERRONEUSNI CKNAME
#define ERR_ERRONEUSNICKNAME(server_name, nickname) (":" + server_name + " 432 " + nickname + ":Erroneous nickname" + CRLF)
// ERR_NICKNAMEINUSE
#define ERR_NICKNAMEINUSE(server_name, nickname, new_nickname) (":" + server_name + " 433 " + nickname + ": " + new_nickname + " Nickname is already in use" + CRLF)
// ERR_NEEDMOREPARAMS
#define ERR_NEEDMOREPARAMS(server_name, nickname, command) (":"+ server_name + " 461 " + nickname + " " + command + " :Not enough parameters" + CRLF)
// ERR_ALREADYREGISTERED
#define ERR_ALREADYREGISTRED(server_name, command) (":" + server_name + " 462 " + command + " :Unauthorized command (already registered)" + CRLF)
// ERR_KEYSET
#define ERR_KEYSET(server_name, nick, channel_name) (":" + server_name + " 467 " + nick + " " + channel_name + " :Channel key already set" + CRLF)
// ERR_CHANNELISFULL
#define ERR_CHANNELISFULL(server_name, nick, channel_name) (":" + server_name + " 471 " + nick + " " + channel_name + " :Cannot join channel (+l)" + CRLF)
// ERR_UNKNOWNMODE 
#define ERR__UNKNOWNMODE(server_name, nick, character) (":" + server_name + " 472 " + nick + "" + character + " :is unknown mode char to me" + CRLF)
// ERR_INVITEONLYCHAN
#define ERR_INVITEONLYCHAN(server_name, nick, channel_name) (":" + server_name + " 473 " + nick + " "  + channel_name + " :Cannot join channel (+i)" + CRLF)
// ERR_BANNEDFROMCHAN
#define ERR_BANNEDFROMCHAN(server_name, nick, channel_name) (":" + server_name + " 474 " + nick + " " + channel_name + " :cannot join channel (+b)" + CRLF)
// ERR_BADCHANNELKEY
#define ERR_BADCHANNELKEY(server_name, nick, channel_name) (":" + server_name + " 475 " + nick + " " + channel_name + " :Canot join channel (+k)" + CRLF)
// ERR_NOPRIVILEGES
#define ERR_NOPRIVILEGE(server_name, nick, command) (":" + server_name + " 481 " + nick + " " + command + " :Permission Denied- You're not an IRC operator" + CRLF)
// ERR_CHANOPRIVSNEEDED
#define ERR_CHANOPRIVSNEEDED(server_name, nick, channel_name) (":" + server_name + " 482 " + nick + " " + channel_name + " :You're not channel operator" + CRLF)// ERR_USERDONTMATCH
// ERR_USERDONTMATCH
#define ERR_USERSDONTMATCH(server_name, nick) (":" + server_name + " 502 " + nick + " :Cant change/view mode for other users" + CRLF)
 
//ERR_INVALIDMODEPARAM
// #define ERR_INVALIDMODEPARM() j'arrive pas a voir comment il fonctionne
///////////////////////////////////////////////////////////////////// 

// RPL (Réponses numériques)
// RPL_JOINMSG
#define RPL_JOINMSG(hostname, ipaddress, channelname) (":" + hostname + "@" + ipaddress + " JOIN #" + channelname + CRLF)
// RPL_NAMREPL
#define RPL_NAMREPLY(nickname, channelname, clientslist) (": 353 " + nickname + " @ #" + channelname + " :" + clientslist + CRLF)
// RPL_TOPICIS
#define RPL_TOPICIS(nickname, channelname, topic) (": 332 " + nickname + " #" +channelname + " :" + topic + "\r\n")
// // RPL_ENDOFNAMES
// #define RPL_ENDOFNAMES(nickname, channelname) (": 366 " + nickname + " #" + channelname + " :END of /NAMES list" + CRLF)
// RPL_AWAY
#define RPL_AWAY(nickname, awayMessage) (": 301 " + nickname + " :" + awayMessage + CRLF)
// RPL_BANLIST
#define RPL_BANLIST(nickname, channelname, bannedUser) (": 367 " + nickname + " #" + channelname + " " + bannedUser + CRLF)
// RPL_ENDOFBANLIST
#define RPL_ENDOFBANLIST(nickname, channelname) (": 368 " + nickname + " #" + channelname + " :End of channel ban list" + CRLF)
// RPL_ENDOFEXCEPTLIST
#define RPL_ENDOFEXCEPTLIST(nickname, channelname) (": 349 " + nickname + " #" + channelname + " :End of exception list" + CRLF)
// RPL_ENDOFINVITELIST
#define RPL_ENDOFINVITELIST(nickname, channelname) (": 347 " + nickname + " #" + channelname + " :End of invite list" + CRLF)
// RPL_EXCEPTLIST
#define RPL_EXCEPTLIST(nickname, channelname, exceptedUser) (": 348 " + nickname + " #" + channelname + " " + exceptedUser + CRLF)
// RPL_INVITELIST
#define RPL_INVITELIST(nickname, channelname, invitedUser) (": 346 " + nickname + " #" + channelname + " " + invitedUser + CRLF)
// RPL_INVITING
#define RPL_INVITING(nickname, channelname, invitedUser) (": 341 " + nickname + " " + invitedUser + " #" + channelname + CRLF)
// RPL_CHANNELMODES
#define RPL_CHANNELMODES(nickname, channelname, modes) (": 324 " + nickname + " #" + channelname + " " + modes + CRLF)
// RPL_NOTOPIC
#define RPL_NOTOPIC(nickname, channelname) (": 331 " + nickname + " #" + channelname + " :No topic is set" + CRLF)
// RPL_TOPIC
// #define RPL_TOPIC(nickname, channelname, topic) (": 332 " + nickname + " #" + channelname + " :" + topic + CRLF)
// RPL_TOPICWHOTIME
#define RPL_TOPICWHOTIME(nickname, channelname, author, timestamp) (": 333 " + nickname + " #" + channelname + " " + author + " " + timestamp + CRLF)
// RPL_YOUREOPER
#define RPL_YOUREOPER (std::string(": 381 :You are now an IRC operator")) + CRLF
// RPL_UMODEIS
// #define RPL_UMODEIS(nickname, mode) (std::string(": 221 ") + nickname + " " + mode + CRLF)
// 	RPL_CHANGEMODE
#define RPL_CHANGEMODE(hostname, channelname, mode, arguments) (":" + hostname + " MODE #" + channelname + " " + mode + " " + arguments + CRLF)

// PRIVMSG
#define PRIVMSG(nick, user, host_ip, recipient, message) (":" + nick + "!~" + user + "@" + host_ip + " PRIVMSG " + recipient + " " + message + CRLF)

// ERR (Erreurs numériques)

// ERR_ALREADYREGISTRED
// #define ERR_ALREADYREGISTRED(command) (command + " :Unauthorized command (already registered)" + CRLF)
// ERR_BADCHANMASK
#define ERR_BADCHANMASK(nickname, channelname) (": 476 " + nickname + " #" + channelname + " :Bad Channel Mask" + CRLF)
// // ERR_BADCHANNELKEY
// #define ERR_BADCHANNELKEY(nickname, channelname) (": 475 " + nickname + " #" + channelname + " :Cannot join channel (+k)" + CRLF)
// ERR_BANNEDFROMCHAN
// #define ERR_BANNEDFROMCHAN(nickname, channelname) (": 474 " + nickname + " #" + channelname + " :You are banned from this channel" + CRLF)
// // ERR_CHANNELISFULL
// #define ERR_CHANNELISFULL(nickname, channelname) (": 471 " + nickname + " #" + channelname + " :Cannot join channel (+l)" + CRLF)
// ERR_CHANOPRIVSNEEDED
// #define ERR_CHANOPRIVSNEEDED(nickname, channelname) (": 482 " + nickname + " #" + channelname + " :You're not channel operator" + CRLF)
// ERR_INVITEONLYCHAN
// #define ERR_INVITEONLYCHAN(nickname, channelname) (": 473 " + nickname + " #" + channelname + " :Cannot join channel (+i)" + CRLF)
// // ERR_KEYSET
// #define ERR_KEYSET(channelname) (": 467 #" + channelname + " :Channel key already set" + CRLF)
// ERR_NEEDMODEPARM
#define ERR_NEEDMODEPARM(channelname, mode) (": 696 #" + channelname + " * You must specify a parameter for the key mode " + mode + CRLF)
// ERR_INVALIDMODEPARM
// #define ERR_INVALIDMODEPARM(channelname, mode) ": 696 #" + channelname + " Invalid mode parameter. " + mode + CRLF
// ERR_NICKCOLLISION
#define ERR_NICKCOLLISION(nickname) (": 436 " + nickname + " :Nickname collision KILL" + CRLF)
// ERR_NOCHANMODES
#define ERR_NOCHANMODES(nickname, channelname) (": 477 " + nickname + " #" + channelname + " :Channel doesn't support modes" + CRLF)
// ERR_NOOPERHOST
#define ERR_NOOPERHOST(nickname) (": 491 " + nickname + " :No O-lines for your host" + CRLF)
// ERR_NORECIPIENT
#define ERR_NORECIPIENT(command) (": 411 :No recipient given (" + command + ")" + CRLF)
// ERR_NOTEXTTOSEND
#define ERR_NOTEXTTOSEND (std::string(": 412 :No text to send")) + CRLF
// ERR_NOTONCHANNEL
#define ERR_NOTONCHANNEL(nickname, channelname) (": 442 " + nickname + " #" + channelname + " :You're not on that channel" + CRLF)
// ERR_PASSWDMISMATCH
#define ERR_PASSWDMISMATCH (std::string(":464 :Password incorrect") + CRLF)
// ERR_RESTRICTED
#define ERR_RESTRICTED(nickname) (": 484 " + nickname + " :Your connection is restricted!" + CRLF)
// ERR_TOOMANYCHANNELS
#define ERR_TOOMANYCHANNELS(nickname, channelname) (": 405 " + nickname + " #" + channelname + " :You have joined too many channels" + CRLF)
// ERR_TOOMANYTARGETS
#define ERR_TOOMANYTARGETS(nickname, target) (": 407 " + nickname + " " + target + " :Too many recipients" + CRLF)
// ERR_UNAVAILRESOURCE
#define ERR_UNAVAILRESOURCE(nickname, resource) (": 437 " + nickname + " " + resource + " :Nick/channel is temporarily unavailable" + CRLF)
// ERR_UNKNOWNMODE
#define ERR_UNKNOWNMODE(nickname, mode) (": 472 " + nickname + " " + mode + " :is unknown mode char to me" + CRLF)
// ERR_USERNOTINCHANNEL
#define ERR_USERNOTINCHANNEL(nickname, target_nick, channelname) (": 441 " + nickname + " " + target_nick + " #" + channelname + " :They aren't on that channel" + CRLF)
// ERR_USERONCHANNEL
#define ERR_USERONCHANNEL(nickname, target_nick, channelname) (": 443 " + nickname + " " + target_nick + " #" + channelname + " :is already on channel" + CRLF)
// ERR_WILDTOPLEVEL
#define ERR_WILDTOPLEVEL(nickname, mask) (": 414 " + nickname + " " + mask + " :Wildcard in toplevel domain" + CRLF)