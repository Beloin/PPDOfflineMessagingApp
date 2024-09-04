#include "ApplicationMain.h"
#include "MessageService.hpp"
#include "ui/QTChat.hpp"
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
#include <qwidget.h>
#include <vector>

ApplicationMain::ApplicationMain(QWidget *parent) : QMainWindow(parent) {
  // setFixedSize(1200, 800);
  setFixedSize(720, 480);
  setLayoutDirection(Qt::RightToLeft);
  auto scene = new QGraphicsScene{this};
  auto button = new QPushButton("Connect");
  connect(button, &QPushButton::released, this, &ApplicationMain::handle);

  auto mainWidget = new QWidget();
  auto hbox = new QHBoxLayout();
  hbox->addWidget(button);

  auto vbox = new QVBoxLayout();
  vbox->addItem(hbox);

  auto mainHorizontalBox = new QHBoxLayout();
  // TODO: Create a way to change chats when clicked in contacts ->
  // onContactClick
  std::string chatName = "empty_chat";
  // TODO: Create a mock qtchat to be as empty contact
  pChat = new Ui::QTChat(chatName, msgService);

  pContacts = new Ui::QTContacts([this, &mainHorizontalBox](std::string &str) {
    auto found = chatMap.find(str);
    if (found != chatMap.end()) {
      // pChat = found->second;
    } else {
      auto newMap = new Ui::QTChat(str, msgService);
      chatMap.insert({str, std::vector<std::string>{}});
    }

  });

  mainHorizontalBox->addItem(pChat);
  mainHorizontalBox->addItem(pContacts);
  mainHorizontalBox->addItem(vbox);

  mainWidget->setLayout(mainHorizontalBox);
  setCentralWidget(mainWidget);
}
void ApplicationMain::handle() {
  auto ok2 = connectionDialog();
  if (ok2) {
    auto res = _serverCon.ConnectTo(serverAddress, "22222");
    if (res) {
      QMessageBox messageBox;
      messageBox.critical(this, "Error", "Could not connect to server");
      return;
    }
    clientListen = std::thread{&ApplicationMain::listen, this};
    clientListen.detach();
  }
}

bool ApplicationMain::connectionDialog() {
  QDialog dialog(this);
  QFormLayout form(&dialog);

  form.addRow(new QLabel("End. do Servidor:"));

  auto *serverAddressField = new QLineEdit(&dialog);
  serverAddressField->setText("localhost");
  form.addRow(serverAddressField);

  QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                             Qt::Horizontal, &dialog);
  form.addRow(&buttonBox);

  QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
  QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

  if (dialog.exec() == QDialog::Accepted) {
    if (serverAddressField->text().isEmpty()) {
      return false;
    }

    serverAddress = serverAddressField->text().toStdString();
    return true;
  }

  return false;
}

void ApplicationMain::listen() {
  // Configure callbacks
  _serverCon.addOnMessage([this](std::string const &message) -> void {
    pChat->addOtherMessage(message);
  });
  _serverCon.listen();
}
