#ifndef MENUBAR_H
#define MENUBAR_H 

#include "wx/wx.h"
#include "ruby.h"

class Menubar : public wxMenuBar
{
public: 
	Menubar (){
		//g_menu_count =0;
	};
	virtual ~Menubar (){};
	void OnMenu(wxCommandEvent& event);
	void ValueToString(VALUE val, std::string &str);
	void AddMenu(VALUE menu,  VALUE title, VALUE content_arr);
	 
private:
	//int g_menu_count;
	std::unordered_map<VALUE, wxObject*> g_object_map{};
	std::unordered_map<int, VALUE> g_menu_callback_inst_map{};
	std::unordered_map<int, VALUE> g_menu_callback_name_map{};
	 
};
#endif 
