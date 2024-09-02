#include "MessageService.hpp"

void Chat::MessageService::addMessage(const std::string &contact,
                                      const std::string &message) {
  serverConnection.sendMessage(message, contact);
}
