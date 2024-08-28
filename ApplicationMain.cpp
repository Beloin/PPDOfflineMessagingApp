#include "ApplicationMain.h"
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
  setFixedSize(1200, 800);
  setLayoutDirection(Qt::RightToLeft);
  auto scene = new QGraphicsScene{this};
  auto button = new QPushButton("Connect");

  auto mainWidget = new QWidget();
  auto hbox = new QHBoxLayout();
  hbox->addWidget(button);

  auto vbox = new QVBoxLayout();
  vbox->addItem(hbox);

  auto mainHorizontalBox = new QHBoxLayout();
  mainHorizontalBox->addItem(vbox);

  mainWidget->setLayout(mainHorizontalBox);
  setCentralWidget(mainWidget);
}
