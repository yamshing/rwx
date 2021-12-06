#include "static_text.h"
#include "static_func.h"
 
 
StaticText::StaticText(int nargs, VALUE *args)
{
	std::cout << "nargs (in static_func.h) " << nargs << std::endl;
	App* app_p = static_cast<App*>(wxTheApp);

	VALUE parent = args[0];
	VALUE content = args[1];
	std::string content_str; 
	StaticFunc::ValueToString(content, content_str);
	 
	wxWindow* parent_p = static_cast<wxWindow*>(app_p->GetObjectFromMap(parent));
	 
	//StaticText* static_text_p;
	 
	if (nargs >= 4) {
		 
		int x = NUM2INT(args[2]);
		int y = NUM2INT(args[3]);
		 
		if (nargs == 4) {
			 
			m_static_text_p = new wxStaticText(parent_p, wxID_ANY, wxString::FromUTF8(content_str), wxPoint(x,y));
			 
		}else if (nargs == 6) {
			 
			int w = NUM2INT(args[4]);
			int h = NUM2INT(args[5]);
			m_static_text_p = new wxStaticText(parent_p, wxID_ANY, wxString::FromUTF8(content_str), wxPoint(x,y), wxSize(w,h));
			 
			std::cout << "call base const (in static_text.cpp) "  << std::endl;
			 
		}
		 
	}else{
		m_static_text_p = new wxStaticText(parent_p, wxID_ANY, wxString::FromUTF8(content_str));
	}

	//std::cout << "static target value (in static_func.h) " << target << std::endl;

}
void StaticText::Call(int nargs, VALUE *args)
{
	 
	VALUE func_name = args[0];
	std::string func_name_str = std::string(StringValuePtr(func_name));
	App* app_p = static_cast<App*>(wxTheApp);
	if (func_name_str == "test") {
		 
	}
}
 
