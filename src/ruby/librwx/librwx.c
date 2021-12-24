#include <stdio.h>
#include "internal.h"

VALUE librwx_Namespace;
 
VALUE librwx_App;
VALUE librwx_Frame;
VALUE librwx_MenuBar;
VALUE librwx_Menu;
VALUE librwx_Canvas;
VALUE librwx_DC;
VALUE librwx_Panel;
VALUE librwx_Splitter;
VALUE librwx_Sizer;
VALUE librwx_StaticText;
VALUE librwx_TextCtrl;
VALUE librwx_Toolbar;
VALUE librwx_Button;
VALUE librwx_Notebook;
 
VALUE librwx_RadioBox;
VALUE librwx_CheckBox;
VALUE librwx_ListBox;
 
VALUE librwx_ListCtrl;
 
VALUE librwx_TreeList;
VALUE librwx_TreeCtrl;
 
VALUE librwx_AuiManager;;
 
 
VALUE(*global_app_callback_ptr)(VALUE, char* , int, VALUE*);
 
void set_app_pointer(VALUE(*cb)(VALUE, char* , int, VALUE*))
{
	global_app_callback_ptr = cb;
}
 

static VALUE
librwx_canvas_initialize(int argc, VALUE *argv, VALUE self)
{
	if (argc == 1) {
		 
		ID method_def_id = rb_intern("new");
		VALUE def_args[0];
		VALUE dc = rb_class_new_instance(0,0, librwx_DC);
		 
		VALUE parent = argv[0];
		rb_iv_set(self, "@parent", parent);
		rb_iv_set(self, "@dc", dc);
		 
		global_app_callback_ptr(self,"init_canvas", argc, argv);
		 
	}
}

 
#define STRINGIFY(x) #x 

