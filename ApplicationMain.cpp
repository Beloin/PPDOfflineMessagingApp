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
#include <random>
#include <sstream>
#include <vector>

std::string getRandomString(int len);

ApplicationMain::ApplicationMain(QWidget *parent) : QMainWindow(parent) {
  // setFixedSize(1200, 800);
  setFixedSize(720, 480);
  setLayoutDirection(Qt::RightToLeft);
  auto scene = new QGraphicsScene{this};
  auto button = new QPushButton("Connect");
  nameLabel = new QLabel("Hello user, please connect!");
  connect(button, &QPushButton::released, this, &ApplicationMain::handle);

  auto mainWidget = new QWidget();
  auto hbox = new QHBoxLayout();
  hbox->addWidget(button);

  auto vbox = new QVBoxLayout();
  vbox->setAlignment(Qt::AlignCenter);
  vbox->addItem(hbox);
  vbox->addWidget(nameLabel);

  auto mainHorizontalBox = new QHBoxLayout();
  std::string chatName = "empty_chat";
  pChat = new Ui::QTChat(chatName, msgService);

  pContacts = new Ui::QTContacts(
      [this, &mainHorizontalBox](std::string &newContact) { pChat->clearAll(newContact); });

  mainHorizontalBox->addItem(pChat);
  mainHorizontalBox->addItem(pContacts);
  mainHorizontalBox->addItem(vbox);

  mainWidget->setLayout(mainHorizontalBox);
  setCentralWidget(mainWidget);
}
void ApplicationMain::handle() {
  auto ok2 = connectionDialog();
  if (ok2) {
    auto res = _serverCon.ConnectTo(serverAddress, "22223");
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

  form.addRow(new QLabel("Seu Nome:"));
  auto *clientNameField = new QLineEdit(&dialog);
  clientNameField->setText(QString::fromStdString(clientName));
  form.addRow(clientNameField);

  QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                             Qt::Horizontal, &dialog);
  form.addRow(&buttonBox);

  QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
  QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

  if (dialog.exec() == QDialog::Accepted) {
    if (serverAddressField->text().isEmpty() ||
        clientNameField->text().isEmpty()) {
      return false;
    }

    serverAddress = serverAddressField->text().toStdString();
    clientName = clientNameField->text().toStdString();
    return true;
  }

  return false;
}

void ApplicationMain::listen() {
  // Configure callbacks
  std::ostringstream a;
  a << "Hello, " << clientName;
  nameLabel->setText(QString::fromStdString(a.str()));
  auto hasRegistered = _serverCon.registerClient(clientName);
  if (!hasRegistered) {
    std::cout << "error while registering" << std::endl;
  }
  _serverCon.addOnMessage(
      [this](std::string const &contact, std::string const &message) -> void {
        pChat->addOtherMessage(contact, message);
      });
  _serverCon.listen();
}

void ApplicationMain::handleOffline() { _serverCon.disconnect(); }

std::random_device dev;
std::mt19937 rng(dev());
std::string getRandomString(int len) {
  static const char alphanum[] = "0123456789"
                                 "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                 "abcdefghijklmnopqrstuvwxyz";
  std::string tmp_s;
  tmp_s.reserve(len);

  std::uniform_int_distribution<std::mt19937::result_type> dist6(
      1, sizeof(alphanum) - 1);
  for (int i = 0; i < len; ++i) {
    tmp_s += alphanum[dist6(rng)];
  }

  return tmp_s;
}
