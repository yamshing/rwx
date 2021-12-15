#include "list_box.h"
#include "static_func.h"
 
ListCtrl::ListCtrl(int nargs, VALUE *args)
{

	VALUE parent = args[0];
	VALUE option = args[1];
	
	App* app_p = static_cast<App*>(wxTheApp);
	wxWindow* parent_p = static_cast<wxWindow*>(app_p->GetObjectFromMap(parent));
	 
	m_listctrl = new wxListCtrl(parent_p, StaticFunc::ALL_EVENT_ID,
													 wxDefaultPosition, wxDefaultSize, wxLC_REPORT |  wxLC_SINGLE_SEL | wxSUNKEN_BORDER
													 );
	 
	m_listctrl->InsertColumn(0, wxString::FromUTF8("Name"));
	m_listctrl->InsertColumn(1, wxString::FromUTF8("Key"));
	m_listctrl->InsertItem(0,wxString::FromUTF8(""));
	 
	m_listctrl->SetItem(0, 0,wxString::FromUTF8("太郎"));
	m_listctrl->SetItem(0, 1, wxString::FromUTF8("あいうえお"));
	 
	++StaticFunc::ALL_EVENT_ID;
}


