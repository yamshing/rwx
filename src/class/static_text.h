#ifndef STATIC_TEXT_H
#define STATIC_TEXT_H 
 
#include "wx/wx.h"
#include "ruby.h"

class StaticText: public wxObject
{
	private:
		wxStaticText* m_static_text_p;
		 
	public:
		wxStaticText* GetStaticTextP(){
			return m_static_text_p;
		};
		 
		StaticText (int nargs, VALUE *args);
		 
		virtual ~StaticText (){
			delete m_static_text_p;
		};
		void Call(int nargs, VALUE *args);
		 
};
 
#endif
