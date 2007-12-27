#include "logwindow.h"
#include <wx/wx.h>

LogWindow::LogWindow(wxWindow * parent) : wxTextCtrl(parent, -1, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxTE_AUTO_URL, wxDefaultValidator, wxTextCtrlNameStr) {
	lf = parent;
	this->AppendText(wxString("blablabla\nmachin\nhttp://hugo.coding-badger.net"));
}