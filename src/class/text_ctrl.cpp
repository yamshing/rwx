
#include "text_ctrl.h"
#include "app.h"
#include "static_func.h"
 

TextCtrl::TextCtrl(int nargs, VALUE *args)
{
	App* app_p = static_cast<App*>(wxTheApp);
	VALUE parent = args[0];
	VALUE content = args[1];
	std::string content_str; 
	StaticFunc::ValueToString(content, content_str);
	wxWindow* parent_p = static_cast<wxWindow*>(app_p->GetObjectFromMap(parent));
	m_text_ctrl_p = new wxTextCtrl(parent_p, wxID_ANY, wxString::FromUTF8(content_str) );

}


void TextCtrl::Call(int nargs, VALUE *args)
{
	 
	VALUE func_name = args[0];
	std::string func_name_str = std::string(StringValuePtr(func_name));
	App* app_p = static_cast<App*>(wxTheApp);
	if (func_name_str == "test") {
		 
	}
	 
}
 
