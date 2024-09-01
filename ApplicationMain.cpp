#include "ApplicationMain.h"
#include "ui/QTContacts.hpp"
#include <QBoxLayout>
#include <QDialogButtonBox>
#include <QDir>
#include <QFormLayout>
#include <QGraphicsScene>
#include <QInputDialog>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QPushButton>

ApplicationMain::ApplicationMain(QWidget *parent) : QMainWindow(parent) {
  // setFixedSize(1200, 800);
  setFixedSize(720, 480);
  setLayoutDirection(Qt::RightToLeft);
  auto scene = new QGraphicsScene{this};
  auto button = new QPushButton("Connect");

  auto mainWidget = new QWidget();
  auto hbox = new QHBoxLayout();
  hbox->addWidget(button);

  auto vbox = new QVBoxLayout();
  vbox->addItem(hbox);

  auto mainHorizontalBox = new QHBoxLayout();
  // TODO: Create a way to change chats when clicked in contacts -> onContactClick
  pChat = new Ui::QTChat();
  pContacts = new Ui::QTContacts();
  mainHorizontalBox->addItem(pChat);
  mainHorizontalBox->addItem(pContacts);
  mainHorizontalBox->addItem(vbox);

  mainWidget->setLayout(mainHorizontalBox);
  setCentralWidget(mainWidget);
}
