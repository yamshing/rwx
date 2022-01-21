#include "image.h"
#include "static_func.h"
#include <wx/mstream.h>
 
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

			m_wx_image  = new wxImage();

			if (m_wx_image-> LoadFile(file_name_wxstr,  wxBITMAP_TYPE_ANY)) {

				std::cout << "load ok"  << std::endl;

			}
			 
		}else if (rb_obj_is_kind_of(option, rb_cHash) && rb_funcall(option, rb_intern("has_key?"),1,ID2SYM(rb_intern("embed_name")))) {
			 
			VALUE file_name = rb_hash_aref(option, ID2SYM(rb_intern("embed_name")));
			std::string file_name_str = std::string(StringValuePtr(file_name));
			 
			std::vector<unsigned char> out_bin{};
			app_p -> GetEmbedBinObject(out_bin, file_name_str);

			m_wx_image  = new wxImage();

			if (out_bin.size() > 0) {

				std::cout << "out_bin.size() (in image.cpp) " << out_bin.size() << std::endl;

				char val_char_arr[out_bin.size()];
				int cnt = 0;
				for (unsigned char v : out_bin) {
					val_char_arr[cnt] = v;
					printf("%x ", v);
					++cnt;
				}
				wxMemoryInputStream image_stream(val_char_arr, cnt);
				if (m_wx_image-> LoadFile(image_stream,  wxBITMAP_TYPE_ANY)) {

					std::cout << "load ok (in image.cpp) " << std::endl;

				}else{
					std::cout << "no load (in image.cpp) " << std::endl;
				}
			}

		}else{

		}

			//rb_p(option);
	}

}
