#include "QTContacts.hpp"
#include <QAbstractButton>
#include <QLineEdit>
#include <QPushButton>

using namespace Ui;

QTContacts::QTContacts() {
  listView = new QListWidget();
  auto *itemO1 = new QListWidgetItem("Add contact \"name,host[,port]\"");
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
  
}
