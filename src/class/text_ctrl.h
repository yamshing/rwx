#ifndef TEXT_CTRL_H
#define TEXT_CTRL_H 
 
#include "wx/wx.h"
#include "ruby.h"

class TextCtrl: public wxTextCtrl
{
	private:
		wxTextCtrl* m_text_ctrl_p;
		
	public:
		//TextCtrl (wxWindow* parent, wxWindowID id, const wxString& label ): wxTextCtrl(parent, id, label )
		//{};

		TextCtrl(int nargs, VALUE *args);
		 
		virtual ~TextCtrl (){
			delete m_text_ctrl_p;
		};
		 
		VALUE Call(int nargs, VALUE *args);
		 
		wxTextCtrl* GetTextCtrlP(){
			return m_text_ctrl_p;
		};
		 
};
 
#endif
