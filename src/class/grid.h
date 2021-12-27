#ifndef GRID_H
#define GRID_H 
 
#include "wx/wx.h"
#include "wx/grid.h"
#include "ruby.h"
 
class Grid :public wxObject
{
private:
	wxGrid* m_grid;
	 
public:
	Grid(int nargs, VALUE *args);
	virtual ~Grid (){
		delete m_grid;
	};
	wxGrid* GetGrid(){
		return m_grid;
	};
	VALUE Call(int nargs, VALUE *args);
	 
};
#endif
