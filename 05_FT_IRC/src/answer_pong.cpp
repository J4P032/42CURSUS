/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   answer_pong.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 11:15:06 by jrollon-          #+#    #+#             */
/*   Updated: 2026/02/09 12:00:10 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCServ.hpp"

void IRCServ::answer_pong(IRCMessage& msg, int fd)
{
    (void)msg;
    std::map<int, IRCClient>::iterator it = clients.find(fd);

    if (it != clients.end()) {
        it->second.updateLastActivity(); // mas eficiente que lo de abajo.
    }

    // if (clients.count(fd)){ //arriba menos eficiente por que busca una vez y vuelve a buscar otra.
    // clients[fd].updateLastActivity();
}
