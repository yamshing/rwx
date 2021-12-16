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
	 
	//m_listctrl->SetItem(0, 0,wxString::FromUTF8("太郎"));
	//m_listctrl->SetItem(0, 1, wxString::FromUTF8("あいうえお"));
	 
	VALUE content = rb_hash_aref(option, ID2SYM(rb_intern("content")));
	int size = static_cast<int>(RARRAY_LEN(content));
	 
	std::cout << "size (in list_ctrl.cpp) " << size << std::endl;
	for (int i = 0; i < size; ++i) {
		 
		VALUE sub_arr = rb_ary_entry(content,i);
		 
		int sub_size = static_cast<int>(RARRAY_LEN(sub_arr));
		m_listctrl->InsertItem(i,"");
		 
		for (int j = 0; j < sub_size; ++j) {
			 
			VALUE sub_content = rb_ary_entry(sub_arr,j);
			std::string sub_content_str;
			 
			StaticFunc::ValueToString(sub_content, sub_content_str);
			 
			m_listctrl->SetItem(i, j,wxString::FromUTF8(sub_content_str));
			 
		}
		 
	}
	 
	++StaticFunc::ALL_EVENT_ID;
	 
}


