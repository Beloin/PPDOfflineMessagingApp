////////////////////////////////////////////////////////////////////////////////
// File:        ContactsService.hpp
// Author:      MyName
// Description:
////////////////////////////////////////////////////////////////////////////////
#ifndef CHAT_CONTACTSSERVICE_H
#define CHAT_CONTACTSSERVICE_H
////////////////////////////////////////////////////////////////////////////////

namespace Chat {

//------------------------------------------------------------------------------

class ContactsService {

public:
  ContactsService() = default;
  ~ContactsService() = default;

private:
  void createOrUseChat();
};

//------------------------------------------------------------------------------

} // namespace Chat
#endif /* CHAT_CONTACTSSERVICE_H */
