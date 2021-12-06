
#include "dc.h"
#include "static_func.h"
 
void DC::GetColorBrush(VALUE color_str_value, wxBrush& brush)
{
	int r,g,b,alpha;
	char* hex_char = StringValuePtr(color_str_value);
	StaticFunc::HexCharToRGB(hex_char, &r, &g, &b, &alpha);
	wxColor color = wxColour(r, g, b, alpha);
	brush = wxBrush(color); 
}
void DC::GetColorPen(VALUE color_str_value, wxPen& pen)
{
	int r,g,b,alpha;
	char* hex_char = StringValuePtr(color_str_value);
	StaticFunc::HexCharToRGB(hex_char, &r, &g, &b, &alpha);
	wxColor color = wxColour(r, g, b, alpha);
	pen = wxPen(color); 
}
 
void DC::Call(int nargs, VALUE *args)
{
	VALUE func_name = args[0];
	std::string func_name_str = std::string(StringValuePtr(func_name));
	 
	if (func_name_str == "draw_circle") {
		int x = NUM2INT(args[1]);
		int y = NUM2INT(args[2]);
		int r = NUM2INT(args[3]);
		 
		m_wx_dc_p->DrawCircle(x, y, r);
		 
	}else if (func_name_str == "set_brush") {
		 
		wxBrush brush;
		GetColorBrush(args[1], brush);
		m_wx_dc_p->SetBrush( brush );
		 
	}else if (func_name_str == "set_pen") {
		 
 
		 
		wxPen pen;
		GetColorPen(args[1], pen);
		 
		if (nargs > 1) {
			int w = NUM2INT(args[2]);
			pen.SetWidth(w);
			 
			if (nargs > 2) {
				 
				std::string style_name_str;
				StaticFunc::ValueToString(args[3], style_name_str);
				 
				if (style_name_str == "dash") {
					VALUE dash_arr = args[4];
					 
					int len = static_cast<int>(RARRAY_LEN(dash_arr));
					 
					wxDash dash[len];
					for (int i = 0; i < len; ++i) {
						VALUE elem = rb_ary_entry(dash_arr,i);
						int elem_i = NUM2INT(elem);
						dash[i] = elem_i;
						std::cout << "elem_i << ',' << i (in dc.cpp) " << elem_i << ',' << i << std::endl;
					} 
					 
					pen.SetStyle(wxPENSTYLE_USER_DASH);
					pen.SetDashes(len, dash);
					 
				}else if(style_name_str == "dot"){
					pen.SetStyle(wxPENSTYLE_DOT);
				}else if(style_name_str == "long_dash"){
					pen.SetStyle(wxPENSTYLE_LONG_DASH);
				}else if(style_name_str == "short_dash"){
					pen.SetStyle(wxPENSTYLE_SHORT_DASH);
				}else if(style_name_str == "hort_dash"){
				}
			}
		}
		 
		m_wx_dc_p->SetPen( pen );
		 
	}
	 
}
