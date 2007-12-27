#include <wx/wx.h>
#include <wx/log.h>

class LogWindow : public wxTextCtrl
{
public:
	LogWindow(wxWindow * parent);
private:
	wxWindow * lf;
};