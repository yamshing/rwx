#ifndef TOOLBAR_H
#define TOOLBAR_H 
 
#include "wx/wx.h"
#include "ruby.h"

class Toolbar :public wxObject
{
private:
	 
	wxToolBar* m_wx_toolbar_p;
	void OnMenu(wxCommandEvent& event);
	void OnCombo(wxCommandEvent& event);
	void OnDropMenu(wxCommandEvent& event);
	void OnCheck(wxCommandEvent& event);
	void OnSlider(wxCommandEvent& event);
	 
	//int m_toolbar_item_count;
	 
	std::unordered_map<int, VALUE> g_menu_callback_inst_map{};
	std::unordered_map<int, VALUE> g_menu_callback_name_map{};
	std::unordered_map<int, wxComboBox*> m_combobox_map{};
	std::unordered_map<int, int> m_drop_index_offset_map{};
	std::unordered_map<int, wxSlider*> m_slider_map{};
	 
public: 
	Toolbar(){
		//m_toolbar_item_count = 0;
	};
	 
	virtual ~Toolbar (){
		delete m_wx_toolbar_p; 
	};
	void Call(int nargs, VALUE *args);
	 
	void SetWxToolbarP(wxToolBar* wx_toolbar_p){
		m_wx_toolbar_p = wx_toolbar_p;
	};

	wxToolBar* GetWxToolbarP(){
		return m_wx_toolbar_p;
	};
	 
};
#endif
