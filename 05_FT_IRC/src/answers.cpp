#include "IRCServ.hpp"

// void IRCServ::answer_kick(IRCMessage & msg, int fd) {}

// void IRCServ::answer_invite(IRCMessage & msg, int fd) {}

// void IRCServ::answer_topic(IRCMessage & msg, int fd) {}

// void IRCServ::answer_mode(IRCMessage & msg, int fd) {}

// void IRCServ::answer_quit(IRCMessage & msg, int fd) {}

// void IRCServ::answer_join(IRCMessage & msg, int fd) {}

// void IRCServ::answer_part(IRCMessage & msg, int fd) {}

// void IRCServ::answer_privmsg(IRCMessage & msg, int fd) {}

// void IRCServ::answer_notice(IRCMessage & msg, int fd) {}



// void IRCServ::answer_pong(IRCMessage & msg, int fd) {}


void IRCServ::answer_pass(IRCMessage & msg, int fd)
{
	std::ostringstream recv_pass;
	vectorIteratorPairType range = msg.getParameters();
	for (vector<string>::const_iterator it = range.first; it != range.second; ++it)
		recv_pass << (it == range.first ? "" : " ") << *it;

	if (recv_pass.str().empty())
	{
		queue_and_send(fd, "461 * PASS :Not enough parameters\r\n");
		close_client(fd);
		return;
	}
	if (recv_pass.str() != clientPassword)
	{
		std::cout << "debug: password incorrecta" << std::endl;
		queue_and_send(fd, "464 * :Password incorrect\r\n");
		close_client(fd);
		return;
	}
	clients[fd].setFlag(PASS_FLAG);
}

void IRCServ::answer_nick(IRCMessage & msg, int fd)
{
	if (msg.getParameters().first == msg.getParameters().second) {
		queue_and_send(fd, ":server 431 :No nickname given\r\n");
		return;
	}

	std::string new_nick = *(msg.getParameters().first);
	std::string old_nick = clients[fd].getNick();

	if (!IRCClient::isValidNick(new_nick)) {
		std::string err = ":server 432 * " + new_nick + " :Erroneous nickname\r\n";
		queue_and_send(fd, err);
		return;
	}
	if (!nickIsUnique(new_nick)) {
		std::string err = ":server 433 * " + new_nick + " :Nickname is already in use\r\n";
		queue_and_send(fd, err);
		return;
	}

	clients[fd].setNick(new_nick);
	addToNicks(new_nick);
	clients[fd].setFlag(NICK_FLAG);

	if (old_nick != "") {
		rmFromNicks(old_nick);
		std::string msg = ":" + old_nick + "!" + clients[fd].getUsername() + "@" + clients[fd].getHost() + " NICK " + new_nick + "\r\n";
		queue_and_send(fd, msg);
		//aqui haríamos broadcast a todos los canales
		//broadcast(fd, msg);
	}
	else if (clients[fd].checkFlag(NICK_FLAG) && clients[fd].checkFlag(USER_FLAG) && clients[fd].checkFlag(PASS_FLAG)) 
	{
		std::string nick = clients[fd].getNick();
		std::string welcome = ":server 001 " + nick + " :Welcome to the Internet Relay Network " + nick + "!" + clients[fd].getUsername() + "@" + clients[fd].getHost() + "\r\n";
		queue_and_send(fd, welcome);
	}

}

void IRCServ::answer_user(IRCMessage & msg, int fd)
{
	if (clients[fd].getUsername() != "") {
		std::string nick = clients[fd].getNick().empty() ? "*" : clients[fd].getNick();
		queue_and_send(fd, ":server 462 " + nick + " :Unauthorized command\r\n");
		return;
	}

	if (std::distance(msg.getParameters().first, msg.getParameters().second) < 4) {
		std::string nick = clients[fd].getNick().empty() ? "*" : clients[fd].getNick();
		queue_and_send(fd, ":server 461 " + nick + " USER :Not enough parameters\r\n");
		return;
	}

	std::string user = *(msg.getParameters().first);

	if (!IRCClient::isValidUsername(user)) {
		std::string nick = clients[fd].getNick().empty() ? "*" : clients[fd].getNick();
		queue_and_send(fd, ":server 432 " + nick + " :Erroneous username\r\n");
		return;
	}

	clients[fd].setUsername(user);
	clients[fd].setFlag(USER_FLAG);

	if (clients[fd].checkFlag(NICK_FLAG) && clients[fd].checkFlag(USER_FLAG) && clients[fd].checkFlag(PASS_FLAG)) 
	{
		std::string nick = clients[fd].getNick();
		std::string welcome = ":server 001 " + nick + " :Welcome to the Internet Relay Network " + nick + "!" + user + "@" + clients[fd].getHost() + "\r\n";
		queue_and_send(fd, welcome);
	}
}


void IRCServ::queue_and_send(int fd, std::string data)
{
    clients[fd].addToObuffer(data);

    std::string &buffer = clients[fd].getObuffer();
    
    ssize_t sent = send(fd, buffer.c_str(), buffer.size(), MSG_NOSIGNAL);
    if (sent > 0)
        buffer.erase(0, sent);

    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN | EPOLLET;
    if (!buffer.empty())
        ev.events |= EPOLLOUT;

    epoll_ctl(epoll_fd, EPOLL_CTL_MOD, fd, &ev);
}

void IRCServ::broadcast(int fd, std::string notify_msg)
{
	std::set<int> targets;
	targets.insert(fd);

	pairIterators its = clients[fd].getChannelIterators();
	for (; its.first != its.second; ++its.first) {
		IRCChannel* chan = &channels[*its.first];

		pairIterators cits = chan->getChannelIterators();
		for (; cits.first != cits.second; ++cits.first) {
			if (*(targets.insert(getFdFromNick(*cits.first)).first) == -1)
				throw std::runtime_error("Tried to reach nonexistent client");
		}
	}

	for (std::set<int>::iterator it = targets.begin(); it != targets.end(); ++it) {
		queue_and_send(*it, notify_msg);
	}
}

int IRCServ::getFdFromNick(string s)
{
		for (std::map<int, IRCClient>::iterator it = clients.begin(); it != clients.end(); ++it) {
				if (it->second.getNick() == s)
						return it->second.getFd();
		}
		return -1;
}
