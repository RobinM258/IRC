#include "Command.hpp"

Part::Part( Server *serv ): Command(serv) { }
Part::~Part( void ) { }

/* bro leave le channel */
void Part::execute( Client *client, std::string args ) {
    Channel *chan = NULL;

    /* faire un truc si args est vide */
    if (args.empty())
        return ;
    /* enleve le client du channel*/
    chan->removeMember(client);
    /*  envois un message si il y a des args apres la commande*/
    if (args.data())
        client->sendReply(args.data());
    chan->broadcast(LEAVE_RPL(client->getNickName(), chan->getName()));
}