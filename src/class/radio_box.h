#ifndef RADIOBOX_H
#define RADIOBOX_H 
 
#include "wx/wx.h"
#include "ruby.h"

class RadioBox :public wxObject
{
	private:
		wxRadioBox* m_radio;
		std::unordered_map<int, VALUE> m_menu_callback_inst_map{};
		std::unordered_map<int, VALUE> m_menu_callback_name_map{};
		 
	public:
		RadioBox(int nargs, VALUE *args);
		virtual ~RadioBox (){};
		 
		wxRadioBox* GetRadioBox(){
			return m_radio;
		};
		void SetRadioBox(wxRadioBox* radio){
			m_radio = radio;
		};
		VALUE Call(int nargs, VALUE *args);
		 
};
	



#endif 
