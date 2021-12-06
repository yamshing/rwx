#include "button.h"
#include "static_func.h"

Button::Button(int nargs, VALUE *args)
{

	VALUE parent = args[0];
	VALUE option = args[1];
	 
	//VALUE parent =  rb_hash_aref(option, ID2SYM(rb_intern("parent")));
	VALUE content = rb_hash_aref(option, ID2SYM(rb_intern("label")));
	VALUE cb_inst = rb_hash_aref(option, ID2SYM(rb_intern("cb_inst")));
	VALUE cb_name = rb_hash_aref(option, ID2SYM(rb_intern("cb_name")));
	 
	 
	std::string content_str; 
	StaticFunc::ValueToString(content, content_str);
	 
	std::cout << "button init (in button.cpp) "  << std::endl;
	rb_p(parent);
	 
	App* app_p = static_cast<App*>(wxTheApp);

	wxWindow* parent_p = static_cast<wxWindow*>(app_p->GetObjectFromMap(parent));
	m_button = new wxButton(parent_p, StaticFunc::ALL_EVENT_ID,  wxString::FromUTF8(content_str));
	m_menu_callback_inst_map[StaticFunc::ALL_EVENT_ID] = cb_inst;
	m_menu_callback_name_map[StaticFunc::ALL_EVENT_ID] = cb_name;
	 
	std::cout << "bind button (in button.cpp) " << std::endl;
	m_button -> Bind(wxEVT_BUTTON, &Button::OnClick, this, StaticFunc::ALL_EVENT_ID);
	 
	++ StaticFunc::ALL_EVENT_ID;
}


void Button::OnClick(wxCommandEvent& event)
{
	 
	int id = event.GetId();
	std::cout << "button click (in button.cpp) " << id << std::endl;
	 
	VALUE callback_inst = m_menu_callback_inst_map[id];
	VALUE callback_name = m_menu_callback_name_map[id];
	 
	std::string callback_name_str;
	StaticFunc::ValueToString(callback_name, callback_name_str);
	ID callback_def_id = rb_intern(callback_name_str.c_str());
	rb_funcall(callback_inst, callback_def_id,0);
	 
}

