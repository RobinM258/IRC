#include "Command.hpp"

Join::Join( Server *serv ): Command(serv) { }
Join::~Join( void ) { }

/* le client rejoind un channel ou le creer si il n'existe pas*/
void Join::execute(Client *client, std::string args)
{
    Channel *chan;

    /* faire un truc si args est vide */
    if (args.empty())
        return ;
    /* creer le channel si il n'existe pas */
    if ((chan = _serv->getChannel(args)) == NULL) 
        chan = _serv->createChannel(args);
    chan->addMember(client);
    chan->addModerator(client);
    std::string clientList;

    std::vector<Client *>::iterator it;
    std::vector<Client *>           memb = chan->getMembers();
    /* creer le string de la liste des users */
    for (it = memb.begin(); it != memb.end(); ++it) {
        clientList = clientList + (*it)->getNickName();
        clientList = clientList + ' ';
    }

    //std::cout << "°" << clientList << "°" << std::endl;
    //std::cout << "(" << client->getNickName() << ")" << std::endl;
    /* on envoie les reponses au client */
    client->sendReply(NO_TOPIC(client->getNickName(), chan->getName()));
    client->sendReply(CLIENTLIST(clientList, client->getNickName(), chan->getName()));
    client->sendReply(ENDOF_CLIENTLIST(client->getNickName(), chan->getName()));
    client->sendReply(WELCOMECHAN_DLC(chan->getName()));
    /* ajoute le nouveau client au channel */
    chan->broadcast(JOIN_RPL(client->getNickName(), chan->getName()));
}