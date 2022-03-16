#ifndef SLIDER_H
#define SLIDER_H 

#include "wx/wx.h"
#include "ruby.h"

 
class Slider :public wxObject
{
private:
	wxSlider* m_slider;
	wxFlexGridSizer* m_slider_sizer;
	 
	 
public:
	Slider (int nargs, VALUE *args);
	 
	virtual ~Slider (){
		delete m_slider; 
	};
	 
	wxSlider* GetSlider(){
		return m_slider;
	};
	 
	wxFlexGridSizer* GetSliderSizer(){
		return m_slider_sizer;
	};
	 
	//VALUE Call(int nargs, VALUE *args);
	 
private:
	/* data */
};


#endif
