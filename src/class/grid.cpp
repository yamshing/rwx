#include "grid.h"
#include "static_func.h"
#include "string_util.h"
#include <wx/clipbrd.h> 
 
Grid::Grid(int nargs, VALUE *args)
{
	VALUE parent = args[0];
	VALUE option = args[1];
	m_prev_selected_col = -1;
	m_prev_selected_row = -1;
	 
	std::cout << "grig ctor (in grid.cpp) " << std::endl;

	App* app_p = static_cast<App*>(wxTheApp);
	wxWindow* parent_p = static_cast<wxWindow*>(app_p->GetObjectFromMap(parent));
	 
	m_grid = new wxGrid(parent_p, wxID_ANY,
			wxPoint(0,0),
			parent_p->FromDIP(wxSize(150,250)),
			wxNO_BORDER | wxWANTS_CHARS);
	m_grid->CreateGrid(50, 20);

	m_grid->Bind(wxEVT_GRID_CELL_LEFT_CLICK, &Grid::OnCellClick, this);
	m_grid->Bind(wxEVT_TEXT_COPY, &Grid::OnCopy, this);

	m_grid->Bind(wxEVT_KEY_DOWN, &Grid::OnKeyDown, this);
	 
	//m_grid->DisableDragRowSize();
	//m_grid->DisableDragColSize();
	 
}

void Grid::OnKeyDown(wxKeyEvent& event)
{

	if (event.GetKeyCode() == 67 && event.ControlDown()) {
		 
		//ctrl-C
		std::string selected_cell_str;
		GetSelectedCellInString(selected_cell_str);
		 
		std::cout << "selected_cell_str (in grid.cpp) " << selected_cell_str << std::endl;
		
	}
	 
}
void Grid::OnCopy(wxEvent& event)
{
	std::cout << "copy event in grid (in grid.cpp) "  << std::endl;
	std::string selected_content;
	GetSelectedCellInString(selected_content);
	 
}
 
void Grid::OnCellClick(wxGridEvent& event)
{
	int col = event.GetCol();
	int row = event.GetRow();
	int label_col = m_grid->GetColLabelSize();
	int label_row = m_grid->GetRowLabelSize();
	 
	wxPoint org_pos = event.GetPosition();
	wxPoint pos = m_grid->CalcGridWindowUnscrolledPosition(org_pos, NULL);
	 
	 
	wxRect cell_rect = m_grid->CellToRect(row, col);
	 
	int edge_click_margin = 2;
	 
	int cell_right = cell_rect.x + label_row + cell_rect.width;
	int cell_left = cell_rect.x + label_row;
	 
	int cell_top = cell_rect.y + label_col;
	int cell_bottom = cell_rect.y + label_col +  cell_rect.height;
	
	 
	int left_diff = abs(pos.x - cell_left);
	int right_diff = abs(pos.x - cell_right);

	int top_diff = abs(pos.y - cell_top);
	int bottom_diff = abs(pos.y - cell_bottom);
	 
	std::cout << "pos.x << ',' << pos.y (in grid.cpp) " << pos.x << ',' << pos.y << std::endl;
	std::cout << "cell_top << ',' << cell_bottom (in grid.cpp) " << cell_top << ',' << cell_bottom << std::endl;
	//std::cout << "col << ',' << row (in grid.cpp) " << col << ',' << row << std::endl;
	//std::cout << "label_col << ',' << label_row (in grid.cpp) " << label_col << ',' << label_row << std::endl;
	//std::cout << "cell_rect.x << ',' << cell_rect.y << ',' cell_rect.w << ',' << cell_rect.h (in grid.cpp) " << cell_rect.x << ',' << cell_rect.y << ',' << cell_rect.width << ',' << cell_rect.height << std::endl;
	//std::cout << "cell_left << ',' << cell_right (in grid.cpp) " << cell_left << ',' << cell_right << std::endl;
	//std::cout << "left_diff << ',' << right_diff (in grid.cpp) " << left_diff << ',' << right_diff << std::endl;
	 
	if (left_diff < edge_click_margin || right_diff < edge_click_margin || top_diff < edge_click_margin || bottom_diff < edge_click_margin) {
		event.Skip();
	}else{
		 
		m_grid->SetGridCursor(row,col);
		 
		if (event.ControlDown()) {
			 
			m_grid->SelectBlock(row,col,row,col,true);

			 
		}else if(event.ShiftDown()){
			 
			m_grid->ClearSelection();
			 
			if (m_prev_selected_col != -1 && m_prev_selected_row != -1) {
				m_grid->SelectBlock(m_prev_selected_row,m_prev_selected_col,row,col,false);
				m_prev_selected_col = -1;
				m_prev_selected_row = -1;
				 
				 
				return;
				 
			}else{
				m_grid->SelectBlock(row,col,row,col,false);
			}
			 
		}else{
			 
			m_grid->ClearSelection();
			m_grid->SelectBlock(row,col,row,col,false);
			 
		}
		m_prev_selected_col = col;
		m_prev_selected_row = row;
	}
	 
	 
}
 
