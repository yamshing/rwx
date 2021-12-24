#include "treectrl.h"
#include "static_func.h"
 

TreeCtrl::TreeCtrl(int nargs, VALUE *args)
{
	VALUE parent = args[0];
	VALUE option = args[1];
	
	App* app_p = static_cast<App*>(wxTheApp);
	wxWindow* parent_p = static_cast<wxWindow*>(app_p->GetObjectFromMap(parent));
	std::cout << "treectrl ctor (in treectrl.cpp) "  << std::endl;
	CreateTreeCtrl(parent_p);
	 
}

void TreeCtrl::CreateTreeCtrl(wxWindow* parent)
{
	m_tree_ctrl = new wxTreeCtrl(parent, wxID_ANY,
			wxPoint(0,0),
			parent->FromDIP(wxSize(160,250)),
			wxTR_DEFAULT_STYLE | wxNO_BORDER);
	 
}
 
