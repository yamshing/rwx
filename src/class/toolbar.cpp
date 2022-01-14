#include "toolbar.h"
#include "static_func.h"
 
void Toolbar::Call(int nargs, VALUE *args)
{
	VALUE func_name = args[0];
	std::string func_name_str = std::string(StringValuePtr(func_name));
	 
	if (func_name_str == "add_tool") {
		 
		//std::cout << "nargs (in toolbar.cpp) " << nargs << std::endl;
		//wxBitmap icon = wxBitmap("assets/save.bmp");
		wxBitmap icon = wxNullBitmap;
		 
		VALUE hash = args[1];
		VALUE type = rb_hash_aref(hash, ID2SYM(rb_intern("type")));
		VALUE title = rb_hash_aref(hash, ID2SYM(rb_intern("title")));
		VALUE content = rb_hash_aref(hash, ID2SYM(rb_intern("content")));
		VALUE label = rb_hash_aref(hash, ID2SYM(rb_intern("label")));
		VALUE desc = rb_hash_aref(hash, ID2SYM(rb_intern("desc")));
		VALUE cb_inst = rb_hash_aref(hash, ID2SYM(rb_intern("cb_inst")));
		VALUE cb_name = rb_hash_aref(hash, ID2SYM(rb_intern("cb_name")));
		 
		 
		std::string type_str;
		StaticFunc::ValueToString(type, type_str);
		 
		if (type_str == "button") {
			 
			std::string title_str;
			StaticFunc::ValueToString(title, title_str);
			std::string label_str;
			StaticFunc::ValueToString(label, label_str);
			std::string desc_str;
			StaticFunc::ValueToString(desc, desc_str);
			g_menu_callback_inst_map[StaticFunc::ALL_EVENT_ID] = cb_inst;
			g_menu_callback_name_map[StaticFunc::ALL_EVENT_ID] = cb_name;
			m_wx_toolbar_p-> AddTool(StaticFunc::ALL_EVENT_ID, wxString::FromUTF8(title_str), icon, wxNullBitmap, wxITEM_NORMAL,wxString::FromUTF8(label_str), wxString::FromUTF8(desc_str));
			//m_wx_toolbar_p-> InsertTool(0, StaticFunc::ALL_EVENT_ID, wxString::FromUTF8(title_str), icon);
			 
			m_wx_toolbar_p-> Bind(wxEVT_MENU, &Toolbar::OnMenu, this, StaticFunc::ALL_EVENT_ID);
			StaticFunc::ALL_EVENT_ID ++;
			 
		}else if(type_str == "combo"){
			 
			wxComboBox *combo = new wxComboBox(m_wx_toolbar_p, StaticFunc::ALL_EVENT_ID, wxEmptyString, wxDefaultPosition, wxDefaultSize ); 
			 
			int size = static_cast<int>(RARRAY_LEN(content));
			for (int i = 0; i < size; ++i) {
				VALUE menu_content = rb_ary_entry(content,i);
				std::string menu_content_str;
				StaticFunc::ValueToString(menu_content, menu_content_str);
				combo->Append(wxString::FromUTF8(menu_content_str));
			}
			 
			m_wx_toolbar_p->AddControl(combo, "Combo Label");
			 
			g_menu_callback_inst_map[StaticFunc::ALL_EVENT_ID] = cb_inst;
			g_menu_callback_name_map[StaticFunc::ALL_EVENT_ID] = cb_name;
			m_combobox_map[StaticFunc::ALL_EVENT_ID] = combo;
			 
			m_wx_toolbar_p-> Bind(wxEVT_COMBOBOX, &Toolbar::OnCombo, this, StaticFunc::ALL_EVENT_ID);
			StaticFunc::ALL_EVENT_ID ++;
			 
		}else if(type_str == "drop"){
			 
			std::string title_str;
			StaticFunc::ValueToString(title, title_str);
			std::string label_str;
			StaticFunc::ValueToString(label, label_str);
			std::string desc_str;
			StaticFunc::ValueToString(desc, desc_str);
			 
			int drop_menu_id = StaticFunc::ALL_EVENT_ID;
			m_wx_toolbar_p-> AddTool(drop_menu_id, wxString::FromUTF8(title_str), icon, wxNullBitmap, wxITEM_DROPDOWN, wxString::FromUTF8(label_str), wxString::FromUTF8(desc_str));
			StaticFunc::ALL_EVENT_ID ++;
			wxMenu* menu = new wxMenu;
			 
			int size = static_cast<int>(RARRAY_LEN(content));
			for (int i = 0; i < size; ++i) {
				VALUE menu_content = rb_ary_entry(content,i);
				std::string menu_content_str;
				StaticFunc::ValueToString(menu_content, menu_content_str);
				if (menu_content_str != "") {
					 
					menu->Append(StaticFunc::ALL_EVENT_ID, wxString::FromUTF8(menu_content_str));
					m_wx_toolbar_p-> Bind(wxEVT_MENU, &Toolbar::OnDropMenu, this, StaticFunc::ALL_EVENT_ID);
					 
					m_drop_index_offset_map[StaticFunc::ALL_EVENT_ID] = drop_menu_id + 1;
					g_menu_callback_inst_map[StaticFunc::ALL_EVENT_ID] = cb_inst;
					g_menu_callback_name_map[StaticFunc::ALL_EVENT_ID] = cb_name;
					 
					StaticFunc::ALL_EVENT_ID ++;
					 
				}else{
					menu->AppendSeparator();
				}
			}
			m_wx_toolbar_p->SetDropdownMenu(drop_menu_id, menu);
			 
		}else if(type_str == "check"){
			 
			int size = static_cast<int>(RARRAY_LEN(content));

			int drop_menu_id = StaticFunc::ALL_EVENT_ID;
			 
			m_wx_toolbar_p->AddSeparator();
			for (int i = 0; i < size; ++i) {
				VALUE menu_content = rb_ary_entry(content,i);
				std::string menu_content_str;
				StaticFunc::ValueToString(menu_content, menu_content_str);
				 
				m_wx_toolbar_p->AddCheckTool(StaticFunc::ALL_EVENT_ID, wxString::FromUTF8(menu_content_str), wxNullBitmap, wxNullBitmap, wxString::FromUTF8(menu_content_str));
				m_wx_toolbar_p-> Bind(wxEVT_MENU, &Toolbar::OnCheck, this, StaticFunc::ALL_EVENT_ID);
				 
				g_menu_callback_inst_map[StaticFunc::ALL_EVENT_ID] = cb_inst;
				g_menu_callback_name_map[StaticFunc::ALL_EVENT_ID] = cb_name;
				 
				m_drop_index_offset_map[StaticFunc::ALL_EVENT_ID] = drop_menu_id;
				 
				StaticFunc::ALL_EVENT_ID ++;
				 
			}
			 
			m_wx_toolbar_p->AddSeparator();
			 
			 
		}else if(type_str == "radio"){
			 
			int size = static_cast<int>(RARRAY_LEN(content));

			int drop_menu_id = StaticFunc::ALL_EVENT_ID;
			 
			m_wx_toolbar_p->AddSeparator();
			for (int i = 0; i < size; ++i) {
				VALUE menu_content = rb_ary_entry(content,i);
				std::string menu_content_str;
				StaticFunc::ValueToString(menu_content, menu_content_str);
				 
				m_wx_toolbar_p->AddRadioTool(StaticFunc::ALL_EVENT_ID, wxString::FromUTF8(menu_content_str), wxNullBitmap, wxNullBitmap, wxString::FromUTF8(menu_content_str));
				m_wx_toolbar_p-> Bind(wxEVT_MENU, &Toolbar::OnCheck, this, StaticFunc::ALL_EVENT_ID);
				 
				g_menu_callback_inst_map[StaticFunc::ALL_EVENT_ID] = cb_inst;
				g_menu_callback_name_map[StaticFunc::ALL_EVENT_ID] = cb_name;
				 
				m_drop_index_offset_map[StaticFunc::ALL_EVENT_ID] = drop_menu_id;
				 
				StaticFunc::ALL_EVENT_ID ++;
				 
			}
			m_wx_toolbar_p->AddSeparator();
			 
		}
		m_wx_toolbar_p->Realize();
	}
}
 
