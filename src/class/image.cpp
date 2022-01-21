#include "image.h"
#include "static_func.h"
 
Image::Image(int nargs, VALUE *args)
{
	m_wx_image = nullptr;
	App* app_p = static_cast<App*>(wxTheApp);
	 
	if (nargs > 0) {
		VALUE option = args[0];
		if (rb_obj_is_kind_of(option, rb_cHash) && rb_funcall(option, rb_intern("has_key?"),1,ID2SYM(rb_intern("file_name")))) {
			 
			VALUE file_name = rb_hash_aref(option, ID2SYM(rb_intern("file_name")));
			std::string file_name_str = std::string(StringValuePtr(file_name));
			wxString file_name_wxstr = wxString::FromUTF8(file_name_str);
			 
			std::vector<unsigned char> out_bin;
			app_p -> GetEmbedBinObject(out_bin, "aaa");
			 
			/*
			std::stringstream ss;
			 
			for (int i = 0; i < out_bin.size(); ++i) {
				ss << out_bin[i];
			}
			std::string text = ss.str();
			 
			std::cout << "text (in image.cpp) " << text << std::endl;
			*/
			 
			m_wx_image  = new wxImage();
			m_wx_image-> LoadFile(file_name_wxstr,  wxBITMAP_TYPE_ANY);
			 
		}else{
			 
		}
		rb_p(option);
	}
	 
}
