/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2026/02/12 11:06:56 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "IRCServ.hpp"
#include <cerrno>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <map>

using std::strerror;

IRCServ::IRCServ() : listening_socket(0), epoll_fd(0), server_name(SERVER_NAME) {}

IRCServ::~IRCServ()
{
	close(epoll_fd);
	close(listening_socket);
}

IRCServ::IRCServ(int listening_port, std::string password) : listening_socket(0), clientPassword(password), epoll_fd(0)
{
	server_name = SERVER_NAME;
		listening_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (listening_socket == -1)
		throw std::runtime_error(std::string("socket: ")
		+ strerror(errno));

	int opt = 1;
	if (setsockopt(listening_socket, SOL_SOCKET, SO_REUSEADDR,
		&opt, sizeof(opt)) == -1)
		throw std::runtime_error(std::string("Server constructor: ")
		+ strerror(errno));

	struct sockaddr_in server_addr;
	std::memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(listening_port);

	if (bind(listening_socket, (struct sockaddr *)&server_addr,
		sizeof(server_addr)) == -1)
		throw std::runtime_error(std::string("Bind: ")
		+ std::strerror(errno));

	if (listen(listening_socket, 10) == -1)
		throw std::runtime_error(std::string("Listen: ")
		+ strerror(errno));

	if (fcntl(listening_socket, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error(std::string("Fcntl: ")
		+ strerror(errno));

	setEpollFd(epoll_create1(EPOLL_CLOEXEC));
	if (epoll_fd == -1)
		throw std::runtime_error(std::string("Epoll_create1: ")
		+ strerror(errno));

	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.fd = listening_socket;
	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listening_socket, &ev) == -1)
		close(epoll_fd);

	std::cout << "🎧 Servidor escuchando en puerto " << listening_port
	<< "..." << std::endl;
	return;
}






int IRCServ::getListeningSocket() const{
	return listening_socket;
}
void IRCServ::setListeningSocket(int socket) {
	listening_socket = socket;
}
void IRCServ::setClientPassword(std::string& password) {
	clientPassword = password;
}
bool IRCServ::checkClientPassword(std::string& password) const {
	return password == clientPassword;
}
int IRCServ::getEpollFd() const{
	return epoll_fd;
}
void IRCServ::setEpollFd(int fd) {
	epoll_fd = fd;
}
const std::map<int, IRCClient>& IRCServ::getClients() const {
return clients;
}
std::map<int, IRCClient>& IRCServ::getClients() {
	return clients;
}
void IRCServ::setClients(const std::map<int, IRCClient>& newClients) {
	clients = newClients;
}
struct epoll_event* IRCServ::getEvents() {
	return events;
}
const struct epoll_event* IRCServ::getEvents() const {
	return events;
}
void IRCServ::setEvent(int fd, epoll_event event) {
	events[fd] = event;
}
void IRCServ::addToNicks(const std::string& n, int fd)
{
		nicks[n] = fd;
}
void IRCServ::rmFromNicks(const std::string& n)
{
    nicks.erase(n);
}
bool IRCServ::nickIsUnique(const std::string& n)
{
    return (nicks.find(n) == nicks.end());
}





void IRCServ::run()
{
	while (true)
	{
		int ready = epoll_wait(epoll_fd, events, 16, -1);
		if (ready == -1)
		{
			if (errno == EINTR)
				continue;
			throw std::runtime_error(std::string("Epoll_wait: ")
			+ strerror(errno));
		}

		for (int i = 0; i < ready; ++i)
		{
			int fd = events[i].data.fd;
			if (fd == listening_socket)
				accept_new_connection();
			else
			{
				if (events[i].events & EPOLLOUT)
					this->queue_and_send(fd, ""); 
				if (read_from_client(clients[fd]))
					close_client(fd);
				process_client_buffer(fd);
			}
		}
	}
}
 
