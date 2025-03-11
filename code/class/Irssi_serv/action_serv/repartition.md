TO DO

YASSINE
    - Faire la diff entre irssi et nc + tester avec nc + tester dans le desordre  les cmd
    - Bonus file fd (vir la commande dcc send et get etcJ)

SAMIRA
    - Faire la diff entre irssi et nc + tester avec nc + tester dans le desordre les cmd
    -   BOT
            no n-word D:

RESTE:
    - faire le mdp verifier (cmd pass a faire) <- ON 

NICK <============ FAIT (sam)
    - caracteres speciaux interdits <- SAM
    ->modifications => nikc_user = cmd_arg[0] au lieu de asterix (asterix = char interdit)
     fonction check err nick ajouté

WHOIS <================ FAIT (sam)
 RPL_WHOISCHANNELS 
 (WHOREPLY) IPv6 addresses such as "::1" are prefixed with a zero ('0', 0x30) to ensure this 

WHOWAS <= FAIT (SAM)
en reponse a whois unknown nick, whowas est envoyé
 ->on ne stock pas d'historique de nick est whowas n'est pas mendatory
    donc je renvoie juste endofwhowas
