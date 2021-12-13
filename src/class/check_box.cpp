
#include "check_box.h"
#include "static_func.h"

CheckBox::CheckBox(int nargs, VALUE *args)
{

	VALUE parent = args[0];
	VALUE option = args[1];
	 
	VALUE label = rb_hash_aref(option, ID2SYM(rb_intern("label")));
	std::string label_str; 
	StaticFunc::ValueToString(label, label_str);
	
	VALUE cb_inst = rb_hash_aref(option, ID2SYM(rb_intern("cb_inst")));
	VALUE cb_name = rb_hash_aref(option, ID2SYM(rb_intern("cb_name")));
	 
	 
	App* app_p = static_cast<App*>(wxTheApp);
	wxWindow* parent_p = static_cast<wxWindow*>(app_p->GetObjectFromMap(parent));
	 
	m_checkbox = new wxCheckBox(parent_p, StaticFunc::ALL_EVENT_ID,
													 wxString::FromUTF8(label_str),
													 wxDefaultPosition, wxDefaultSize
													 );
	 
	++StaticFunc::ALL_EVENT_ID;
	 
}
void CheckBox::Call(int nargs, VALUE *args)
{
	VALUE func_name = args[0];
	std::string func_name_str = std::string(StringValuePtr(func_name));
	if (func_name_str == "get_value") {
		std::cout << "get value call (in check_box.cpp) "  << std::endl;
	}
	 
}
 

/*void Button::OnClick(wxCommandEvent& event)
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
*/
