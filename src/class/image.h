#ifndef IMAGE_H
#define IMAGE_H 
 
#include "wx/wx.h"
#include "ruby.h"

class Image: public wxObject
{

	public:
		 
		Image(int nargs, VALUE *args);
		 
		virtual ~Image (){};
		 
		//void Call(int nargs, VALUE *args);
		 
		wxImage* GetWxImage(){
			return m_wx_image;
		};
		VALUE Call(int nargs, VALUE *args);
		 
	private:
		 
		bool Capture(wxBitmap* bitmap, int x, int y, int width, int height, int delay);
		void Delay(int seconds);
		wxImage* m_wx_image;
		 
};
#endif
