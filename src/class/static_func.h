#ifndef STATIC_FUNC_H
#define STATIC_FUNC_H 
extern "C"{ 
	void set_app_pointer(VALUE(*cb)(VALUE, char* , int, VALUE*));
}
 
#include <sstream>
#include <cstring>
#include "canvas.h"
#include "app.h"
#include "frame.h"
#include "menubar.h"
#include "dc.h"
#include "toolbar.h"
#include "splitter.h"
#include "panel.h"
#include "sizer.h"
#include "static_text.h"
#include "text_ctrl.h"
#include "button.h"
#include "radio_box.h"
#include "check_box.h"
#include "notebook.h"
#include "list_box.h"
#include "list_ctrl.h"
 
#include <wx/wx.h> 

extern "C" VALUE rb_cFloat;
extern "C" VALUE rb_cInteger;
extern "C" VALUE rb_cSymbol;
extern "C" VALUE rb_cTrueClass;
extern "C" VALUE rb_cFalseClass;
extern "C" VALUE rb_cNilClass;
 

struct StaticFunc
{
	static int ALL_EVENT_ID;
	 
	static bool CheckFuncExist(VALUE klass, std::string method_name)
	{
		ID method_def_id = rb_intern("method_defined?");
		VALUE def_args[1];
		def_args[0] = rb_str_new_cstr(method_name.c_str());
		VALUE defined = rb_funcall2(klass, method_def_id,1,def_args);
		return (defined == Qtrue);
	}
	 
	static void CallRwxFunc(VALUE target, std::string name, int narg, VALUE* args)
	{
		ID method_id = rb_intern(name.c_str());
		rb_funcall2(target, method_id,narg,args); 
	}
	 
	static bool check_class_name(VALUE target, std::string must_be_str)
	{
		
		std::string class_str = std::string(rb_class2name(CLASS_OF(target)));
		//std::cout << "class_str (in static_func.h) " << class_str << std::endl;
		bool res = (class_str == must_be_str);
		return res;
		 
	}
	static void frame_callback(VALUE target, char* func_name,  int nargs, VALUE *args)
	{
		std::string func_name_str = std::string(func_name);
		App* app_p = static_cast<App*>(wxTheApp);
		 
		if (func_name_str == "init_frame"){
			 
			Frame* frame_p = new Frame("Minimal wxWidgets App");
			app_p->SetFrameP(frame_p);
			app_p -> SetObjectToMap(target, frame_p);
			frame_p->m_rwx_frame = target;
			frame_p->CallOnInit();
			frame_p -> Show(true);
			 
		}else if (func_name_str == "frame_call"){
			 
			Frame* frame_p = app_p->GetFrameP();
			frame_p->Call(nargs, args);
		}
	}
	static void menu_callback(VALUE target, char* func_name,  int nargs, VALUE *args)
	{
		std::string func_name_str = std::string(func_name);
		App* app_p = static_cast<App*>(wxTheApp);
	
		if (func_name_str == "init_menubar"){

			VALUE parent = args[0];

			if (!check_class_name(parent, "Rwx::Frame")) {
				std::cerr << "*** PLEASE SET FRAME CLASS AS PARENT FOR MENUBAR ! ***"  << std::endl;
				return;
			}

			Menubar* menubar_p = new Menubar();

			app_p -> SetObjectToMap(target, menubar_p);

			Frame* frame_p = static_cast<Frame*>(app_p->GetObjectFromMap(parent));

			frame_p->SetMenuBar(menubar_p);
		}else if (func_name_str == "init_menu"){

			VALUE parent = args[0];
			if (!check_class_name(parent, "Rwx::MenuBar")) {
				std::cerr << "*** PLEASE SET MENUBAR CLASS AS PARENT FOR MENU ! ***"  << std::endl;
				return;
			}

			VALUE title = args[1];
			VALUE content_arr = args[2];

			Menubar* menubar_p = static_cast<Menubar*>(app_p->GetObjectFromMap(parent));
			if (menubar_p) {
				menubar_p->AddMenu(target, title, content_arr);
			}
		}else if (func_name_str == "init_toolbar"){
			 
			VALUE parent = args[0];
			 
			if (!check_class_name(parent, "Rwx::Frame")) {
				std::cerr << "*** PLEASE SET FRAME CLASS AS PARENT FOR TOOLBAR ! ***"  << std::endl;
				return;
			}
			 
			Frame* frame_p = static_cast<Frame*>(app_p->GetObjectFromMap(parent));
			 
			Toolbar* toolbar_p = new Toolbar();
			app_p -> SetObjectToMap(target, toolbar_p);
			 
			//long style = wxTB_FLAT | wxTB_DOCKABLE | wxTB_TEXT;
			//style &= ~(wxTB_HORIZONTAL | wxTB_VERTICAL | wxTB_BOTTOM | wxTB_RIGHT | wxTB_HORZ_LAYOUT); 
			//long style = wxTB_NOICONS | wxTB_TEXT | wxTB_VERTICAL | wxTB_DOCKABLE;
			 
			long style = wxTB_HORIZONTAL | wxTB_TEXT | wxTB_HORZ_LAYOUT;
			 
			wxToolBarBase* wx_toolbar_p = frame_p->CreateToolBar(style, 1);
			toolbar_p->SetWxToolbarP(wx_toolbar_p);
			 
			 
		}else if (func_name_str == "toolbar_call"){
			 
			Toolbar* toolbar_p = static_cast<Toolbar*>(app_p->GetObjectFromMap(target));
			toolbar_p->Call(nargs, args);
		}
	}
	 
