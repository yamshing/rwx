#ifndef MOD_STATIC_FUNC_H
#define MOD_STATIC_FUNC_H 

#include <wx/wx.h> 
#include "app.h"

extern "C" VALUE rb_cFloat;
extern "C" VALUE rb_cInteger;
extern "C" VALUE rb_cSymbol;
extern "C" VALUE rb_cHash;
 
extern "C" VALUE rb_cTrueClass;
extern "C" VALUE rb_cFalseClass;
extern "C" VALUE rb_cNilClass;
 

struct ModStaticFunc
{
	static VALUE mod_app_callback(VALUE target, char* func_name,  int nargs, VALUE *args)
	{
		VALUE result = Qtrue;
		App* app_p = static_cast<App*>(wxTheApp);
		 
		std::cout << "func_name (in mod_static_func.h) " << func_name << std::endl;
		 
		return result;
		 
	}

};
#endif

