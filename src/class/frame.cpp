
#include "app.h"
#include "frame.h"
 
#include <sstream>
#include <vector>
#include <unordered_map>
#include <wx/clipbrd.h> 

#include "string_util.h"
#include "static_func.h"
 
extern "C" VALUE librwx_Frame;
 
Frame::Frame(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title)
{
	
	this -> Connect(wxEVT_TEXT_COPY, wxEventHandler(Frame::OnCopy), NULL, this);
	this -> Connect(wxEVT_TEXT_PASTE, wxEventHandler(Frame::OnPaste), NULL, this);
	 
}
 
void Frame::OnCopy(wxEvent& event)
{
	std::cout << "on copy (in frame.cpp) "  << std::endl;
}
void Frame::OnPaste(wxEvent& event)
{
	std::string method_name = "on_paste";
	bool defined = StaticFunc::CheckFuncExist(librwx_Frame, method_name);
	 
	if (defined) {
		wxString copy_data;
		wxString cur_field;
		wxString cur_line;
		if (wxTheClipboard->Open())
		{
			if (wxTheClipboard->IsSupported( wxDF_TEXT ))
			{
				wxTextDataObject data;
				wxTheClipboard->GetData( data );
				copy_data = data.GetText();
				 
				VALUE args[1];
				std::string value_str;;
				StringUtil::WxStringToStdString(copy_data, &value_str);
				VALUE res_str =  rb_utf8_str_new(value_str.c_str(),value_str.length());
				args[0] = res_str;
				StaticFunc::CallRwxFunc(m_rwx_frame, method_name, 1, args);
				 
			}
			 
			wxTheClipboard->Close();
		}
	}
	
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
