#ifndef BUTTON_H
#define BUTTON_H 
 
#include "wx/wx.h"
#include "ruby.h"

class Button :public wxObject
{
	private:
		wxButton* m_button;
		std::unordered_map<int, VALUE> m_menu_callback_inst_map{};
		std::unordered_map<int, VALUE> m_menu_callback_name_map{};
		void OnClick(wxCommandEvent& event);
		 
	public:
		Button(int nargs, VALUE *args);
		virtual ~Button (){
			delete m_button;
		};
		 
		wxButton* GetButton(){
			return m_button;
		};
		void SetButton(wxButton* button){
			m_button = button;
		};
		 
};
	
#endif
