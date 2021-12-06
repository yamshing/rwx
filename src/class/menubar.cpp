#include "menubar.h"
#include "app.h"
#include "frame.h"
#include <vector>
#include <unordered_map>
#include "static_func.h"
 

void Menubar::AddMenu(VALUE menu, VALUE title, VALUE content_arr)
{
	 
	int size = static_cast<int>(RARRAY_LEN(content_arr));
	 
	wxMenu *menu_ptr = new wxMenu();
	 
	g_object_map[menu] = menu_ptr;
	 
	std::string title_str;
		 
	StaticFunc::ValueToString(title, title_str);
	 
	App* app_p = static_cast<App*>(wxTheApp);
	 
	this->Append(menu_ptr, wxString::FromUTF8(title_str));
	 
	for (int i = 0; i < size; ++i) {
		 
		VALUE menu_content = rb_ary_entry(content_arr,i);

		VALUE title = rb_hash_aref(menu_content, ID2SYM(rb_intern("title")));
		VALUE label = rb_hash_aref(menu_content, ID2SYM(rb_intern("label")));
		VALUE cb_inst = rb_hash_aref(menu_content, ID2SYM(rb_intern("cb_inst")));
		VALUE cb_name = rb_hash_aref(menu_content, ID2SYM(rb_intern("cb_name")));
		 
		std::string title_str;
		StaticFunc::ValueToString(title, title_str);
		 
		std::string label_str;
		StaticFunc::ValueToString(label, label_str);
	
		menu_ptr->Append(StaticFunc::ALL_EVENT_ID, wxString::FromUTF8(title_str), wxString::FromUTF8(label_str));
		 
		g_menu_callback_inst_map[StaticFunc::ALL_EVENT_ID] = cb_inst;
		g_menu_callback_name_map[StaticFunc::ALL_EVENT_ID] = cb_name;
		 
		this->Bind(wxEVT_MENU, &Menubar::OnMenu, this, StaticFunc::ALL_EVENT_ID);
		 
		StaticFunc::ALL_EVENT_ID ++;
		 
	}
	 
}

 
void Menubar::OnMenu(wxCommandEvent& event)
{
	 
	std::cout << "onmenu (in test_wx.cpp) " << std::endl;
	int menu_id = event.GetId();
	std::cout << "menu_id (in test_wx.cpp) " << menu_id << std::endl;
	 
	VALUE callback_inst = g_menu_callback_inst_map[menu_id];
	VALUE callback_name = g_menu_callback_name_map[menu_id];
	 
	std::string callback_name_str;
	StaticFunc::ValueToString(callback_name, callback_name_str);
	ID callback_def_id = rb_intern(callback_name_str.c_str());
	rb_funcall(callback_inst, callback_def_id,0);
	 
}
