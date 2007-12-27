#include "servertree.h"

ServerTree::ServerTree(wxWindow * parent) : wxTreeCtrl(parent, -1, wxDefaultPosition, wxDefaultSize,  wxTR_HAS_BUTTONS|wxTR_FULL_ROW_HIGHLIGHT|wxTR_MULTIPLE, wxDefaultValidator, "treeCtrl") {
	wxTreeItemId root = this->AddRoot("Racine", -1, -1, NULL);
	wxTreeItemId it1 = this->AppendItem(root, "Item 1", -1, -1, NULL);
	wxTreeItemId it2 = this->AppendItem(root, "Item 2", -1, -1, NULL);
}