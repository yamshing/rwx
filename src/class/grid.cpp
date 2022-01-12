#include "grid.h"
#include "static_func.h"
 
Grid::Grid(int nargs, VALUE *args)
{
	VALUE parent = args[0];
	VALUE option = args[1];
	std::cout << "grig ctor (in grid.cpp) " << std::endl;

	App* app_p = static_cast<App*>(wxTheApp);
	wxWindow* parent_p = static_cast<wxWindow*>(app_p->GetObjectFromMap(parent));
	 
	m_grid = new wxGrid(parent_p, wxID_ANY,
			wxPoint(0,0),
			parent_p->FromDIP(wxSize(150,250)),
			wxNO_BORDER | wxWANTS_CHARS);
	m_grid->CreateGrid(50, 20);

	m_grid->Bind(wxEVT_GRID_CELL_LEFT_CLICK, &Grid::OnCellClick, this);
	 
	//m_grid->DisableDragRowSize();
	//m_grid->DisableDragColSize();
	 
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
		m_grid->ClearSelection();
		m_grid->SelectBlock(row,col,row,col);
		m_grid->SetGridCursor(row,col);
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
