#ifndef CANVAS_H
#define CANVAS_H 

#include "wx/wx.h"
#include "ruby.h"
#include "frame.h"
 
#include "dc.h"

class Canvas: public wxScrolledWindow
{

	public:
		Canvas(wxWindow* parent, VALUE rwx_canvas , VALUE rwx_dc );
		virtual ~Canvas (){
			delete m_dc;
		};
		void CallOnInit(VALUE self);
		void Call(int nargs, VALUE *args);
		 
	private:
		wxDECLARE_EVENT_TABLE();
		VALUE m_rwx_canvas;
		VALUE m_rwx_dc;
		void OnPaint(wxPaintEvent &WXUNUSED(event));
		void OnMouseEvent(wxMouseEvent& event);
		void OnEraseBG(wxEraseEvent& evt);
		bool CheckMouseEventFlag(std::string method_name);
		void OnDropFiles(wxDropFilesEvent& event);
		 
		DC* m_dc;
		bool m_use_on_mouse_down;
		bool m_use_on_mouse_up;
		bool m_use_on_mouse_dragging;
		 
};

#endif
