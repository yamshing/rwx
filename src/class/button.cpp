#include "button.h"
#include "static_func.h"
#include <wx/platinfo.h>

Button::Button(int nargs, VALUE *args)
{

	VALUE parent = args[0];
	VALUE option = args[1];
	 
	//VALUE parent =  rb_hash_aref(option, ID2SYM(rb_intern("parent")));
	VALUE content = rb_hash_aref(option, ID2SYM(rb_intern("label")));
	VALUE cb_inst = rb_hash_aref(option, ID2SYM(rb_intern("cb_inst")));
	VALUE cb_name = rb_hash_aref(option, ID2SYM(rb_intern("cb_name")));
	 
	VALUE image = Qnil;
	VALUE hover_image = Qnil;
	VALUE press_image = Qnil;
	 
	wxBitmap img_bitmap;
	wxBitmap hover_img_bitmap;
	wxBitmap press_img_bitmap;
	 
	std::string content_str; 
	StaticFunc::ValueToString(content, content_str);
	int width =  -1;
	int height = -1;

	if (rb_funcall(option, rb_intern("has_key?"),1,ID2SYM(rb_intern("width")))) {
		width = NUM2INT(rb_hash_aref(option, ID2SYM(rb_intern("width"))));
	}
	 
	if (rb_funcall(option, rb_intern("has_key?"),1,ID2SYM(rb_intern("height")))) {
		height = NUM2INT(rb_hash_aref(option, ID2SYM(rb_intern("height"))));
	}
	std::cout << "width << ',' height (in button.cpp) " << width << ',' << height << std::endl;
	 
	 
	//rb_p(parent);
	 
	App* app_p = static_cast<App*>(wxTheApp);
	wxWindow* parent_p = static_cast<wxWindow*>(app_p->GetObjectFromMap(parent));
	 
	if (rb_funcall(option, rb_intern("has_key?"),1,ID2SYM(rb_intern("image")))) {
		image = rb_hash_aref(option, ID2SYM(rb_intern("image")));
		Image* image_p = dynamic_cast<Image*>(app_p->GetObjectFromMap(image));

		if (image_p) {
			wxImage* wx_image_p = image_p -> GetWxImage();
			img_bitmap = wxBitmap(*wx_image_p);
		}
	}
	 
	if (rb_funcall(option, rb_intern("has_key?"),1,ID2SYM(rb_intern("hover_image")))) {
		hover_image = rb_hash_aref(option, ID2SYM(rb_intern("hover_image")));
		Image* hover_image_p = dynamic_cast<Image*>(app_p->GetObjectFromMap(hover_image));
		 
		if (hover_image_p) {
			wxImage* wx_hover_image_p = hover_image_p -> GetWxImage();
			hover_img_bitmap = wxBitmap(*wx_hover_image_p);
		}
	}
	 
	if (rb_funcall(option, rb_intern("has_key?"),1,ID2SYM(rb_intern("pressed_image")))) {
		press_image = rb_hash_aref(option, ID2SYM(rb_intern("pressed_image")));
		Image* press_image_p = dynamic_cast<Image*>(app_p->GetObjectFromMap(press_image));
		 
		if (press_image_p) {
			wxImage* wx_press_image_p = press_image_p -> GetWxImage();
			press_img_bitmap = wxBitmap(*wx_press_image_p);
		}
	}
	
	 
	wxString os_name =  wxPlatformInfo::Get().GetOperatingSystemFamilyName(); 
	std::cout << "os_name (in button.cpp) " << os_name << std::endl;

	if (image != Qnil) {
		 
		if (os_name == _T("Windows")) {
			m_button = new wxButton(parent_p, StaticFunc::ALL_EVENT_ID);
			m_button -> SetBitmap(img_bitmap);
			 
			if (hover_image != Qnil) {
				m_button -> SetBitmapCurrent(hover_img_bitmap);
			}
			if (press_image != Qnil) {
				m_button -> SetBitmapPressed(press_img_bitmap);
			}
			 
			m_button -> SetLabel(wxString::FromUTF8(content_str));
		}else{
			m_button = new wxButton(parent_p, StaticFunc::ALL_EVENT_ID, wxString::FromUTF8(content_str));
			m_button -> SetBitmap(img_bitmap);

			if (hover_image != Qnil) {
				m_button -> SetBitmapCurrent(hover_img_bitmap);
			}
			if (press_image != Qnil) {
				m_button -> SetBitmapPressed(press_img_bitmap);
			}
			 
			std::cout << "set size (in button.cpp) "  << std::endl;
			 
			 
			//m_button -> SetBitmapPressed(bitmap);
		}
		 
	}else{
		m_button = new wxButton(parent_p, StaticFunc::ALL_EVENT_ID,  wxString::FromUTF8(content_str));
	}
	 
	if (width > 0 && height > 0) {
		m_button -> SetMinSize(wxSize(width,height));
	}
	 
	//m_button = new wxButton(parent_p, StaticFunc::ALL_EVENT_ID,  wxString::FromUTF8(content_str));
	 
	m_menu_callback_inst_map[StaticFunc::ALL_EVENT_ID] = cb_inst;
	m_menu_callback_name_map[StaticFunc::ALL_EVENT_ID] = cb_name;
	 
	std::cout << "bind button (in button.cpp) " << std::endl;
	m_button -> Bind(wxEVT_BUTTON, &Button::OnClick, this, StaticFunc::ALL_EVENT_ID);
	 
	++ StaticFunc::ALL_EVENT_ID;
}


void Button::OnClick(wxCommandEvent& event)
{
	 
	int id = event.GetId();
	std::cout << "button click (in button.cpp) " << id << std::endl;
	 
	VALUE callback_inst = m_menu_callback_inst_map[id];
	VALUE callback_name = m_menu_callback_name_map[id];
	 
	std::string callback_name_str;
	StaticFunc::ValueToString(callback_name, callback_name_str);
	ID callback_def_id = rb_intern(callback_name_str.c_str());
	rb_funcall(callback_inst, callback_def_id,0);

	 
}

