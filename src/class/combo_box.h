#ifndef COMBO_BOX_H
#define COMBO_BOX_H 
 
#include "wx/wx.h"
#include "ruby.h"

class ComboBox :public wxObject
{
	private:
		wxComboBox* m_combo;
		 
	public:
		ComboBox(int nargs, VALUE *args);
		virtual ~ComboBox (){
			delete m_combo; 
		};
		 
		wxComboBox* GetComboBox(){
			return m_combo;
		};
		void SetComboBox(wxComboBox* combo){
			m_combo = combo;
		};
		VALUE Call(int nargs, VALUE *args);
		 
};
	







#endif
