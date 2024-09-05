#include "QTChat.hpp"
#include "MessageService.hpp"
#include <QAbstractButton>
#include <QLineEdit>
#include <QPushButton>
#include <qstringview.h>
#include <sstream>
#include <string>
#include <vector>

using namespace Ui;

// TODO: Add map to qtchat and use vector list to clear and create
//   std::unordered_map<std::string, std::vector<std::string>> chatMap{};
QTChat::QTChat(std::string &name, Chat::MessageService &messageService)
    : messageService(messageService), contactName(name) {
  listView = new QListWidget();
  auto *itemO1 =
      new QListWidgetItem(QString::fromStdString(generateFirstLine()));
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

std::string QTChat::generateFirstLine() {
  std::ostringstream st{};
  auto title = "Write message to \"";
  st << title << contactName << "\" i";
  return st.str();
}

void QTChat::addUserMessage(const std::string &msg) {
  auto *message = new QListWidgetItem(QString::fromStdString(msg));
  message->setBackground(QColor(0x96, 0x96, 0xFF));
  message->setTextAlignment(Qt::AlignLeft);
  listView->addItem(message);
}

void QTChat::addOtherMessage(const std::string &contact, const std::string &msg) {
  if (contactName != contact) {
    return;
  }
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

  messageService.addMessage(contactName, basicString);

  lineEdit->clear();
}

void QTChat::clearAll(std::string &newCon) {
  listView->clear();
  contactName = newCon;
  auto *itemO1 =
      new QListWidgetItem(QString::fromStdString(generateFirstLine()));
  itemO1->setBackground(Qt::lightGray);
  itemO1->setTextAlignment(Qt::AlignCenter);
  listView->addItem(itemO1);
}

QTChat::~QTChat() {
  delete listView;
  delete lineEdit;
}
