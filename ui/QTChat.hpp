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
#include <vector>

namespace Ui {

//------------------------------------------------------------------------------

// TODO: Create a chat to each contact in order to save all chats
class QTChat : public QVBoxLayout {

public:
  QTChat(std::string &name, Chat::MessageService &messageService);
  ~QTChat();

  QListWidget *listView;
  std::string contactName;
  void sendMessage();

  void addUserMessage(const std::string &);

  void addOtherMessage(std::string const&contact, const std::string &msg);

  void clearAll(std::string &newContact);

  std::unordered_map<std::string, std::vector<std::string>> buffer{};

private:
  QLineEdit *lineEdit;

  Chat::MessageService &messageService;

  std::string generateFirstLine();


  void addToBuffer(const std::string &, const std::string&);
};

//------------------------------------------------------------------------------

} // namespace Ui
#endif /* UI_QTCHAT_H */
