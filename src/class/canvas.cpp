#include "canvas.h"
 
#include <wx/dcbuffer.h>
#include <wx/graphics.h>
 
#include "static_func.h"
 
extern "C" VALUE librwx_Canvas;

wxBEGIN_EVENT_TABLE(Canvas, wxScrolledWindow)
  EVT_MOUSE_EVENTS(Canvas::OnMouseEvent)
  EVT_ERASE_BACKGROUND(Canvas::OnEraseBG)
  //EVT_MOTION(Canvas::OnMouseMove)
  //EVT_MIDDLE_DOWN(Canvas::OnMouseMiddleDown)
  //EVT_MIDDLE_UP(Canvas::OnMouseMiddleUp)
  //EVT_MOUSEWHEEL(Canvas::OnMouseWheel)
wxEND_EVENT_TABLE()

Canvas::Canvas(wxWindow *parent, VALUE rwx_canvas, VALUE rwx_dc)
	: wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,wxHSCROLL | wxVSCROLL)
{
	this->Bind(wxEVT_PAINT, &Canvas::OnPaint, this, wxID_ANY);
	 
	m_rwx_canvas = rwx_canvas;
	m_rwx_dc = rwx_dc;
	 
	 
	m_use_on_mouse_down = CheckMouseEventFlag("on_mouse_down");
	m_use_on_mouse_up = CheckMouseEventFlag("on_mouse_up");
	m_use_on_mouse_dragging = CheckMouseEventFlag("on_mouse_dragging");
	 
	 
	SetVirtualSize(wxSize(1000,1000));
	 
	m_dc = new DC();
	 
	App* app_p = static_cast<App*>(wxTheApp);
	//std::cout << "dc set (in canvas.cpp) " << m_rwx_dc << std::endl;
	app_p -> SetObjectToMap(m_rwx_dc, m_dc);
	 
	 
}
 
bool Canvas::CheckMouseEventFlag(std::string method_name)
{
	bool defined = StaticFunc::CheckFuncExist(librwx_Canvas, method_name);
	return defined;
}
 
 
void Canvas::CallOnInit(VALUE self)
{
	std::string method_name = "on_init";
	bool defined = StaticFunc::CheckFuncExist(librwx_Canvas, method_name);
	 
	if (defined) {
		VALUE args[0];
		StaticFunc::CallRwxFunc(self, method_name, 0, args);
	}
}
 

void Canvas::OnPaint(wxPaintEvent &WXUNUSED(event))
{
	wxBufferedPaintDC dc( this );
	PrepareDC( dc );
	dc.SetBackground(*wxWHITE_BRUSH);
	dc.Clear();
	 
	m_dc->SetWxDcP(&dc);
	 
	std::string method_name = "on_paint";
	bool defined = StaticFunc::CheckFuncExist(librwx_Canvas, method_name);
	 
	//std::cout << "defined (in test_wx.cpp) " << defined << std::endl;
	 
	if (defined) {
		VALUE args[0];
		StaticFunc::CallRwxFunc(m_rwx_canvas, method_name, 0, args);
	}
	 


}
 
void Canvas::OnMouseEvent(wxMouseEvent& event)
{
	const wxPoint& pt = event.GetPosition();
	int scrolled_pos_x;
	int scrolled_pos_y;
	CalcUnscrolledPosition(pt.x, pt.y, &scrolled_pos_x, &scrolled_pos_y);
	 
	if (
			(event.LeftDown() && m_use_on_mouse_down) || 
			(event.LeftUp() && m_use_on_mouse_up) || 
			(event.Dragging() && m_use_on_mouse_dragging) 
		) {
		 
		std::string method_name = "";
		 
		if (event.LeftDown()) {
			method_name = "on_mouse_down";
		}else if(event.LeftUp()){
			method_name = "on_mouse_up";
		}else if(event.Dragging()){
			method_name = "on_mouse_dragging";
		}
		 
		VALUE args[0];
		VALUE hash = rb_hash_new();
		 
		rb_hash_aset(hash, ID2SYM(rb_intern("pos_x")), INT2FIX(pt.x));
		rb_hash_aset(hash, ID2SYM(rb_intern("pos_y")), INT2FIX(pt.y));
		 
		args[0] = hash;
		 
		StaticFunc::CallRwxFunc(m_rwx_canvas, method_name, 1, args);
		 
	}
	 
	 
}
void Canvas::Call(int nargs, VALUE *args)
{
	VALUE func_name = args[0];
	std::string func_name_str = std::string(StringValuePtr(func_name));
	 
	if (func_name_str == "refresh") {
		Refresh(true);
	}
	 
}
 
void Canvas::OnEraseBG(wxEraseEvent& evt)
{
  //do nothing to prevent flicker
}


