
//
// Created by beloin on 11/02/24.
//

#ifndef TEST_QT5_APPLICATIONMAIN_H
#define TEST_QT5_APPLICATIONMAIN_H

#include "ui/QTChat.hpp"
#include "ui/QTContacts.hpp"
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMainWindow>

class ApplicationMain : public QMainWindow {

private:
  bool connectionDialog();
  Ui::QTChat *pChat;
  Ui::QTContacts *pContacts;

public:
  explicit ApplicationMain(QWidget *parent = Q_NULLPTR);

  void OnMessage(std::string message);
};

#endif // TEST_QT5_APPLICATIONMAIN_H
