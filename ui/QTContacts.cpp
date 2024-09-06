#include "QTContacts.hpp"
#include "split.hpp"
#include <QAbstractButton>
#include <QLineEdit>
#include <QPushButton>
#include <iostream>
#include <qlistwidget.h>

using namespace Ui;

QTContacts::QTContacts(OnContactChange onContactChange)
    : pCallback(onContactChange) {
  listView = new QListWidget();
  connect(listView, &QListWidget::itemClicked, this,
          &QTContacts::onContactClick);

  auto *itemO1 = new QListWidgetItem("Add contact Name");
  itemO1->setBackground(Qt::lightGray);
  itemO1->setTextAlignment(Qt::AlignCenter);
  listView->addItem(itemO1);

  auto button = new QPushButton("Add Contact");
  connect(button, &QPushButton::released, this, &QTContacts::handleContacts);

  QBoxLayout::addWidget(listView);

  lineEdit = new QLineEdit();

  auto hbox = new QHBoxLayout();
  hbox->setDirection(LeftToRight);
  hbox->addWidget(lineEdit);
  hbox->addWidget(button);
  QBoxLayout::addItem(hbox);
}

QTContacts::~QTContacts() {
  delete listView;
  delete lineEdit;
}

void QTContacts::handleContacts() {
  const QString &string = lineEdit->text();

  if (string.isNull() || string.isEmpty())
    return;

  const std::string &basicString = string.toStdString();
  addContact(basicString);
  // TODO: Create something here

  lineEdit->clear();
}

void QTContacts::addContact(std::string const &value) {
  auto vars = split(value, ",");
  auto *message = new QListWidgetItem(QString::fromStdString(value));
  message->setBackground(QColor(0x96, 0x96, 0xFF));
  message->setTextAlignment(Qt::AlignLeft);
  listView->addItem(message);
}

void QTContacts::onContactClick(QListWidgetItem *item) {
  if (listView->item(0) == item) {
    std::cout << "Cannot change first item" << std::endl;
    return;
  }

  std::string contactName = item->text().toStdString();
  std::cout << "Clicked on: " << contactName << std::endl;

  if (pCallback)
    pCallback(contactName);
}
