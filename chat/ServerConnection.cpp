#include "ServerConnection.hpp"
#include <iostream>

bool Chat::ServerConnection::sendMessage(ConstString message,
                                         ConstString contact) {
  std::cout << "Sending message to " << contact << std::endl;
  if (message.length() > 255) {
    return false;
  }

  std::string normalizedMessage{message};
  for (int i = normalizedMessage.length(); i < 255; i++) {
    normalizedMessage += '\0';
  }

  std::string normalizedContact{contact};
  for (int i = normalizedContact.length(); i < 255; i++) {
    normalizedContact += '\0';
  }

  // TODO: validate
  auto status = internalSendBytes(std::string{2}, 1);
  status = internalSendBytes(normalizedContact, 256);
  status = internalSendBytes(normalizedMessage, 256);

  return status > 0;
}

bool Chat::ServerConnection::registerClient(ConstString myClientName) {
  std::cout << "Registering client with name: " << myClientName << std::endl;
  if (myClientName.length() > 255) {
    return false;
  }

  std::string result{myClientName};
  for (int i = result.length(); i < 255; i++) {
    result += '\0';
  }

  // TODO: validate
  auto status = internalSendBytes(std::string{1}, 1);
  status = internalSendBytes(result, 256);

  return status > 0;
}

void Chat::ServerConnection::listen() {
  if (!hasConnected)
    return;

  char buffer[256]; // High to receive TEXT
  ssize_t status = 1;
  while (status && hasConnected) {
    // First 256 bytes is contact name
    status = internalReadBytes((unsigned char *)buffer, 256);
    auto contactName = std::string{buffer};
    if (status <= 0)
      break;
    status = internalReadBytes((unsigned char *)buffer, 256);
    auto message = std::string{buffer};
    if (status <= 0)
      break;

    callOnMessage(contactName, message);
  }

  std::cout << "Connection closed..." << std::endl;
  disconnect();
}

void Chat::ServerConnection::callOnMessage(Chat::ConstString contactName, Chat::ConstString message) {
  std::cout << "Recieved message" << std::endl;
  if (chatCallable != nullptr) {
    chatCallable(contactName, message);
  }
}

void Chat::ServerConnection::addOnMessage(OnMessage cb) { chatCallable = cb; }
