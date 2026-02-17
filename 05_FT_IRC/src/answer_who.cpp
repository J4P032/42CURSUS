#include "IRCClient.hpp"
#include "IRCCommand.hpp"
#include "IRCMessage.hpp"
#include "IRCServ.hpp"
#include "IRCChannel.hpp"
#include <sstream>
#include <string>
#include <vector>

void IRCServ::answer_who(IRCMessage & msg, int fd)
{
    if (msg.getParametersSize() < 1)
        return; 

    std::string target = msg.getParam(0);
    std::string requestingNick = clients[fd].getNick();

    if (target[0] == '#') {
        if (channels.find(target) != channels.end()) {
            IRCChannel &channel = channels[target];
            PairUserMapIterators pairIterators = channel.getUsersIterators();
            
            for (UserMapIterator kvIt = pairIterators.first; kvIt != pairIterators.second; ++kvIt) {
                std::string userNick = kvIt->first;
                UserMode uMode = kvIt->second;

                IRCClient &targetClient = clients[nicks[userNick]];

                // --- Construcción de RPL_WHOREPLY (352) ---
                std::stringstream rpl;
                rpl << ":" << getServerName() << " 352 " << requestingNick << " " << target << " "
                    << targetClient.getUsername() << " " << targetClient.getHost() << " "
                    << getServerName() << " " << userNick << " H"; // 'H' es por "Here"
                
                if (uMode == CHANNEL_OPERATOR)
                    rpl << "@";
                
                rpl << " :0 " << targetClient.getFullname() << "\r\n";
                
                queue_and_send(fd, rpl.str());
            }
        }

        // --- RPL_ENDOFWHO (315) ---
        std::stringstream endRpl;
        endRpl << ":" << getServerName() << " 315 " << requestingNick << " " << target << " :End of /WHO list\r\n";
        queue_and_send(fd, endRpl.str());
    }
}
