#include "grid.h"
#include "static_func.h"
#include "string_util.h"
#include <wx/clipbrd.h> 
#include <wx/tokenzr.h>


 
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
	 
	// overlay canvas example
	//wxScrolledWindow* test = new wxScrolledWindow( m_grid, wxID_ANY, wxPoint(0,0), parent_p->FromDIP(wxSize(1500,2500)), wxFRAME_FLOAT_ON_PARENT );

}

void Grid::OnKeyDown(wxKeyEvent& event)
{

	std::cout << "event.GetKeyCode() (in grid.cpp) " << event.GetKeyCode() << std::endl;
	 
	if ((event.GetKeyCode() == 67 && event.ControlDown()) || (event.GetKeyCode() == 88 && event.ControlDown())) {
		 
		//ctrl-C
		 
		std::string selected_content;
		GetSelectedCellInString(selected_content);

		if (wxTheClipboard->Open())
		{
			wxTheClipboard->Clear();
			wxTheClipboard->SetData( new wxTextDataObject(wxString::FromUTF8(selected_content)) );
			wxTheClipboard->Close();
		}
		 
	}else if (event.GetKeyCode() == 86 && event.ControlDown()) {
		 
		//ctrl-V
		 
		wxString copy_data;
		wxString cur_field;
		wxString cur_line;
		 
		if (wxTheClipboard->Open())
		{
			if (wxTheClipboard->IsSupported( wxDF_TEXT ))
			{
				wxGridBlocks range = m_grid->GetSelectedBlocks();
				int start_row = 0;
				int start_col = 0;
				 
				SELECTED_BLOCK_LOOP_START(range)
					start_row = top_row;
					start_col = left_col;
				SELECTED_BLOCK_LOOP_END
	
				 
				wxTextDataObject data;
				wxTheClipboard->GetData( data );
				copy_data = data.GetText();

				std::cout << "copy_data (in grid.cpp) " << copy_data << std::endl;
				wxStringTokenizer line_tokenizer(copy_data, "\n");
				 
				wxString delim = "\t";
				if (copy_data.Find("\t") == -1) {
					delim = ",";
				}
				 
				while ( line_tokenizer.HasMoreTokens() )
				{
					 
					wxString line_token = line_tokenizer.GetNextToken();
					wxStringTokenizer cell_tokenizer(line_token, delim);
					 
					int now_col = start_col;
					 
					while ( cell_tokenizer.HasMoreTokens() )
					{
						wxString cell_token = cell_tokenizer.GetNextToken();
						 
						m_grid->SetCellValue(start_row, now_col, cell_token);
						 
						++ now_col;
						 
					}
					 
					++ start_row;
					 
				}
			}
			 
			wxTheClipboard->Close();
			 
		}
	}
	 
	if (event.GetKeyCode() == 127 || (event.GetKeyCode() == 88 && event.ControlDown())) {
		//delete
		 
		wxGridBlocks range = m_grid->GetSelectedBlocks();
		SELECTED_BLOCK_LOOP_START(range)

			for (int i = top_row; i < bottom_row + 1; ++i) {
				for (int j = left_col; j < right_col + 1; ++j) {
					m_grid->SetCellValue(i, j, wxT(""));
				}
			}
		SELECTED_BLOCK_LOOP_END

		 
	}
}
void Grid::OnCopy(wxEvent& event)
{
	
	 
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
 
void Grid::GetSelectedCellInRubyArr(VALUE rhash)
{
	 
	wxGridBlocks range = m_grid->GetSelectedBlocks();
	VALUE selection_arr = rb_ary_new();
	VALUE selection_index_arr = rb_ary_new();
	 
	SELECTED_BLOCK_LOOP_START(range)
		 
		for (int i = top_row; i < bottom_row + 1; ++i) {
			 
			VALUE row = rb_ary_new();
			 
			VALUE select_index_row = rb_ary_new();
			 
			for (int j = left_col; j < right_col + 1; ++j) {
				 
				wxString wx_cell_val = m_grid->GetCellValue(i, j);
				std::string value_str;
				StringUtil::WxStringToStdString(wx_cell_val, &value_str);
				VALUE res_str =  rb_utf8_str_new(value_str.c_str(),value_str.length());
				 
				rb_ary_push(row, res_str);
				 
				VALUE coord_arr = rb_ary_new();
				rb_ary_push(coord_arr, INT2NUM(i));
				rb_ary_push(coord_arr, INT2NUM(j));
				rb_ary_push(select_index_row, coord_arr);
				
			}
			 
			rb_ary_push(selection_arr, row);
			rb_ary_push(selection_index_arr, select_index_row);
			 
		}
	 
	SELECTED_BLOCK_LOOP_END
		 
	rb_hash_aset(rhash,  ID2SYM(rb_intern("selection_arr")), selection_arr);
	rb_hash_aset(rhash,  ID2SYM(rb_intern("selection_index_arr")), selection_index_arr);
	 
}

void Grid::GetSelectedCellInString(std::string& out_str)
{

	wxString wx_res_str;
	wx_res_str.Clear();
	 
	wxGridBlocks range = m_grid->GetSelectedBlocks();
	 
	SELECTED_BLOCK_LOOP_START(range)
		 
		for (int i = top_row; i < bottom_row + 1; ++i) {
			for (int j = left_col; j < right_col + 1; ++j) {
				wxString wx_cell_val = m_grid->GetCellValue(i, j);
				wx_res_str.Append(wx_cell_val);  
				 
				if (j < right_col) {
					wx_res_str.Append(wxT(","));  
				}
				 
			}
			wx_res_str.Append(wxT("\n"));  
		}
	SELECTED_BLOCK_LOOP_END
		 
	StringUtil::WxStringToStdString(wx_res_str, &out_str);
	 
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
		 
	}else if (func_name_str == "set_cell_value_with_index_arr") {
		 
		std::cout << "set cell value with index arr (in grid.cpp) " << std::endl;
		 
	}else if (func_name_str == "get_selection") {
		 
		res = rb_hash_new();
		 
		GetSelectedCellInRubyArr(res);
		 
	}
	return res;
	 
}
 

/*
 *
VALUE type = rb_hash_aref(hash, ID2SYM(rb_intern("type")));
 ary loop
		int size = static_cast<int>(RARRAY_LEN(content));
			for (int i = 0; i < size; ++i) {
				VALUE menu_content = rb_ary_entry(content,i);
				std::string menu_content_str;
				StaticFunc::ValueToString(menu_content, menu_content_str);
				combo->Append(wxString::FromUTF8(menu_content_str));
			}
		
			*/
