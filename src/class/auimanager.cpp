
#include "auimanager.h"
#include "static_func.h"
 
AuiManager::AuiManager(int nargs, VALUE *args)
{
	VALUE parent = args[0];
	VALUE option = args[1];
	
	App* app_p = static_cast<App*>(wxTheApp);
	wxWindow* parent_p = static_cast<wxWindow*>(app_p->GetObjectFromMap(parent));
	std::cout << "auimanager constr (in auimanager.cpp) "  << std::endl;
	 
}
