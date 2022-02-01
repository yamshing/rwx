#ifndef MOD_STATIC_FUNC_H
#define MOD_STATIC_FUNC_H 

#include <wx/wx.h> 
#include "app.h"
#include "static_func.h"

/*DEFINE*/
 
extern "C" VALUE rb_cFloat;
extern "C" VALUE rb_cInteger;
extern "C" VALUE rb_cSymbol;
extern "C" VALUE rb_cHash;
 
extern "C" VALUE rb_cTrueClass;
extern "C" VALUE rb_cFalseClass;
extern "C" VALUE rb_cNilClass;
 

struct ModStaticFunc
{
	static bool check_class_name(VALUE target, std::string must_be_str)
	{
		
		std::string class_str = std::string(rb_class2name(CLASS_OF(target)));
		bool res = (class_str == must_be_str);
		return res;
		 
	}
	static VALUE mod_app_callback(VALUE target, char* func_name_str,  int nargs, VALUE *args)
	{
		VALUE result = Qtrue;
		App* app_p = static_cast<App*>(wxTheApp);
		 
		 
		/*CALL*/
		 
		return result;
		 
	}

};
#endif

