#include "slider.h"
#include "static_func.h"


Slider::Slider(int nargs, VALUE *args)
{
	VALUE parent = args[0];
	VALUE option = args[1];
	App* app_p = static_cast<App*>(wxTheApp);
	 
	std::cout << "slider ctor (in slider.cpp) " << std::endl;
	
}
