/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCServ.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2026/02/17 12:02:26 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef IRCSERV_HPP
#define IRCSERV_HPP


#include <sys/epoll.h>
#include <map>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include "IRCChannel.hpp"
#include "IRCClient.hpp"
#include "IRCMessage.hpp"

#define SERVER_NAME "42_irc_server"
#define TIMEOUT	120 //seconds

class IRCServ {
public:
	IRCServ();
	IRCServ(int listening_port, std::string password);
	~IRCServ();

	int																getListeningSocket() const;
	void															setListeningSocket(int socket);
	void															setClientPassword(std::string& password);
	bool															checkClientPassword(std::string& password) const;
	int																getEpollFd() const;
	void															setEpollFd(int fd);
	const std::map<int, IRCClient>&		getClients() const;
	std::map<int, IRCClient>&					getClients();
	void															setClients(const std::map<int, IRCClient>& newClients);
	struct epoll_event*								getEvents();
	const struct epoll_event*					getEvents() const;
	void															setEvent(int fd, epoll_event event);
	void															addToNicks(const string & n, int fd);
	void															rmFromNicks(const string & n);
	bool															nickIsUnique(const string & n);
	int 															getFdFromNick(string s);
	std::string												getServerName(void) const;
	const std::map<const std::string, int>&	getNicks(void) const; //For privmsg
	const std::map<const string, IRCChannel>& getChannels(void) const; //Privmsg
	std::map<const string, IRCChannel>& getChannels(void); //KICK
	
	void			run();
	void			process_client_buffer(int fd);
	void			close_client(int fd);
	void			accept_new_connection();
	bool			read_from_client(IRCClient & client);
	void			answer_command(IRCMessage & msg, int fd);
	void			sendWelcome(int fd);
	void			queue_and_send(int fd, std::string data);
	void			broadcast(int fd, std::string notify_msg);
	void			broadcastToChannel(IRCChannel & channel, const std::string & message);
	void			send_names_from_channel(const IRCChannel &channel, int fd);

	void			answer_pass(IRCMessage & msg, int fd);
	void			answer_nick(IRCMessage & msg, int fd);
	void			answer_user(IRCMessage & msg, int fd);
	void			answer_ping(IRCMessage & msg, int fd);
	void 			answer_join(IRCMessage & msg, int fd);
	void 			answer_part(IRCMessage & msg, int fd);	
	void			answer_pong(IRCMessage & msg, int fd);
	void			answer_privmsg(IRCMessage & msg, int fd);
	void			answer_mode(IRCMessage & msg, int fd);
	void			answer_notice(IRCMessage & msg, int fd);
	void			answer_quit(IRCMessage & msg, int fd);
	void			answer_kick(IRCMessage & msg, int fd);
	void			answer_topic(IRCMessage & msg, int fd);
	void			answer_names(IRCMessage & msg, int fd);
	void			answer_who(IRCMessage & msg, int fd);
	//timeout checkout
	void			send_ping_to_client(int fd);
	void			check_clients_timeout(void);

		//QUIT or any other function to remove clients in the loop
		std::set<int>& get_clientsToBeRemoved(void);
		void					set_clientsToBeRemoved(int fd);
			/** Deletes an empty channel (number of users == 0) from 
	channel map channels.
	*/
	void			delEmptyChannel(const string channelName);


private:
	int listening_socket;
	std::string clientPassword;
	int epoll_fd;
	std::map<int, IRCClient> clients;					// fd -> IRCClient
	struct epoll_event events[16];

	// nick -> fd
	// nicknames are case-insensitive
	std::map<const std::string, int> nicks;		// nick -> fd

	// channelName -> IRCChannel
	// IRC channel names are case-insensitive
	std::map<const string, IRCChannel> channels; 
		std::set<int>	_clientsToBeRemoved; //FDs 
	string server_name;
};
#endif
