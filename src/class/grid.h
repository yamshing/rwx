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
	void GetSelectedCellInString(std::string& out_str);
	void OnKeyDown(wxKeyEvent& event);
	 
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

#define  SELECTED_BLOCK_LOOP_START(blocks)\
	for ( const wxGridBlockCoords& block : blocks ) {\
		int top_row = block.GetTopRow();\
		int bottom_row = block.GetBottomRow();\
		int left_col = block.GetLeftCol();\
		int right_col = block.GetRightCol();\
	

#define  SELECTED_BLOCK_LOOP_END\
	}\
	 

#endif
