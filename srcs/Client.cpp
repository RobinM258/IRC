#include "Client.hpp"

Client::Client(void) {
    std::cout << "Client: <unamed>" << GREEN << " created" << RESET << std::endl;
}

Client::Client( int fd ): _socketFd(fd), _state(NONE) {
    std::cout << "Client: <unamed>" << GREEN << " created" << RESET << std::endl;
}

Client::Client(std::string realname, std::string nickname, std::string username, int socketfd): _socketFd(socketfd), _realname(realname), _username(username), _nickname(nickname){
    std::cout << "Client: " << _nickname << GREEN << " created" << RESET << std::endl;
}

Client::~Client(void) {
    close(this->_socketFd);
    std::cout << "Client: " << _nickname << RED << " deleted" << RESET << std::endl;
}

Client &Client::operator=( const Client & ref)
{
    this->_realname = ref._realname;
    this->_username = ref._username;
    this-> _nickname = ref._nickname;
    return *this;
}

std::string Client::getNickName(void){
    return this->_nickname;
}

std::string Client::getUsername(void){
    return this->_username;
}

std::string Client::getRealname(void){
    return this->_realname;
}

int Client::getSocketFd(void){
    return this->_socketFd;
}

int Client::getState( void ) {
    return this->_state;
}

void Client::setNickName(std::string name){
    this->_nickname = name;
}

void Client::setUsername(std::string username){
    this->_username = username;
}

void Client::setRealname(std::string realname){
    this->_realname = realname;
}

void    Client::setState( int state ) {
    this->_state = state;
}

/* envoie un message au client (genre PRIVMSG)*/
void    Client::sendMsg( std::string msg ) {
    msg += "\r\n";
    send(this->_socketFd, msg.data(), msg.size(), 0);
}

/* sendReply = reponse au sender (genre JOIN)*/
void    Client::sendReply( std::string msg ) {
    msg = ":ft_irc " + msg + "\r\n";
    send(this->_socketFd, msg.data(), msg.size(), 0);
}

/* fonction pour afficher un client (debug) */
std::ostream &operator<<(std::ostream &os, Client &ref ) {
    os << "nn: -" << ref.getNickName() << "-" << std::endl;
    os << "un: -" << ref.getUsername() << "-" << std::endl;
    os << "rn: -" << ref.getRealname() << "-" << std::endl;
    return os;
}