
//
// Created by beloin on 11/02/24.
//

#ifndef TEST_QT5_APPLICATIONMAIN_H
#define TEST_QT5_APPLICATIONMAIN_H

#include "chat/ServerConnection.hpp"
#include "ui/QTChat.hpp"
#include "ui/QTContacts.hpp"
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMainWindow>
#include <thread>
#include <unordered_map>

class ApplicationMain : public QMainWindow {

private:
  Ui::QTChat *pChat;
  Ui::QTChat *ptest1Chat;
  Ui::QTContacts *pContacts;

  Chat::ServerConnection _serverCon{};
  Chat::MessageService msgService{_serverCon};

  std::string serverAddress;
  std::thread clientListen;

  // TODO: Instead of creating a list of chats, make it easier using a list of
  // messages
  std::unordered_map<std::string, std::vector<std::string>> chatMap{};

  bool connectionDialog();

public:
  explicit ApplicationMain(QWidget *parent = Q_NULLPTR);

  void handle();
  void listen();

  void disconnect();
};

#endif // TEST_QT5_APPLICATIONMAIN_H
