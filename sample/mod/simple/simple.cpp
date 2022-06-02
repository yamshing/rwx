
#include "simple.h"
 
Simple::Simple(int nargs, VALUE *args)
{
	std::cout << "SIMPLE MODULE OK (in simple.cpp) " << std::endl;
}
 
VALUE Simple::Call(int nargs, VALUE *args)
{
	VALUE func_name = args[0];
	VALUE result = INT2NUM(-1);
	 
	std::string func_name_str = std::string(StringValuePtr(func_name));
	std::cout << "call (in simple.cpp) " << std::endl;
	 
	/*if (func_name_str == "get_selection") {
		//int combo_selected = m_combo->GetSelection();
		//result = INT2NUM(combo_selected);
	}
	*/
	 
	return result;
	 
}
 
