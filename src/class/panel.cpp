
#include "panel.h"
#include "app.h"
#include "static_func.h"
 
 
extern "C" VALUE librwx_Panel;
 


void Panel::Call(int nargs, VALUE *args)
{
	VALUE func_name = args[0];
	std::string func_name_str = std::string(StringValuePtr(func_name));
	App* app_p = static_cast<App*>(wxTheApp);
	 
	if (func_name_str == "add_sizer") {
		 
		VALUE sizer = args[1];
		Sizer* sizer_p = static_cast<Sizer*>(app_p->GetObjectFromMap(sizer));
		 
		wxSizer* wxsizer_p = sizer_p->GetSizer();
		 
		//wxTextCtrl* text_ctrl = new wxTextCtrl(this, wxID_ANY, wxString(), wxPoint(0,0), wxSize(80,30));
		//wxsizer_p->Add(text_ctrl); //, 0,wxALIGN_CENTER_VERTICAL);
		 
		SetSizerAndFit(wxsizer_p);
		 
	}
}
 
void Panel::CallOnInit(VALUE self)
{
	std::string method_name = "on_init";
	bool defined = StaticFunc::CheckFuncExist(librwx_Panel, method_name);
	 
	if (defined) {
		VALUE args[0];
		StaticFunc::CallRwxFunc(self, method_name, 0, args);
	}
	 
}
