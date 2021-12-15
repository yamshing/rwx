#include "list_box.h"
#include "static_func.h"
 
ListBox::ListBox(int nargs, VALUE *args)
{

	VALUE parent = args[0];
	VALUE option = args[1];
	 
	//VALUE label = rb_hash_aref(option, ID2SYM(rb_intern("label")));
	//std::string label_str; 
	//StaticFunc::ValueToString(label, label_str);
	
	App* app_p = static_cast<App*>(wxTheApp);
	wxWindow* parent_p = static_cast<wxWindow*>(app_p->GetObjectFromMap(parent));
	 
	m_listbox = new wxListBox(parent_p, StaticFunc::ALL_EVENT_ID,
													 wxDefaultPosition, wxDefaultSize,
													 0, NULL, wxLB_HSCROLL
													 );
	m_listbox->Append(wxString::FromUTF8("test"));
	m_listbox->Append(wxString::FromUTF8("test2"));
	 
	++StaticFunc::ALL_EVENT_ID;
}


