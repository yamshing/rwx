#include "combo_box.h"
#include "static_func.h"

ComboBox::ComboBox(int nargs, VALUE *args)
{

	std::cout << "combo init (in combo_box.cpp) "  << std::endl;
	VALUE parent = args[0];
	VALUE option = args[1];
	 
	VALUE image = Qnil;
	VALUE hover_image = Qnil;
	VALUE press_image = Qnil;
	wxBitmap img_bitmap;
	wxBitmap hover_img_bitmap;
	wxBitmap press_img_bitmap;

	App* app_p = static_cast<App*>(wxTheApp);
	 
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

	
	 
	wxWindow* parent_p = static_cast<wxWindow*>(app_p->GetObjectFromMap(parent));
	wxArrayString   arrItems;
	arrItems.Add( "Solid" );
	arrItems.Add( "Transparent" );
	arrItems.Add( "Dot" );
	arrItems.Add( "Long Dash" );
	arrItems.Add( "Short Dash" );
	arrItems.Add( "Dot Dash" );
	arrItems.Add( "Backward Diagonal Hatch" );
	arrItems.Add( "Cross-diagonal Hatch" );
	arrItems.Add( "Forward Diagonal Hatch" );
	arrItems.Add( "Cross Hatch" );
	arrItems.Add( "Horizontal Hatch" );
	arrItems.Add( "Vertical Hatch" );
	 
	m_combo = new wxOwnerDrawnComboBox(parent_p,StaticFunc::ALL_EVENT_ID,wxEmptyString,
			wxDefaultPosition, wxDefaultSize,
			arrItems,
			wxCB_SORT // wxNO_BORDER|wxCB_READONLY
			);
	if (image != Qnil && hover_image != Qnil && press_image != Qnil) {
		 
		std::cout << "image found (in combo_box.cpp) "  << std::endl;
		 
		m_combo->SetButtonBitmaps(img_bitmap, true, press_img_bitmap, hover_img_bitmap);
		 
	}
	 
	++StaticFunc::ALL_EVENT_ID;

}
VALUE ComboBox::Call(int nargs, VALUE *args)
{
	VALUE func_name = args[0];
	VALUE result = INT2NUM(-1);
	 
	std::string func_name_str = std::string(StringValuePtr(func_name));
	 
	if (func_name_str == "get_selection") {
		//int combo_selected = m_combo->GetSelection();
		//result = INT2NUM(combo_selected);
	}
	return result;
	 
}


