
#include "splitter.h"
#include "app.h"
 
void Splitter::Call(int nargs, VALUE *args)
{
	VALUE func_name = args[0];
	std::string func_name_str = std::string(StringValuePtr(func_name));
	App* app_p = static_cast<App*>(wxTheApp);
	 
	if (func_name_str == "split") {
		//std::cout << "split call (in splitter.cpp) "  << std::endl;
		VALUE left = args[1];
		VALUE right = args[2];
		//std::cout << "left (in splitter.cpp) " << left << std::endl;
		 
		wxWindow* left_p = static_cast<wxWindow*>(app_p->GetObjectFromMap(left));
		wxWindow* right_p = static_cast<wxWindow*>(app_p->GetObjectFromMap(right));
		 
		SplitVertically(left_p, right_p, 100);
		 
	}
}
