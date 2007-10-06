#include "application.h"
#include "connectbox.h"
#include "fmenu.h"

/*#include <zthread/Runnable.h>*/


BEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_MENU(ID_Quit, MainWindow::OnQuit)
EVT_MENU(ID_About, MainWindow::OnAbout)
EVT_MENU(ID_Connect, MainWindow::OnConnect)
END_EVENT_TABLE()

IMPLEMENT_APP(FreeSpeak)



/*EngineThread::EngineThread() : ZThread::Runnable() {

}

void EngineThread::run() {
  main2(); */
/*  int sockfd;
  struct sockaddr_in servaddr;

  struct connection_request connectme = {
    "Machine Youx",
    "",
    "sllm",
    "Client test!",
    0
  };
  connect_to(&connectme, &sockfd, &servaddr);
  receive(sockfd, &servaddr); */
  /*return 0;*/
/*}*/

bool FreeSpeak::OnInit() {
  MainWindow * frame = new MainWindow( _T("FreeSpeak"), wxPoint(50,50), wxSize(450,340));
  frame->Show(TRUE);
  SetTopWindow(frame);
  return true;
}

MainWindow::MainWindow(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
   FMenuBar * menubar = new FMenuBar;
   SetMenuBar(menubar);
   CreateStatusBar();
   SetStatusText( _T(""));
}

void MainWindow::OnQuit(wxCommandEvent& WXUNUSED(event)) {
  Close(TRUE);
}

void MainWindow::OnAbout(wxCommandEvent& WXUNUSED(event)) {
  wxMessageBox(_T("FreeSpeak, written by Hugo Camboulive"),
      _T("About FreeSpeak"), wxOK | wxICON_INFORMATION, this);
}

void MainWindow::OnConnect(wxCommandEvent& WXUNUSED(event)) {
   ConnectBox * cb = new ConnectBox();
}
