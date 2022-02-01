#ifndef MOD_SIMPLE_H
#define MOD_SIMPLE_H 
 
#include "wx/wx.h"
#include "ruby.h"

class Simple :public wxObject
{
	public:
		Simple(int nargs, VALUE *args);
		 
		virtual ~Simple (){
			 
		};
		 
};
#endif 
