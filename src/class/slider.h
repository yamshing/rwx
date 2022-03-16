#ifndef SLIDER_H
#define SLIDER_H 

#include "wx/wx.h"
#include "ruby.h"

 
class Slider :public wxObject
{
private:
	wxSlider* m_slider;
	 
public:
	Slider (int nargs, VALUE *args);
	 
	virtual ~Slider (){
		delete m_slider; 
	};
	 
	wxSlider* GetSlider(){
		return m_slider;
	};
	 
	//VALUE Call(int nargs, VALUE *args);


private:
	/* data */
};


#endif
