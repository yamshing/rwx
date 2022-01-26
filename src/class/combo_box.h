#ifndef COMBO_BOX_H
#define COMBO_BOX_H 
 
#include "wx/wx.h"
#include "ruby.h"
 
#include "wx/combo.h"
#include "wx/odcombo.h"


class ComboBox :public wxObject
{
	private:
		wxOwnerDrawnComboBox* m_combo;
		 
	public:
		ComboBox(int nargs, VALUE *args);
		virtual ~ComboBox (){
			delete m_combo; 
		};
		 
		wxOwnerDrawnComboBox* GetComboBox(){
			return m_combo;
		};
		VALUE Call(int nargs, VALUE *args);
		 
};
	







#endif
