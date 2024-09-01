////////////////////////////////////////////////////////////////////////////////
// File:        QTChat.hpp
// Author:      MyName
// Description:
////////////////////////////////////////////////////////////////////////////////
#ifndef UI_QTCHAT_H
#define UI_QTCHAT_H
////////////////////////////////////////////////////////////////////////////////

#include <QLineEdit>
#include <QListWidget>
#include <QVBoxLayout>

namespace Ui {

//------------------------------------------------------------------------------

// TODO: Create a chat to each contact in order to save all chats
class QTChat : public QVBoxLayout {

public:
  QTChat();
  ~QTChat();

  QListWidget *listView;

  void sendMessage();

  void addUserMessage(const std::string &);

  void addOtherMessage(const std::string &msg);

  void clearAll();

private:
  QLineEdit *lineEdit;
};

//------------------------------------------------------------------------------

} // namespace Ui
#endif /* UI_QTCHAT_H */
