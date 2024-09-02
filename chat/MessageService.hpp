////////////////////////////////////////////////////////////////////////////////
// File:        MessageService.hpp
// Author:      MyName
// Description:
////////////////////////////////////////////////////////////////////////////////
#ifndef CHAT_MESSAGESERVICE_H
#define CHAT_MESSAGESERVICE_H
////////////////////////////////////////////////////////////////////////////////

#include "ServerConnection.hpp"
namespace Chat {

//------------------------------------------------------------------------------

class MessageService {

public:
  MessageService(ServerConnection &serverConnection)
      : serverConnection(serverConnection) {}

  void addMessage(const std::string &contact, const std::string &message);

private:
  ServerConnection &serverConnection;
};

//------------------------------------------------------------------------------

} // namespace Chat
#endif /* CHAT_MESSAGESERVICE_H */
