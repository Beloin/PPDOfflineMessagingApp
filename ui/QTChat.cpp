#include "QTChat.hpp"
#include "MessageService.hpp"
#include <QAbstractButton>
#include <QLineEdit>
#include <QPushButton>
#include <string>

using namespace Ui;

QTChat::QTChat(Chat::MessageService &messageService)
    : messageService(messageService) {
  listView = new QListWidget();
  auto *itemO1 = new QListWidgetItem("Write message");
  itemO1->setBackground(Qt::lightGray);
  itemO1->setTextAlignment(Qt::AlignCenter);
  listView->addItem(itemO1);

  auto button = new QPushButton("Send");
  connect(button, &QPushButton::released, this, &QTChat::sendMessage);

  QBoxLayout::addWidget(listView);

  lineEdit = new QLineEdit();

  auto hbox = new QHBoxLayout();
  hbox->setDirection(LeftToRight);
  hbox->addWidget(lineEdit);
  hbox->addWidget(button);

  QBoxLayout::addItem(hbox);
}

void QTChat::addUserMessage(const std::string &msg) {
  auto *message = new QListWidgetItem(QString::fromStdString(msg));
  message->setBackground(QColor(0x96, 0x96, 0xFF));
  message->setTextAlignment(Qt::AlignLeft);
  listView->addItem(message);
}

void QTChat::addOtherMessage(const std::string &msg) {
  auto *message = new QListWidgetItem(QString::fromStdString(msg));
  message->setBackground(QColor(0xFF, 0x9D, 0x96));
  message->setTextAlignment(Qt::AlignRight);
  listView->addItem(message);
}

void QTChat::sendMessage() {
  const QString &string = lineEdit->text();

  if (string.isNull() || string.isEmpty())
    return;

  const std::string &basicString = string.toStdString();
  addUserMessage(basicString);

  // TODO: Add contact as constructor parameter
  std::string contact{"mycontact"};
  // TODO: server_fd is somehow wrong here -> Memory leak?
  messageService.addMessage(contact, basicString);

  lineEdit->clear();
}

void QTChat::clearAll() {
  listView->clear();

  auto *itemO1 = new QListWidgetItem("Write message");
  itemO1->setBackground(Qt::lightGray);
  itemO1->setTextAlignment(Qt::AlignCenter);
  listView->addItem(itemO1);
}

QTChat::~QTChat() {
  delete listView;
  delete lineEdit;
}