	static void canvas_callback(VALUE target, char* func_name,  int nargs, VALUE *args)
	{
		std::string func_name_str = std::string(func_name);
		App* app_p = static_cast<App*>(wxTheApp);
		 
		if (func_name_str == "init_canvas"){
			 
			VALUE dc = rb_iv_get(target, "@dc");
			VALUE parent = args[0];
			wxWindow* parent_p = static_cast<wxWindow*>(app_p->GetObjectFromMap(parent));
			//Frame* frame_p = static_cast<Frame*>(app_p->GetObjectFromMap(parent));
			Canvas* canvas_p = new Canvas(parent_p, target, dc);
			app_p -> SetObjectToMap(target, canvas_p);
			canvas_p->CallOnInit(target);
			 
			 
		}else if (func_name_str == "dc_call"){
			 
			DC* dc_p = static_cast<DC*>(app_p->GetObjectFromMap(target));
			dc_p->Call(nargs, args);

		}else if (func_name_str == "canvas_call"){
			 
			Canvas* canvas_p = static_cast<Canvas*>(app_p->GetObjectFromMap(target));
			canvas_p->Call(nargs, args);
			 
		}
	}

	static void panel_callback(VALUE target, char* func_name,  int nargs, VALUE *args)
	{
		std::string func_name_str = std::string(func_name);
		App* app_p = static_cast<App*>(wxTheApp);
		 
		if (func_name_str == "init_splitter"){
			VALUE parent = args[0];
			if (!check_class_name(parent, "Rwx::Frame")) {
				std::cerr << "*** PLEASE SET FRAME CLASS AS PARENT FOR TOOLBAR ! ***"  << std::endl;
				return;
			}

			Frame* frame_p = static_cast<Frame*>(app_p->GetObjectFromMap(parent));
			Splitter* splitter_p = new Splitter(frame_p);
			app_p -> SetObjectToMap(target, splitter_p);
		}else if (func_name_str == "init_panel"){

			VALUE parent = args[0];
			wxWindow* parent_p = static_cast<wxWindow*>(app_p->GetObjectFromMap(parent));
			Panel* panel_p = new Panel(parent_p, nargs, args);
			//std::cout << "init panel (in static_func.h) "  << std::endl; 
			rb_p(target);
			app_p -> SetObjectToMap(target, panel_p);
			panel_p->CallOnInit(target);
			 
		}else if (func_name_str == "splitter_call"){
			Splitter* splitter_p = static_cast<Splitter*>(app_p->GetObjectFromMap(target));
			splitter_p->Call(nargs, args);
			 
		}else if (func_name_str == "panel_call"){
			 
			Panel* panel_p = static_cast<Panel*>(app_p->GetObjectFromMap(target));
			panel_p->Call(nargs, args);
			 
		}else if (check_class_name(target,"Rwx::Sizer") && func_name_str == "init_sizer"){
			 
			Sizer* sizer_p = new Sizer(nargs, args);
			//panel_p->CallOnInit(target);
			app_p -> SetObjectToMap(target, sizer_p);
			 
		}else if (func_name_str == "sizer_call"){
			 
			Sizer* sizer_p = static_cast<Sizer*>(app_p->GetObjectFromMap(target));
			sizer_p->Call(nargs, args);
			 
		}else if (func_name_str == "init_notebook"){
			 
			VALUE parent = args[0];
			wxWindow* parent_p = static_cast<wxWindow*>(app_p->GetObjectFromMap(parent));
			Notebook* notebook_p = new Notebook(parent_p, nargs, args);
			 
			app_p -> SetObjectToMap(target, notebook_p);
			 
		}else if (func_name_str == "notebook_call"){
			 
			Notebook* notebook_p = static_cast<Notebook*>(app_p->GetObjectFromMap(target));
			notebook_p->Call(nargs, args);
			 
		}
	}
	static VALUE input_callback(VALUE target, char* func_name,  int nargs, VALUE *args)
	{
		std::string func_name_str = std::string(func_name);
		App* app_p = static_cast<App*>(wxTheApp);
		 
		VALUE result = Qtrue;
		 
		if (check_class_name(target,"Rwx::StaticText") && func_name_str == "init_static_text"){
			 
			StaticText* static_text_p = new StaticText(nargs, args);
			app_p -> SetObjectToMap(target, static_text_p);
			 
		}else if (check_class_name(target,"Rwx::TextCtrl") && func_name_str == "init_text_ctrl"){
			 
			TextCtrl* text_ctrl_p = new TextCtrl(nargs, args);
			app_p -> SetObjectToMap(target, text_ctrl_p);

		}else if (check_class_name(target,"Rwx::TextCtrl") && func_name_str == "text_ctrl_call"){
			 
			TextCtrl* text_ctrl_p = static_cast<TextCtrl*>(app_p->GetObjectFromMap(target));
			result = text_ctrl_p->Call(nargs, args);
			 
		}else if (check_class_name(target,"Rwx::Button") && func_name_str == "init_button"){
			 
			Button* button_p = new Button(nargs, args);
			app_p -> SetObjectToMap(target, button_p);

		}else if (check_class_name(target,"Rwx::RadioBox") && func_name_str == "init_radiobox"){
			 
			RadioBox* radio_p = new RadioBox(nargs, args);
			app_p -> SetObjectToMap(target, radio_p);
			 
		}else if (check_class_name(target,"Rwx::CheckBox") && func_name_str == "init_checkbox"){
			 
			CheckBox* checkbox_p = new CheckBox(nargs, args);
			app_p -> SetObjectToMap(target, checkbox_p);
			 
			//std::cout << "checkbox init (in static_func.h) "  << std::endl;
			 
		}else if (check_class_name(target,"Rwx::ListBox") && func_name_str == "init_listbox"){
			 
			ListBox* listbox_p = new ListBox(nargs, args);
			app_p -> SetObjectToMap(target, listbox_p);
			std::cout << "init and set list box (in static_func.h) " <<  std::endl;
			 
		}else if (check_class_name(target,"Rwx::ListCtrl") && func_name_str == "init_listctrl"){
			ListCtrl* listctrl_p = new ListCtrl(nargs, args);
			app_p -> SetObjectToMap(target, listctrl_p);
			 
		}
		 
	}
	
	 
	 
