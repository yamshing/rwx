#ifndef GRID_H
#define GRID_H 
 
#include "wx/wx.h"
#include "wx/grid.h"
#include "ruby.h"
 
class Grid :public wxObject
{
private:
	wxGrid* m_grid;
	int m_prev_selected_col;
	int m_prev_selected_row;
	 
	void GetSelectedCellInRubyArr(VALUE rarray);
	 
public:
	Grid(int nargs, VALUE *args);
	virtual ~Grid (){
		delete m_grid;
	};
	wxGrid* GetGrid(){
		return m_grid;
	};
	VALUE Call(int nargs, VALUE *args);
	void OnCellClick(wxGridEvent& event);
	void OnCopy(wxEvent& event);
	 
};
#endif
