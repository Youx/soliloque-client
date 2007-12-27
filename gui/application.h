#include <wx/wx.h>

extern "C" int main2();



class FreeSpeak: public wxApp 
{
  virtual bool OnInit();
};


class MainWindow: public wxFrame 
{
  public:
    MainWindow(const wxString& title, const wxPoint& pos, const wxSize& size);
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnConnect(wxCommandEvent& event);
    DECLARE_EVENT_TABLE()
};

enum {
  ID_Quit = 1,
  ID_About,
  ID_Connect,
  ID_Disconnect,
  ID_ToggleAway,
  ID_ToggleMic,
  ID_ToggleSpk,
  ID_QuickConnect,
  ID_ServerInfo
};