void IRCServ::close_client(int fd)
{
    // 1. Eliminar del epoll
    if (epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, NULL) == -1)
        std::cerr << "Error eliminando fd de epoll: " << strerror(errno) << std::endl;

    std::map<int, IRCClient>::iterator client_it = clients.find(fd);
    if (client_it != clients.end())
    {
        std::string nick = client_it->second.getNick();
        // 3. Bucle que itera por los canales y borra el usuario de todos ellos
        std::map<const std::string, IRCChannel>::iterator ch_it = channels.begin();
        while (ch_it != channels.end())
        {
            ch_it->second.delUser(nick);
            // Lógica estándar de IRC: Si el canal no tiene más usuarios, se borra el canal
            if (ch_it->second.getNumberOfUsers() == 0)
            {
                std::map<const std::string, IRCChannel>::iterator to_erase = ch_it;
                ++ch_it;
                channels.erase(to_erase);
            }
            else
                ++ch_it;
        }
        // 4. Limpieza de los mapas globales del servidor
        nicks.erase(nick);
        clients.erase(client_it);
    }
    // 5. Cierre físico del socket
    close(fd);
    std::cout << "Cliente [" << fd << "] desconectado" << std::endl;
}

// Acepta una nueva conexión entrante en listening_socket.
// - Configura el socket cliente en non-blocking.
// - Registra el cliente en epoll con EPOLLIN | EPOLLET.
// - Inicializa el buffer del cliente en client_buffers.
// Devuelve 0 en éxito, -1 en error (y no registra el cliente).
void IRCServ::accept_new_connection()
{
		struct sockaddr_in client_addr;
		socklen_t addr_len = sizeof(client_addr);

		int fd = accept(listening_socket, (struct sockaddr *)&client_addr, &addr_len);
		if (fd == -1)
				throw std::runtime_error(std::string("accept: ") + strerror(errno));

		unsigned char *ip = (unsigned char *)&client_addr.sin_addr.s_addr;
		std::ostringstream oss;
		oss << (int)ip[0] << "." << (int)ip[1] << "." << (int)ip[2] << "." << (int)ip[3];
		std::string host = oss.str();

		if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1) {
				close(fd);
				throw std::runtime_error(std::string("set nonblocking client: ") + strerror(errno));
		}

		struct epoll_event client_ev;
		client_ev.events = EPOLLIN | EPOLLET;
		client_ev.data.fd = fd;
		if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &client_ev) == -1){
				close(fd);
				throw std::runtime_error(std::string("epoll_ctl add client: ") + strerror(errno));
		}

		clients[fd] = IRCClient(fd);
		clients[fd].setHost(host);

		std::cout << "Nueva conexión: fd=" << fd << " host=" << host << std::endl;
}

// Lee todo lo disponible en modo non-blocking (EPOLLET) desde fd.
// - Añade los bytes leídos al buffer del cliente en client_buffers.
// - Si no está cerrado devuelve false.
bool IRCServ::read_from_client(IRCClient & client)
{
	char tmp[4096];

	while (true)
	{
		ssize_t n = recv(client.getFd(), tmp, sizeof(tmp), 0);
		if (n > 0)
			client.addToIbuffer(tmp, n);

		else if (client.getIbuffer().size() > 4000) {
			std::cerr << "Client flooding, disconnecting..." << std::endl;
			close_client(client.getFd());
			return true;
		}
		else if (n == 0)
			return true;
		else
		{
			// el hecho de que errno haya sido llenado con estos numeros
			//    por recv() significa que llegamos al final del buffer
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				return false;
			else if (errno == EINTR)
				continue;
			else
				throw std::runtime_error(std::string("recv(): ")
				+ strerror(errno));
		}
	}
}

