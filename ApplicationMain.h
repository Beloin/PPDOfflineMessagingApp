
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

class ApplicationMain : public QMainWindow {

private:
  Ui::QTChat *pChat;
  Ui::QTChat *ptest1Chat;
  Ui::QTContacts *pContacts;
  QLabel *nameLabel;

  Chat::ServerConnection _serverCon{};
  Chat::MessageService msgService{_serverCon};

  std::string serverAddress;
  std::string clientName{"Juan"};
  std::thread clientListen;

  bool connectionDialog();

public:
  explicit ApplicationMain(QWidget *parent = Q_NULLPTR);

  void handle();
  void listen();

  void disconnect();
};

#endif // TEST_QT5_APPLICATIONMAIN_H
