////////////////////////////////////////////////////////////////////////////////
// File:        ServerConnection.hpp
// Author:      MyName
// Description:
////////////////////////////////////////////////////////////////////////////////
#ifndef CHAT_SERVERCONNECTION_H
#define CHAT_SERVERCONNECTION_H
////////////////////////////////////////////////////////////////////////////////

#include "../network/client.h"
#include <functional>
#include <iostream>
#include <string>

namespace Chat {

using ConstString = std::string const &;
typedef std::string const &MyStr;

// typedef void (*OnMessage)(ConstString message);
// Enables caputuring lambdas
typedef std::function<void(ConstString, ConstString)> OnMessage;

//------------------------------------------------------------------------------

class ServerConnection : public Network::Client {

public:
  ServerConnection() = default;
  ~ServerConnection() = default;

  bool sendMessage(ConstString message, ConstString contact);

  bool registerClient(ConstString myClientName);

  void listen();

  // TODO: Create a way to read chat messages
  void addOnMessage(OnMessage);

private:
  void callOnMessage(Chat::ConstString contactName, Chat::ConstString message);
  OnMessage chatCallable{nullptr};
};

//------------------------------------------------------------------------------

} // namespace Chat
#endif /* CHAT_SERVERCONNECTION_H */