void Grid::GetSelectedCellInRubyArr(VALUE rarray)
{
	 
	wxGridBlocks range = m_grid->GetSelectedBlocks();
	 
	for ( const wxGridBlockCoords& block : range ) {
		 
		int top_row = block.GetTopRow();
		int bottom_row = block.GetBottomRow();
		 
		int left_col = block.GetLeftCol();
		int right_col = block.GetRightCol();
		 
		for (int i = top_row; i < bottom_row + 1; ++i) {
			 
			VALUE row = rb_ary_new();
			 
			for (int j = left_col; j < right_col + 1; ++j) {
				 
				wxString wx_cell_val = m_grid->GetCellValue(i, j);
				std::string value_str;
				StringUtil::WxStringToStdString(wx_cell_val, &value_str);
				VALUE res_str =  rb_utf8_str_new(value_str.c_str(),value_str.length());
				rb_ary_push(row, res_str);
				
			}
			rb_ary_push(rarray, row);
		}
		//std::cout << "top_row << ',' << left_col << ',' << bottom_row << ',' << right_col (in grid.cpp) " << top_row << ',' << left_col << ',' << bottom_row << ',' << right_col << std::endl;
	}
}

void Grid::GetSelectedCellInString(std::string& out_str)
{
	std::stringstream ss;
	ss << "hello";

	out_str = ss.str();
	if (wxTheClipboard->Open())
	{
		wxTheClipboard->Clear();
		wxTheClipboard->SetData( new wxTextDataObject(wxString::FromUTF8(out_str)) );
		wxTheClipboard->Close();
	}

}
 
//ref http://marupeke296.com/IKDADV_WX_GridWindow.html
 
VALUE Grid::Call(int nargs, VALUE *args)
{
	VALUE func_name = args[0];
	std::string func_name_str = std::string(StringValuePtr(func_name));
	VALUE res = Qtrue;
	 
	if (func_name_str == "set_cell_value") {
		VALUE row_val = args[1];
		VALUE col_val = args[2];
		VALUE value_val = args[3];
		int row = NUM2INT(row_val);
		int col = NUM2INT(col_val);
		std::string value_str = std::string(StringValuePtr(value_val));
		m_grid->SetCellValue(row, col, wxString::FromUTF8(value_str));
		 
		std::cout << "value_str << ',' << row << ',' << col (in grid.cpp) " << value_str << ',' << row << ',' << col << std::endl;
		 
		//
		// select cell
		//m_grid->SelectBlock(1,1,1,1);
		//std::cout << "this->grid->GetSelectedCells().Count() (in grid.cpp) " << m_grid->GetSelectedCells().Count() << std::endl;
		 
		// scroll to this cell
		//m_grid->MakeCellVisible(2,2);
		 
	}else if (func_name_str == "get_selection") {
		 
		res = rb_ary_new();
		GetSelectedCellInRubyArr(res);
		 
	}
	return res;
	 
}

/* on copy
	 wxString copy_data;
	 bool something_in_this_line;
	 copy_data.Clear();
	 for (int i=0; i<GetNumberRows();i++)
	 {     
	 something_in_this_line = false;    
	 for (int j=0; j<GetNumberCols(); j++)
	 {  
	 if (IsInSelection(i,j))
	 { 
	 if (something_in_this_line == false)
	 {  
	 if (copy_data.IsEmpty() == false) 
	 {   
	 copy_data.Append(wxT("\n"));  
	 }
	 something_in_this_line = true;
	 } 
	 else
	 {                                
	 copy_data.Append(wxT("\t"));  
	 }
	 copy_data = copy_data + GetCellValue(i,j);    
	 }
	 }
	 }
	 if (wxTheClipboard->Open())
	 {
	 wxTheClipboard->Clear();
	 wxTheClipboard->SetData( new wxTextDataObject(copy_data) );
	 wxTheClipboard->Close();
	 }
	 }
 */
