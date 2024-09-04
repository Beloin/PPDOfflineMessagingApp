////////////////////////////////////////////////////////////////////////////////
// File:        QTChat.hpp
// Author:      MyName
// Description:
////////////////////////////////////////////////////////////////////////////////
#ifndef UI_QTCHAT_H
#define UI_QTCHAT_H
////////////////////////////////////////////////////////////////////////////////

#include "MessageService.hpp"
#include <QLineEdit>
#include <QListWidget>
#include <QVBoxLayout>

namespace Ui {

//------------------------------------------------------------------------------

// TODO: Create a chat to each contact in order to save all chats
class QTChat : public QVBoxLayout {

public:
  QTChat(std::string &name, Chat::MessageService &messageService);
  ~QTChat();

  QListWidget *listView;
  std::string contactName;
  // TODO: Reset message list after each iteration
  std::vector<std::string> &messages;

  void sendMessage();

  void addUserMessage(const std::string &);

  void addOtherMessage(const std::string &msg);

  void clearAll();

private:
  QLineEdit *lineEdit;

  Chat::MessageService &messageService;
};

//------------------------------------------------------------------------------

} // namespace Ui
#endif /* UI_QTCHAT_H */
