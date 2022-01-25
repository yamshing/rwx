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

	if (rb_funcall(option, rb_intern("has_key?"),1,ID2SYM(rb_intern("image")))) {
		image = rb_hash_aref(option, ID2SYM(rb_intern("image")));
	}
	 
	 
	std::string content_str; 
	StaticFunc::ValueToString(content, content_str);
	 
	std::cout << "button init (in button.cpp) "  << std::endl;
	rb_p(parent);
	 
	App* app_p = static_cast<App*>(wxTheApp);

	wxWindow* parent_p = static_cast<wxWindow*>(app_p->GetObjectFromMap(parent));

	if (image != Qnil) {
		 
		Image* image_p = dynamic_cast<Image*>(app_p->GetObjectFromMap(image));
		 
		if (image_p) {
			 
			wxImage* wx_image_p = image_p -> GetWxImage();
			wxBitmap img_bitmap = wxBitmap(*wx_image_p);
			 
			wxBitmap bitmap( 20, 20 );
			wxMemoryDC dc;
			dc.SelectObject( bitmap );
			wxSystemSettings sys;

			//dc.SetBackground(wxBrush(wxTransparentColour));
			//dc.SetBackground(*wxGREEN);
			//dc.SetBackground(wxBrush(sys.GetColour(wxSYS_COLOUR_BTNFACE)));
			//dc.SetPen(*wxRED_PEN);
			//dc.Clear();

			//dc.SetBrush( *wxTRANSPARENT_BRUSH );
			//dc.DrawRectangle( 0, 0, 100, 30 );

			dc.DrawBitmap(img_bitmap, 0, 0);
			//dc.DrawText(_T("button"), 25, 5);

			dc.SelectObject( wxNullBitmap );
			 
			//m_button = new wxBitmapButton(parent_p, StaticFunc::ALL_EVENT_ID,  bitmap, wxPoint(0,0), wxSize(100,50));
			 
			wxString os_name =  wxPlatformInfo::Get().GetOperatingSystemFamilyName(); 
			std::cout << "os_name (in button.cpp) " << os_name << std::endl;
			 
			if (os_name == _T("Windows")) {
				 
				m_button = new wxButton(parent_p, StaticFunc::ALL_EVENT_ID);
				m_button -> SetBitmap(bitmap);
				m_button -> SetLabel(wxString::FromUTF8(content_str));
				 
			}else{
				m_button = new wxButton(parent_p, StaticFunc::ALL_EVENT_ID, wxString::FromUTF8(content_str));
				m_button -> SetBitmap(bitmap);
			}
			 

		}
		 
	}else{
		m_button = new wxButton(parent_p, StaticFunc::ALL_EVENT_ID,  wxString::FromUTF8(content_str));
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

