#include "mainandlog.h"
#include "logwindow.h"
#include "servertree.h"


MainAndLog::MainAndLog(wxFrame *parent)
                : wxSplitterWindow(parent, wxID_ANY,
                                   wxDefaultPosition, wxDefaultSize,
                                   wxSP_3D | wxSP_LIVE_UPDATE |
                                   wxCLIP_CHILDREN /* | wxSP_NO_XP_THEME */ )
{
    m_frame = parent;
    SplitHorizontally(new ServerTree(this), new LogWindow(this), 100);
}
