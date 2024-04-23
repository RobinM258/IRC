#include "Command.hpp"

Kick::Kick( Server *serv ): Command(serv) { }
Kick::~Kick( void ) { }

void Kick::execute( Client *client, std::string args ) {
    Channel *chan = _serv->getChannel(args);
    Client *target = chan->searchMember(args.substr(0, args.find(' ')));
    /* trouver un moyen d avoir le channel ou a ete ecrit la commande  et par qui */
    std::string motif = args.substr(args.find(' '),  args.find('\n'));
    if (chan->searchModerator(client->getNickName()) != NULL)
    {
        /* on recherche si le nickname dans arg existe dans le channel*/
        if (target == chan->searchMember(args) != NULL)
        {
            chan->removeMember(target);
            chan->broadcast(CLIENTKICK(client->getNickName(), chan->getName(), motif));
        }
        else
            /* si le client donne en args n'existe pas */
            client->sendReply(CLIENTNOTINCHANNEL(client->getNickName(), chan->getName()));
    }
}