void Toolbar::OnCheck(wxCommandEvent& event)
{
	//std::cout << "on check (in test_wx.cpp) " << std::endl;
	int menu_id = event.GetId();
	//std::cout << "menu_id (in test_wx.cpp) " << menu_id << std::endl;
	int drop_menu_id  = menu_id - m_drop_index_offset_map[menu_id];
	 
	VALUE callback_inst = g_menu_callback_inst_map[menu_id];
	VALUE callback_name = g_menu_callback_name_map[menu_id];
	 
	std::string callback_name_str;
	StaticFunc::ValueToString(callback_name, callback_name_str);
	ID callback_def_id = rb_intern(callback_name_str.c_str());
	VALUE arg[1];
	arg[0] = INT2NUM(drop_menu_id); 
	 
	rb_funcall2(callback_inst, callback_def_id,1,arg);
	
}

void Toolbar::OnDropMenu(wxCommandEvent& event)
{
	int menu_id = event.GetId();
	int drop_menu_id  = menu_id - m_drop_index_offset_map[menu_id];
	 
	VALUE callback_inst = g_menu_callback_inst_map[menu_id];
	VALUE callback_name = g_menu_callback_name_map[menu_id];
	 
	std::string callback_name_str;
	StaticFunc::ValueToString(callback_name, callback_name_str);
	ID callback_def_id = rb_intern(callback_name_str.c_str());
	VALUE arg[1];
	arg[0] = INT2NUM(drop_menu_id); 
	 
	rb_funcall2(callback_inst, callback_def_id,1,arg);
}
 
void Toolbar::OnMenu(wxCommandEvent& event)
{
	//std::cout << "onmenu (in test_wx.cpp) " << std::endl;
	int menu_id = event.GetId();
	//std::cout << "menu_id (in test_wx.cpp) " << menu_id << std::endl;
	 
	VALUE callback_inst = g_menu_callback_inst_map[menu_id];
	VALUE callback_name = g_menu_callback_name_map[menu_id];
	 
	std::string callback_name_str;
	StaticFunc::ValueToString(callback_name, callback_name_str);
	ID callback_def_id = rb_intern(callback_name_str.c_str());
	rb_funcall(callback_inst, callback_def_id,0);
}
 
void Toolbar::OnCombo(wxCommandEvent& event)
{
	//std::cout << "oncombo (in test_wx.cpp) " << std::endl;
	int menu_id = event.GetId();
	//std::cout << "menu_id (in test_wx.cpp) " << menu_id << std::endl;
	wxComboBox* combo = m_combobox_map[menu_id];
	int selected = combo->GetCurrentSelection();
	 
	VALUE callback_inst = g_menu_callback_inst_map[menu_id];
	VALUE callback_name = g_menu_callback_name_map[menu_id];
	 
	std::string callback_name_str;
	StaticFunc::ValueToString(callback_name, callback_name_str);
	ID callback_def_id = rb_intern(callback_name_str.c_str());
	VALUE arg[1];
	arg[0] = INT2NUM(selected); 
	rb_funcall2(callback_inst, callback_def_id,1,arg);
}

