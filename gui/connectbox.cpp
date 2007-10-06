#include "connectbox.h"

ConnectBox::ConnectBox() 
: wxDialog(NULL, -1, _T("Connect to"), wxDefaultPosition, wxSize(250,230))
{
  wxBoxSizer * vbox = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer * hbox1 = new wxBoxSizer(wxHORIZONTAL);

  hbox1->Add(new wxStaticText(this, -1, _T("Server address")));
  hbox1->Add(new wxTextCtrl(this, -1, _T("")), 1);
  vbox->Add(hbox1);

  SetSizer(vbox);
  Centre();
  ShowModal();
  Destroy();
}
