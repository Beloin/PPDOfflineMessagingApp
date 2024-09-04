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

using OnContactChange = std::function<void(std::string &)>;

// TODO: Create contact selection
class QTContacts : public QVBoxLayout {

public:
  QTContacts(OnContactChange);
  ~QTContacts();

private:
  QListWidget *listView;
  QLineEdit *lineEdit;

  void handleContacts();
  // TODO: Use ContactService to save
  // contacts as a list of those, and referecing them with some id
  void addContact(std::string const &);

  void onContactClick(QListWidgetItem *);

  OnContactChange pCallback{nullptr};
};

//------------------------------------------------------------------------------

} // namespace Ui
#endif /* UI_QTCONTACTS_H */
