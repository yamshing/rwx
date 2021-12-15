
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
 
VALUE CheckBox::Call(int nargs, VALUE *args)
{
	VALUE func_name = args[0];
	VALUE result = Qfalse;
	 
	std::string func_name_str = std::string(StringValuePtr(func_name));
	 
	if (func_name_str == "get_value") {
		bool checked = m_checkbox->GetValue();
		if (checked) {
			result = Qtrue;
		}else{
			result = Qfalse;
		}
	}else if (func_name_str == "set_value") {
		VALUE check_val = args[1];
		bool check_bool = RTEST(check_val);
		 
		m_checkbox->SetValue(check_bool);
		 
		 
		//std::cout << "check_bool (in check_box.cpp) " << check_bool << std::endl;
		 
	}
	return result;
}
 
