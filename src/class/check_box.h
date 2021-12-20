#ifndef CHECKBOX_H
#define CHECKBOX_H 
 
#include "wx/wx.h"
#include "ruby.h"

class CheckBox :public wxObject
{
	private:
		wxCheckBox* m_checkbox;
		std::unordered_map<int, VALUE> m_menu_callback_inst_map{};
		std::unordered_map<int, VALUE> m_menu_callback_name_map{};
		void OnClick(wxCommandEvent& event);
		 
	public:
		CheckBox(int nargs, VALUE *args);
		virtual ~CheckBox (){
			delete m_checkbox;
		};
		 
		wxCheckBox* GetCheckBox(){
			return m_checkbox;
		};
		void SetCheckBox(wxCheckBox* checkbox){
			m_checkbox = checkbox;
		};
		 
		VALUE Call(int nargs, VALUE *args);
		 
};
	
#endif
