#ifndef DC_H
#define DC_H 
 
#include "wx/wx.h"
#include "ruby.h"

class DC: public wxObject
{

	public:
		DC (){
		};
		virtual ~DC (){};
		wxDC* GetWxDcP(){
			return m_wx_dc_p;
		};
		 
		void SetWxDcP(wxDC* wx_dc_p){
			m_wx_dc_p = wx_dc_p;
		};
		 
		void Call(int nargs, VALUE *args);
		 
	private:
		wxDC* m_wx_dc_p;
		void GetColorBrush(VALUE color_str_value, wxBrush& brush);
		void GetColorPen(VALUE color_str_value, wxPen& pen);
		 
};
#endif
