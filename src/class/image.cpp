#include "image.h"
#include "static_func.h"
 
Image::Image(int nargs, VALUE *args)
{
	App* app_p = static_cast<App*>(wxTheApp);
	if (nargs > 0) {
		VALUE option = args[0];
		if (rb_obj_is_kind_of(option, rb_cHash) && rb_funcall(option, rb_intern("has_key?"),1,ID2SYM(rb_intern("file_name")))) {
			std::cout << "option file name (in image.cpp) "  << std::endl;
		}else{
			std::cout << "no opt (in image.cpp) "  << std::endl;
		}
		rb_p(option);
	}
	 
}