void IRCServ::process_client_buffer(int fd)
{
		std::string &buf = clients[fd].getIbuffer();
		while (true)
		{
				if (clients.find(fd) == clients.end())
					return;
				size_t pos = buf.find("\r\n");
				size_t terminator_len = 2;
				if (pos == std::string::npos) {
						pos = buf.find('\n');
						terminator_len = 1;
				}
				if (pos == std::string::npos) {
						if (buf.size() > 512)
								throw std::runtime_error("Line too long");
						break; 
				}
				std::string raw_line = buf.substr(0, pos);
				buf.erase(0, pos + terminator_len);
				if (raw_line.size() > 510)
						raw_line = raw_line.substr(0, 510);

				IRCMessage ircMsg;
				try {
						ircMsg = IRCMessage::parse(raw_line);
						std::cout << fd << ": " << ircMsg.toString() << std::endl;
				} catch (...) {
						std::cerr << fd << ": Error parsing => " << raw_line << std::endl;
				}
				answer_command(ircMsg, fd);
		}
}

std::string IRCServ::getServerName(void) const{
	return (server_name);
}

void	IRCServ::send_ping_to_client(int fd){
	std::ostringstream msg;
	
	if (clients.count(fd)){
		msg << "PING :" << server_name << "\r\n";
		queue_and_send(fd, msg.str());
	}
}

void	IRCServ::check_clients_timeout(void){
	time_t	now  = std::time(NULL);
	
	for (std::map<int, IRCClient>::iterator it = clients.begin(); it != clients.end();){ //note* below because of not ++it here.
		int 			fd = it->first;
		IRCClient &client = it->second;
		time_t		last = client.getLastActivity();
		bool			ping_sent = client.get_server_ping_sent();
		
		/*If client is TIMEOUT seconds without saying anything server send a PING
		only should send it once because with epoll can saturate it during those extra 60 sec.*/
		if (now - last > TIMEOUT && now - last <= TIMEOUT + 60 && !ping_sent){
			IRCServ::send_ping_to_client(fd);
			client.set_server_ping_sent(); //set to true
			++it;
		}

		//If it didnt reply to PING with PONG in 60 seconds more we kick it
		/*note*: If the ++it would be only in the for and not in each 'if' as it is now,
		when we remove a client, and we make in the for the ++it, it would produce a segfaul
		We cannot have only an ++it here in that case and the for one, because we would
		jump over an valid one making it = it + 2. */
		
		else if (now - last > TIMEOUT + 60){
			std::ostringstream msg;
			msg << "ERROR :Closign Link: Ping timeout: "
			<< (TIMEOUT + 60) << "seconds\r\n";
			queue_and_send(fd, msg.str());
			++it; //note* above
			close_client(fd); //hay que eliminar el nick y canales en la funcion
		}
		else
			++it;
	}
}

//privmsg
const std::map<const std::string, int>&	IRCServ::getNicks(void) const{
	return (nicks);
}

//privmsg
const std::map<const string, IRCChannel>& IRCServ::getChannels(void) const{
	return (channels);
}


void IRCServ::answer_command(IRCMessage &msg, int fd)
{
    switch (msg.getCommand())
    {
        // === OBLIGATORIOS por subject ===
        // case CMD_KICK:     answer_kick(msg, fd);     break;
        // case CMD_INVITE:   answer_invite(msg, fd);   break;
        // case CMD_TOPIC:    answer_topic(msg, fd);    break;
        case CMD_MODE:     answer_mode(msg, fd);     break;
        case CMD_PASS:     answer_pass(msg, fd);     break;
        case CMD_NICK:     answer_nick(msg, fd);     break;
        case CMD_USER:     answer_user(msg, fd);     break;
        case CMD_QUIT:     answer_quit(msg, fd);     break;

        // // === extras ===
        case CMD_JOIN:     answer_join(msg, fd);     break;
        case CMD_PART:     answer_part(msg, fd);     break;
        case CMD_PRIVMSG:  answer_privmsg(msg, fd);  break;
        case CMD_NOTICE:   answer_notice(msg, fd);   break;
        case CMD_PING:     answer_ping(msg, fd);     break;
        case CMD_PONG:     answer_pong(msg, fd);     break;

        default:
            // (???) Enviar error ERR_UNKNOWNCOMMAND (421) al cliente
            break;
    }
}



