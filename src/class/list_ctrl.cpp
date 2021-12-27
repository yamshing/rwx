#include "list_box.h"
#include "static_func.h"
 
ListCtrl::ListCtrl(int nargs, VALUE *args)
{

	VALUE parent = args[0];
	VALUE option = args[1];
	
	App* app_p = static_cast<App*>(wxTheApp);
	wxWindow* parent_p = static_cast<wxWindow*>(app_p->GetObjectFromMap(parent));
	 
	m_listctrl = new wxListCtrl(parent_p, StaticFunc::ALL_EVENT_ID,
													 wxDefaultPosition, wxDefaultSize, wxLC_REPORT  | wxSUNKEN_BORDER //|  wxLC_SINGLE_SEL
													 );
	 
	m_listctrl->InsertColumn(0, wxString::FromUTF8("Name"));
	m_listctrl->InsertColumn(1, wxString::FromUTF8("Key"));
	 
	//m_listctrl->SetItem(0, 0,wxString::FromUTF8("太郎"));
	//m_listctrl->SetItem(0, 1, wxString::FromUTF8("あいうえお"));
	 
	VALUE content = rb_hash_aref(option, ID2SYM(rb_intern("content")));
	int size = static_cast<int>(RARRAY_LEN(content));
	 
	//std::cout << "size (in list_ctrl.cpp) " << size << std::endl;
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
		 
		m_listctrl->SetItemData(i, i); 
		 
	}
	 
	++StaticFunc::ALL_EVENT_ID;
	 
}


VALUE ListCtrl::Call(int nargs, VALUE *args)
{
	VALUE func_name = args[0];
	std::string func_name_str = std::string(StringValuePtr(func_name));
	VALUE res;
	 
	if (func_name_str == "get_selection") {
		int cnt = m_listctrl->GetSelectedItemCount();
		long item = -1;
		res = rb_ary_new();
		 
		for (int i = 0; i < cnt; ++i) {
			 
			item = m_listctrl->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
			 
			if (item != -1) {
				int data = m_listctrl->GetItemData(item);
				rb_ary_push(res, INT2NUM(data));
			}
		}
	}
	 
	return res;
}
