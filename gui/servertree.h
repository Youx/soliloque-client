#include <wx/wx.h>
#include <wx/treectrl.h>

class ServerTree : public wxTreeCtrl {
public:
	ServerTree(wxWindow * parent);
private:
	wxWindow * parent;
};