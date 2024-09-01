////////////////////////////////////////////////////////////////////////////////
// File:        QTContacts.hpp
// Author:      MyName
// Description:
////////////////////////////////////////////////////////////////////////////////
#ifndef UI_QTCONTACTS_H
#define UI_QTCONTACTS_H
////////////////////////////////////////////////////////////////////////////////

#include <QLineEdit>
#include <QListWidget>
#include <QVBoxLayout>

namespace Ui {

//------------------------------------------------------------------------------

// TODO: Create contact selection
class QTContacts : public QVBoxLayout {

public:
  QTContacts();
  ~QTContacts();

private:
  QListWidget *listView;
  QLineEdit *lineEdit;

  void handleContacts();
  void addContact(std::string const &);
};

//------------------------------------------------------------------------------

} // namespace Ui
#endif /* UI_QTCONTACTS_H */
