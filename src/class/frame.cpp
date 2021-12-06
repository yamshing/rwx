
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
		 
	}
	 
}