#define INITIALIZE(target) \
static VALUE librwx_##target##_initialize(int argc, VALUE *argv, VALUE self)\
{\
	global_app_callback_ptr(self,STRINGIFY(init_##target) , argc, argv);\
}\

#define GENERIC_CALL(target) \
static VALUE librwx_##target (int argc, VALUE *argv, VALUE self, char* func_name)\
{\
	VALUE arg_arr[argc + 1];\
	arg_arr[0] = rb_str_new_cstr(func_name);\
	 \
	for (int i = 1; i < argc + 1; ++i) {\
		arg_arr[i] = argv[i - 1];\
	}\
	VALUE result = global_app_callback_ptr(self, #target, argc + 1, arg_arr);\
	return result;\
}\
 
#define FUNC_TO_GENERIC(target,name) \
static VALUE librwx_##target##_##name (int argc, VALUE *argv, VALUE self)\
{\
	return librwx_##target##_call(argc, argv, self, #name );\
}\

INITIALIZE(text_ctrl)
INITIALIZE(static_text)
INITIALIZE(toolbar)
INITIALIZE(panel)
INITIALIZE(sizer)
INITIALIZE(splitter)
INITIALIZE(menu)
INITIALIZE(menubar)
INITIALIZE(app)
INITIALIZE(frame)
INITIALIZE(button)
INITIALIZE(radiobox)
INITIALIZE(checkbox)
INITIALIZE(notebook)
	 
INITIALIZE(listbox)
INITIALIZE(listctrl)
INITIALIZE(treelist)
INITIALIZE(treectrl)
INITIALIZE(auimanager)
	 
	 
GENERIC_CALL(dc_call)
GENERIC_CALL(frame_call)
GENERIC_CALL(toolbar_call)
GENERIC_CALL(splitter_call)
GENERIC_CALL(panel_call)
GENERIC_CALL(sizer_call)
GENERIC_CALL(notebook_call)
GENERIC_CALL(canvas_call)
GENERIC_CALL(checkbox_call)
	 
GENERIC_CALL(text_ctrl_call)
GENERIC_CALL(radiobox_call)

GENERIC_CALL(auimanager_call)

GENERIC_CALL(treectrl_call)
	 
	 
FUNC_TO_GENERIC(frame,set_size)
FUNC_TO_GENERIC(frame,set_sizer)
	 
FUNC_TO_GENERIC(dc,set_brush)
FUNC_TO_GENERIC(dc,set_pen)
FUNC_TO_GENERIC(dc,draw_circle)
FUNC_TO_GENERIC(toolbar,add_tool)
FUNC_TO_GENERIC(splitter,split)
FUNC_TO_GENERIC(panel,add_sizer)
FUNC_TO_GENERIC(sizer,add)
FUNC_TO_GENERIC(sizer,add_spacer)
FUNC_TO_GENERIC(notebook,add)
FUNC_TO_GENERIC(canvas,refresh)
FUNC_TO_GENERIC(checkbox,get_value)
FUNC_TO_GENERIC(checkbox,set_value)
	 
FUNC_TO_GENERIC(text_ctrl,get_value)
FUNC_TO_GENERIC(text_ctrl,set_value)
	 
FUNC_TO_GENERIC(treectrl,get_selection)

FUNC_TO_GENERIC(radiobox,get_selection)
FUNC_TO_GENERIC(radiobox,set_selection)
	 
FUNC_TO_GENERIC(auimanager,add_pane)



void
Init_LibRwx(void)
{
	
	librwx_Namespace = rb_define_module("Rwx");
	 
	librwx_App  = rb_define_class_under(librwx_Namespace, "App", rb_cObject);
	rb_define_method(librwx_App, "initialize", librwx_app_initialize, -1);
	 
	librwx_Frame  = rb_define_class_under(librwx_Namespace, "Frame", rb_cObject);
	 
	rb_define_method(librwx_Frame, "initialize", librwx_frame_initialize, -1);
	rb_define_method(librwx_Frame, "set_size", librwx_frame_set_size, -1);
	rb_define_method(librwx_Frame, "set_sizer", librwx_frame_set_sizer, -1);
	 
	librwx_MenuBar  = rb_define_class_under(librwx_Namespace, "MenuBar", rb_cObject);
	rb_define_method(librwx_MenuBar, "initialize", librwx_menubar_initialize, -1);
	 
	librwx_Menu  = rb_define_class_under(librwx_Namespace, "Menu", rb_cObject);
	rb_define_method(librwx_Menu, "initialize", librwx_menu_initialize, -1);

	librwx_Canvas  = rb_define_class_under(librwx_Namespace, "Canvas", rb_cObject);
	 
	rb_define_method(librwx_Canvas, "initialize", librwx_canvas_initialize, -1);
	rb_define_method(librwx_Canvas, "refresh", librwx_canvas_refresh, -1);

	librwx_DC  = rb_define_class_under(librwx_Namespace, "DC", rb_cObject);
	 
	rb_define_method(librwx_DC, "draw_circle", librwx_dc_draw_circle, -1);
	rb_define_method(librwx_DC, "set_brush", librwx_dc_set_brush, -1);
	rb_define_method(librwx_DC, "set_pen", librwx_dc_set_pen, -1);
	 
	librwx_Toolbar  = rb_define_class_under(librwx_Namespace, "Toolbar", rb_cObject);
	rb_define_method(librwx_Toolbar, "initialize", librwx_toolbar_initialize, -1);
	rb_define_method(librwx_Toolbar, "add_tool", librwx_toolbar_add_tool, -1);
	 
	 
	librwx_Panel  = rb_define_class_under(librwx_Namespace, "Panel", rb_cObject);
	rb_define_method(librwx_Panel, "initialize", librwx_panel_initialize, -1);
	rb_define_method(librwx_Panel, "add_sizer", librwx_panel_add_sizer, -1);
	 
	librwx_Splitter  = rb_define_class_under(librwx_Namespace, "Splitter", rb_cObject);
	rb_define_method(librwx_Splitter, "initialize", librwx_splitter_initialize, -1);
	rb_define_method(librwx_Splitter, "split", librwx_splitter_split, -1);
	 
	librwx_Sizer  = rb_define_class_under(librwx_Namespace, "Sizer", rb_cObject);
	rb_define_method(librwx_Sizer, "initialize", librwx_sizer_initialize, -1);
	rb_define_method(librwx_Sizer, "add", librwx_sizer_add, -1);
	rb_define_method(librwx_Sizer, "add_spacer", librwx_sizer_add_spacer, -1);

	librwx_StaticText  = rb_define_class_under(librwx_Namespace, "StaticText", rb_cObject);
	rb_define_method(librwx_StaticText, "initialize", librwx_static_text_initialize, -1);

	librwx_TextCtrl  = rb_define_class_under(librwx_Namespace, "TextCtrl", rb_cObject);
	rb_define_method(librwx_TextCtrl, "initialize", librwx_text_ctrl_initialize, -1);
	rb_define_method(librwx_TextCtrl, "get_value", librwx_text_ctrl_get_value, -1);
	rb_define_method(librwx_TextCtrl, "set_value", librwx_text_ctrl_set_value, -1);

	librwx_Button  = rb_define_class_under(librwx_Namespace, "Button", rb_cObject);
	rb_define_method(librwx_Button, "initialize", librwx_button_initialize, -1);
	 
	librwx_RadioBox  = rb_define_class_under(librwx_Namespace, "RadioBox", rb_cObject);
	rb_define_method(librwx_RadioBox, "initialize", librwx_radiobox_initialize, -1);
	rb_define_method(librwx_RadioBox, "get_selection", librwx_radiobox_get_selection, -1);
	rb_define_method(librwx_RadioBox, "set_selection", librwx_radiobox_set_selection, -1);
	 
	librwx_CheckBox  = rb_define_class_under(librwx_Namespace, "CheckBox", rb_cObject);
	rb_define_method(librwx_CheckBox, "initialize", librwx_checkbox_initialize, -1);
	rb_define_method(librwx_CheckBox, "get_value", librwx_checkbox_get_value, -1);
	rb_define_method(librwx_CheckBox, "set_value", librwx_checkbox_set_value, -1);
	
	librwx_Notebook  = rb_define_class_under(librwx_Namespace, "Notebook", rb_cObject);
	rb_define_method(librwx_Notebook, "initialize", librwx_notebook_initialize, -1);
	rb_define_method(librwx_Notebook, "add", librwx_notebook_add, -1);
	 
	librwx_ListBox  = rb_define_class_under(librwx_Namespace, "ListBox", rb_cObject);
	rb_define_method(librwx_ListBox, "initialize", librwx_listbox_initialize, -1);
	 
	librwx_ListCtrl  = rb_define_class_under(librwx_Namespace, "ListCtrl", rb_cObject);
	rb_define_method(librwx_ListCtrl, "initialize", librwx_listctrl_initialize, -1);
	 
	librwx_TreeList  = rb_define_class_under(librwx_Namespace, "TreeList", rb_cObject);
	rb_define_method(librwx_TreeList, "initialize", librwx_treelist_initialize, -1);
	
	librwx_AuiManager  = rb_define_class_under(librwx_Namespace, "AuiManager", rb_cObject);
	rb_define_method(librwx_AuiManager, "initialize", librwx_auimanager_initialize, -1);
	rb_define_method(librwx_AuiManager, "add_pane", librwx_auimanager_add_pane, -1);
	 
	librwx_TreeCtrl  = rb_define_class_under(librwx_Namespace, "TreeCtrl", rb_cObject);
	rb_define_method(librwx_TreeCtrl, "initialize", librwx_treectrl_initialize, -1);
	rb_define_method(librwx_TreeCtrl, "get_selection", librwx_treectrl_get_selection, -1);
	 
	 
}

