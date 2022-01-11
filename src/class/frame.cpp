
#include "app.h"
#include "frame.h"
 
#include <sstream>
#include <vector>
#include <unordered_map>

#include "static_func.h"
 
extern "C" VALUE librwx_Frame;
 
Frame::Frame(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title)
{
	
	this -> Connect(wxEVT_TEXT_COPY, wxEventHandler(Frame::OnCopy), NULL, this);
	 
}
 
void Frame::OnCopy(wxEvent& event)
{
	std::cout << "oncopy (in grid.cpp) " << std::endl;
}

void Frame::CallOnInit()
{
	std::string method_name = "on_init";
	bool defined = StaticFunc::CheckFuncExist(librwx_Frame, method_name);
	 
	if (defined) {
		VALUE args[0];
		StaticFunc::CallRwxFunc(m_rwx_frame, method_name, 0, args);
	}
	 
}

void Frame::Call(int nargs, VALUE *args)
{
	VALUE func_name = args[0];
	std::string func_name_str = std::string(StringValuePtr(func_name));
	 
	if (func_name_str == "set_size") {
		int w = NUM2INT(args[1]);
		int h = NUM2INT(args[2]);
		SetSize(wxSize(w,h));
		 
	}else if (func_name_str == "set_sizer") {
		 
		App* app_p = static_cast<App*>(wxTheApp);
		std::cout << "set sizer (in frame.cpp) "  << std::endl;
		VALUE sizer_val = args[1];
		std::cout << "sizer_val (in frame.cpp) " << sizer_val << std::endl;
		Sizer* sizer_p = dynamic_cast<Sizer*>(app_p->GetObjectFromMap(sizer_val));
		wxSizer* wxsizer_p = sizer_p->GetSizer();
		SetSizer(wxsizer_p);
		 
	}
	 
}
