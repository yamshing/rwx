#ifndef PANEL_H
#define PANEL_H 
 
#include "wx/wx.h"
#include "ruby.h"
#include "wx/notebook.h"



class Panel: public wxScrolledWindow
{

	public:
		Panel(wxWindow* parent, int nargs, VALUE *args) : wxScrolledWindow(parent) 
		{
			 
			if (nargs > 1) {
				 
				VALUE option = args[1];
				 
				VALUE with_scroll = rb_hash_aref(option, ID2SYM(rb_intern("with_scroll")));
				if (TYPE(with_scroll) != T_NIL) {
					if (RTEST(with_scroll)) {
						SetScrollRate( 10, 10 );
						SetScrollbars(10,10,100,100);
					}
				}
			}
		};
		 
		virtual ~Panel (){};
		void Call(int nargs, VALUE *args);
		void CallOnInit(VALUE self);

		 
	private:
		 
};



#endif
