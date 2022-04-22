#include "image.h"
#include "static_func.h"
#include "string_util.h"
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
			 
			if (app_p -> GetEmbedBinObject(out_bin, file_name_str)) {
				 
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
				 
				//------------------------------
				// search in asset folder for debug
				//  
				std::string file_path_str = "./asset/";
				file_path_str += file_name_str;
				 
				std::cout << "file_path (in image.cpp) " << file_path_str << std::endl;
				 
				wxString file_name_wxstr = wxString::FromUTF8(file_path_str);
				m_wx_image  = new wxImage();

				if (m_wx_image-> LoadFile(file_name_wxstr,  wxBITMAP_TYPE_ANY)) {
					 
				}
			}
			 
		}else{

		}

			//rb_p(option);
	}else{
		m_wx_image  = new wxImage();
	}

}
 
VALUE Image::Call(int nargs, VALUE *args)
{
	VALUE func_name = args[0];
	std::string func_name_str = std::string(StringValuePtr(func_name));
	App* app_p = static_cast<App*>(wxTheApp);

	VALUE result = Qfalse;
	 
	if (func_name_str == "capture_desktop") {
		 
		wxScreenDC screen;
		wxSize size = screen.GetSize();
		int screen_w = size.GetWidth();
		int screen_h = size.GetHeight();
		 
		//m_wx_image->Create(screen_w, screen_h);
		 
		m_wx_image->Destroy();
		 
		wxBitmap* bitmap = new wxBitmap(screen_w, screen_h);
		Capture(bitmap, 0,0, screen_w, screen_h, 0);
		m_wx_image  = new wxImage(bitmap->ConvertToImage());
		 
		//bitmap->SaveFile("./test.png", wxBITMAP_TYPE_PNG);
		 
	}
	return result;
}
 
bool Image::Capture(wxBitmap* bitmap, int x, int y, int width, int height, int delay)
{
	 
#ifdef __WXMAC__

    char captureCommand[80] =""; 
    sprintf(captureCommand, "sleep %d;%s", delay, "screencapture -x /tmp/wx_screen_capture.png");
    system(captureCommand);

    if(delay) Delay(delay);

    wxBitmap fullscreen;
    do
    {
        fullscreen = wxBitmap(wxT("/tmp/wx_screen_capture.png"), wxBITMAP_TYPE_PNG);
    }
    while(!fullscreen.IsOk());

    *bitmap = fullscreen.GetSubBitmap(wxRect(x, y, width, height));

    system("rm /tmp/wx_screen_capture.png");

    return true;

#else // Under other paltforms, take a real screenshot

    if(delay) Delay(delay);

    wxScreenDC dcScreen;

    bitmap->Create(width, height);

    wxMemoryDC memDC;
    memDC.SelectObject((*bitmap));
    memDC.Clear();

    memDC.Blit( 0, 
                0, 
                width, 
                height, 
                &dcScreen, 
                x, 
                y  
              );

    memDC.SelectObject(wxNullBitmap);
		 
#endif // #ifdef __WXMAC__

    return true;
}
 
void Image::Delay(int seconds)
{
    clock_t start = clock();
    while ( clock() - start < (clock_t)CLOCKS_PER_SEC * seconds)
        wxYieldIfNeeded();
}
