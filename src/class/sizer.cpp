#include "sizer.h"
#include "static_func.h"
 
Sizer::Sizer(int nargs, VALUE *args)
{

	VALUE type = args[0];
	std::string type_str; 
	StaticFunc::ValueToString(type, type_str);
	 
	VALUE dir = args[1];
	std::string dir_str; 
	StaticFunc::ValueToString(dir, dir_str);

	m_type = type_str;
	m_dir = dir_str;
	 
	//std::cout << "m_type (in sizer.cpp) " << m_type << std::endl;
	 
	if (m_dir == "horizontal") {
		m_sizer = new wxBoxSizer(wxHORIZONTAL);
	}else{
		m_sizer = new wxBoxSizer(wxVERTICAL);
	}
	 
	//std::cout << "init msizer (in sizer.cpp) " << std::endl;

}
void Sizer::Call(int nargs, VALUE *args)
{
	VALUE func_name = args[0];
	std::string func_name_str = std::string(StringValuePtr(func_name));
	App* app_p = static_cast<App*>(wxTheApp);
	 
	if (func_name_str == "add") {
		VALUE child = args[1];
		 
		//std::cout << "sizer add (in sizer.cpp) "  << std::endl;
		rb_p(child);
		//std::cout << "-------- (in sizer.cpp) "  << std::endl;
		 
		Sizer* sizer_child_p = dynamic_cast<Sizer*>(app_p->GetObjectFromMap(child));
		 
		if (sizer_child_p) {
			wxSizer* wxchild_p = sizer_child_p->GetSizer();
			m_sizer -> Add(wxchild_p);
			return;
		}
		 
		StaticText* static_child_p = dynamic_cast<StaticText*>(app_p->GetObjectFromMap(child));
		 
		if (static_child_p) {
			                                                  //border apply dir, border width
			m_sizer -> Add(static_child_p->GetStaticTextP(), wxALIGN_LEFT | wxTOP, 3); //, 0, wxALIGN_CENTER, 0); //, 0, wxALIGN_CENTER_VERTICAL);
			return;
		}
		 
		TextCtrl* text_ctrl_child_p = dynamic_cast<TextCtrl*>(app_p->GetObjectFromMap(child));
		 
		if (text_ctrl_child_p) {
			if (m_dir == "horizontal") {
				m_sizer -> Add(text_ctrl_child_p->GetTextCtrlP(), 0, wxALIGN_CENTER_VERTICAL);
			}else{
				m_sizer -> Add(text_ctrl_child_p->GetTextCtrlP());
			}
			return;
		}
		 
		Button* button_child_p = dynamic_cast<Button*>(app_p->GetObjectFromMap(child));
		if (button_child_p) {
			std::cout << "button add (in sizer.cpp) " << std::endl;
			m_sizer -> Add(button_child_p->GetButton());
			return;
		}

		RadioBox* radio_child_p = dynamic_cast<RadioBox*>(app_p->GetObjectFromMap(child));
		if (radio_child_p) {
			m_sizer -> Add(radio_child_p->GetRadioBox());
			return;
		}
		 
		CheckBox* check_child_p = dynamic_cast<CheckBox*>(app_p->GetObjectFromMap(child));
		if (check_child_p) {
			m_sizer -> Add(check_child_p->GetCheckBox());
			return;
		}
		 
		ListBox* list_child_p = dynamic_cast<ListBox*>(app_p->GetObjectFromMap(child));
		if (list_child_p) {
			m_sizer -> Add(list_child_p->GetListBox());
			return;
		}
		ListCtrl* listctrl_child_p = dynamic_cast<ListCtrl*>(app_p->GetObjectFromMap(child));
		if (listctrl_child_p) {
			m_sizer -> Add(listctrl_child_p->GetListCtrl());
			return;
		}
	
		 
		std::cout << "PLEASE ADD GETOBJECT IN SIZER.CPP "  << std::endl;
		 
		 
	}else if (func_name_str == "add_spacer") {
		 
		int space = NUM2INT(args[1]);
		m_sizer->AddSpacer(space);
		 
	}
}
