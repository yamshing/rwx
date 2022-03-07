
#include "text_ctrl.h"
#include "app.h"
#include "static_func.h"
#include "string_util.h"
 

TextCtrl::TextCtrl(int nargs, VALUE *args)
{
	App* app_p = static_cast<App*>(wxTheApp);
	VALUE parent = args[0];
	VALUE content = args[1];
	 
	VALUE option = 0;
	 
	if (nargs > 2) {
		option = args[2];
	}
	 
	std::string content_str; 
	StaticFunc::ValueToString(content, content_str);
	wxWindow* parent_p = static_cast<wxWindow*>(app_p->GetObjectFromMap(parent));

	 
	if (option != 0) {
		 
		if (rb_funcall(option, rb_intern("has_key?"),1,ID2SYM(rb_intern("style")))) {

			VALUE style = rb_hash_aref(option, ID2SYM(rb_intern("style")));
			std::string style_str = std::string(StringValuePtr(style));
			int w = 150;
			int h = 200;

			if (rb_funcall(option, rb_intern("has_key?"),1,ID2SYM(rb_intern("w")))) {
				VALUE w_val = rb_hash_aref(option, ID2SYM(rb_intern("w")));
				w = NUM2INT(w_val);
			}
			if (rb_funcall(option, rb_intern("has_key?"),1,ID2SYM(rb_intern("h")))) {
				VALUE h_val = rb_hash_aref(option, ID2SYM(rb_intern("h")));
				h = NUM2INT(h_val);
			}
			 
			if (style_str == "multi_line") {
				m_text_ctrl_p = new wxTextCtrl(parent_p, wxID_ANY, wxString::FromUTF8(content_str), wxDefaultPosition,wxSize(w, h), wxTE_MULTILINE);
			}
			 
		}
		 
	}else{

		m_text_ctrl_p = new wxTextCtrl(parent_p, wxID_ANY, wxString::FromUTF8(content_str) );
		 
	}
	 
}


VALUE TextCtrl::Call(int nargs, VALUE *args)
{
	 
	VALUE func_name = args[0];
	std::string func_name_str = std::string(StringValuePtr(func_name));
	App* app_p = static_cast<App*>(wxTheApp);
	VALUE result = Qfalse;
	 
	if (func_name_str == "get_value") {
		 
		wxString value_wxstr = m_text_ctrl_p->GetValue();
		std::string value_str;
		StringUtil::WxStringToStdString(value_wxstr, &value_str);
		 
		VALUE res_str =  rb_utf8_str_new(value_str.c_str(),value_str.length());
		 
		result = res_str;
		 
	}else if (func_name_str == "set_value") {
		 
		VALUE val_to_set = args[1];
		std::string val_to_set_str;
		StaticFunc::ValueToString(val_to_set, val_to_set_str);
		 
		std::cout << "set val (in text_ctrl.cpp) " << val_to_set_str << std::endl;
		 
		wxString val_to_set_wxstr = wxString::FromUTF8(val_to_set_str);
		m_text_ctrl_p->SetValue(val_to_set_wxstr);
		 
	}
	 
	return result;
	 
}
 
