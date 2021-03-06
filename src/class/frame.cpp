
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
	wxString os_name =  wxPlatformInfo::Get().GetOperatingSystemFamilyName(); 
	static const char *const rwx_xpm[] = {};
	 
	if (os_name == _T("Windows")) {
		SetIcon(wxICON(rwx));
	}

	 
	this -> Bind(wxEVT_TEXT_COPY, &Frame::OnCopy, this);
	this -> Bind(wxEVT_TEXT_PASTE, &Frame::OnPaste, this);
	this -> Bind(wxEVT_CONTEXT_MENU, &Frame::OnContextMenu, this);
	this -> Bind(wxEVT_COMMAND_MENU_SELECTED, &Frame::OnContextMenuSelected, this);
	 
}
 
void Frame::OnContextMenuSelected(wxCommandEvent& event)
{
	 
	wxString str;
	 
	switch (event.GetId()) {
		case 0:
			str = "Context Menu command 1";
			break;
		case 1:
			str = "Context Menu command 2";
			break;
		case 2:
			str = "Context Menu command 3";
			break;
		default:
			str = "Uknown command?!";
	}
	std::cout << "str (in frame.cpp) " << str << std::endl;

}
 
void Frame::OnContextMenu(wxEvent& event)
{

	wxMenu menu;

	menu.Append(0, "Context Menu command 1");
	menu.Append(1, "Context Menu command 2");
	menu.Append(2, "Context Menu command 3");

	PopupMenu(&menu); 
	 
}
void Frame::OnCopy(wxEvent& event)
{
	//wxWindow *foc = wxWindow::FindFocus();
	//wxPostEvent(foc, event);
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
		 
	}else if (func_name_str == "close") {
		 
		Close(); 
		 
	}else if (func_name_str == "show") {
		 
		Show();
		 
	}else if (func_name_str == "hide") {
		 
		Hide();
		 
	}else if (func_name_str == "set_fullscreen") {
		 
		ShowFullScreen(true); 
		 
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
