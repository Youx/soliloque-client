#include "fmenu.h"
#include "application.h"


FMenuBar::FMenuBar() : wxMenuBar() {
  wxMenu * menuHelp = new wxMenu;
  wxMenu * menuFile = new wxMenu;
  wxMenu * menuStatus = new wxMenu;

  menuHelp->Append(ID_About, _T("&About..."));
 
  menuStatus->Append(ID_ToggleAway, _T("Away"));
  menuStatus->Append(ID_ToggleMic, _T("Mute microphone"));
  menuStatus->Append(ID_ToggleSpk, _T("Mute speakers"));

  menuFile->Append(ID_Connect, _T("Co&nnect"));
  menuFile->Append(ID_QuickConnect, _T("&Quick Connect"));
  menuFile->Append(ID_Disconnect, _T("&Disconnect"));
  menuFile->AppendSeparator();
  menuFile->Append(ID_ServerInfo, _T("&Server Connection Info"));
  menuFile->AppendSeparator();
  menuFile->Append(ID_Quit, _T("Quit"));

  this->Append(menuFile, _T("Connection"));
  this->Append(menuStatus, _T("Status"));
  this->Append(menuHelp, _T("Help"));
}

