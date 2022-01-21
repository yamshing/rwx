#include "image.h"
#include "static_func.h"
 
Image::Image(int nargs, VALUE *args)
{
	App* app_p = static_cast<App*>(wxTheApp);
	VALUE parent = args[0];
	VALUE content = args[1];
	std::cout << "image ctor call (in image.cpp) "  << std::endl;

}