	static VALUE app_callback(VALUE target, char* func_name,  int nargs, VALUE *args)
	{
		std::string func_name_str = std::string(func_name);
		App* app_p = static_cast<App*>(wxTheApp);
		 
		//std::cout << "func_name_str (in static_func.h) " << func_name_str << ',' << func_name << std::endl;
		 
		VALUE result = Qtrue;
		 
		if (func_name_str == "init_app") {
			app_p->SetRwxApp(target);
		}else if (func_name_str == "init_frame" || func_name_str == "frame_call") {
			frame_callback(target, func_name, nargs, args);
		}else if (func_name_str == "init_menubar" || func_name_str == "init_menu" || func_name_str == "init_toolbar" || func_name_str == "toolbar_call"){
			menu_callback(target, func_name, nargs, args);
		}else if (func_name_str == "init_canvas" || func_name_str == "dc_call" || func_name_str == "canvas_call"){
			canvas_callback(target, func_name, nargs, args);
		}else if (func_name_str == "init_splitter" || func_name_str == "notebook_call"|| func_name_str == "init_notebook" || func_name_str == "splitter_call" ||  func_name_str == "init_panel" || func_name_str == "panel_call" || func_name_str == "init_sizer" || func_name_str == "sizer_call"){
			panel_callback(target, func_name, nargs, args);
		}else if (func_name_str == "init_static_text" || func_name_str == "init_text_ctrl" || func_name_str == "init_button"  || func_name_str == "init_radiobox" || func_name_str == "init_checkbox" || func_name_str == "text_ctrl_call" || func_name_str == "init_listbox" || func_name_str == "init_listctrl"  ){
			result = input_callback(target, func_name, nargs, args);
			 
		}else if (func_name_str == "checkbox_call" ) {
			CheckBox* checkbox_p = static_cast<CheckBox*>(app_p->GetObjectFromMap(target));
			result = checkbox_p->Call(nargs, args);
		}else if (func_name_str == "radiobox_call" ) {
			RadioBox* radiobox_p = static_cast<RadioBox*>(app_p->GetObjectFromMap(target));
			result = radiobox_p->Call(nargs, args);
			 
		}
		 
		return result;
		 
	}
	 
	 
	static void ValueToString(VALUE val, std::string &str)
	{
		char* txt = StringValuePtr(val);
		std::stringstream ss;
		ss << txt;
		str = ss.str();
		 
	}
	static void HexCharToRGB(char* hex_char, int* r, int* g, int* b, int* alpha)
	{

		size_t len = std::strlen(hex_char);
		 
		//std::cout << "len (in static_func.h) " << len << hex_char << std::endl;
		 
		if (len == 7) {
			std::sscanf(hex_char, "#%02x%02x%02x", r, g, b);
			*alpha = 255;
		}else if(len == 9){
			std::sscanf(hex_char, "#%02x%02x%02x%02x", r, g, b, alpha);
		}
	}
};
#endif

