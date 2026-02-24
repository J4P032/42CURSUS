/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   answer_quit.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 11:09:52 by jrollon-          #+#    #+#             */
/*   Updated: 2026/02/17 19:15:38 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCCommand.hpp"
#include "IRCServ.hpp"
#include <sstream>
#include <iostream>

typedef std::map<int, IRCClient>::iterator SENDER;

void IRCServ::answer_quit(IRCMessage & msg, int fd) {
    (void)msg;
    SENDER it_sender = clients.find(fd);
    if (it_sender == clients.end())
        return;
    set_clientsToBeRemoved(fd);
}
