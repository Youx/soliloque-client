#include <wx/wx.h>
#include <wx/splitter.h>


class MainAndLog : public wxSplitterWindow
{
public:
	MainAndLog(wxFrame * parent);
private:
	wxFrame * m_frame;
};
