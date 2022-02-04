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
	m_grid->Bind(wxEVT_TEXT_PASTE, &Grid::OnPaste, this);
	m_grid->Bind(wxEVT_TEXT_CUT, &Grid::OnCut, this);
	m_grid->Bind(wxEVT_KEY_DOWN, &Grid::OnKeyDown, this);
	 
	 
	//m_grid->DisableDragRowSize();
	//m_grid->DisableDragColSize();
	 
	// overlay canvas example
	//wxScrolledWindow* test = new wxScrolledWindow( m_grid, wxID_ANY, wxPoint(0,0), parent_p->FromDIP(wxSize(1500,2500)), wxFRAME_FLOAT_ON_PARENT );

}

void Grid::OnKeyDown(wxKeyEvent& event)
{

	std::cout << "event.GetKeyCode() (in grid.cpp) " << event.GetKeyCode() << std::endl;
	 
	bool key_hit = false;
	 
	if ((event.GetKeyCode() == 67 && event.ControlDown()) || (event.GetKeyCode() == 88 && event.ControlDown())) {
		 
		//ctrl-C
		 
		key_hit = true;
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
		 
		key_hit = true;
		 
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
					wxStringTokenizer cell_tokenizer(line_token, delim, wxTOKEN_RET_EMPTY_ALL);
					 
					int now_col = start_col;
					 
					while ( cell_tokenizer.HasMoreTokens() )
					{
						wxString cell_token = cell_tokenizer.GetNextToken();
						if (cell_token == " ") {
							cell_token = wxT("");
						}
						 
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
		 
		key_hit = true;
		 
		wxGridBlocks range = m_grid->GetSelectedBlocks();
		SELECTED_BLOCK_LOOP_START(range)

			for (int i = top_row; i < bottom_row + 1; ++i) {
				for (int j = left_col; j < right_col + 1; ++j) {
					m_grid->SetCellValue(i, j, wxT(""));
				}
			}
		SELECTED_BLOCK_LOOP_END

		 
	}
	if (!key_hit) {
		std::cout << "skip (in grid.cpp) "  << std::endl;
		event.Skip();
	}
	 
}
void Grid::OnCopy(wxEvent& event)
{
	
	wxTextCtrl *win = (wxTextCtrl *)event.GetEventObject();
	wxString val = win->GetValue();
	if (wxTheClipboard->Open())
	{
		wxTheClipboard->Clear();
		wxTheClipboard->SetData( new wxTextDataObject(wxString::FromUTF8(val)) );
		wxTheClipboard->Close();
	}
	 
}
 
void Grid::OnCut(wxEvent& event)
{
	
	OnCopy(event);
	wxTextCtrl *win = (wxTextCtrl *)event.GetEventObject();
	win->SetValue(wxT(""));
	 
}
void Grid::OnPaste(wxEvent& event)
{

	if (wxTheClipboard->Open())
	{
		if (wxTheClipboard->IsSupported( wxDF_TEXT ))
		{
			wxTextDataObject data;
			wxTheClipboard->GetData( data );
			wxString copy_data = data.GetText();
			wxTextCtrl *win = (wxTextCtrl *)event.GetEventObject();
			win->SetValue(copy_data);
			 
		}
		 
		wxTheClipboard->Close();
		 
	}
	 
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
		 
		std::cout << "top_row << ',' << bottom_row (in grid.cpp) " << top_row << ',' << bottom_row << std::endl;
	 
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
				if (wx_cell_val == "") {
					wx_cell_val = wxT(" ");
				}
				 
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
		 

		 
	}else if ((func_name_str == "get_cell_value_with_index_arr")) {
		 
		VALUE hash = args[1];
		VALUE index_arr = rb_hash_aref(hash, ID2SYM(rb_intern("index_arr")));
		int size = static_cast<int>(RARRAY_LEN(index_arr));
		 
		res = rb_ary_new();
		 
		for (int i = 0; i < size; ++i) {
			VALUE index_row = rb_ary_entry(index_arr,i);
			int index_row_size = static_cast<int>(RARRAY_LEN(index_row));
			VALUE res_row = rb_ary_new();
			 
			for (int j = 0; j < index_row_size; ++j) {
				VALUE index = rb_ary_entry(index_row,j);
				VALUE row = rb_ary_entry(index,0);
				VALUE col = rb_ary_entry(index,1);
				int row_i = NUM2INT(row);
				int col_i = NUM2INT(col);
				wxString cell_val_wxstr = m_grid->GetCellValue(row_i, col_i);
				 
				std::string cell_val_str;
				StringUtil::WxStringToStdString(cell_val_wxstr, &cell_val_str);
				VALUE cell_val =  rb_utf8_str_new(cell_val_str.c_str(),cell_val_str.length());
				rb_ary_push(res_row, cell_val);
				 
			}
			 
			rb_ary_push(res, res_row);
			 
		}
		 
		 
	}else if ((func_name_str == "set_cell_value_with_index_arr") || (func_name_str == "delete_cell_value_with_index_arr")) {
		 
		bool is_deleting = false;
		if (func_name_str == "delete_cell_value_with_index_arr") {
			is_deleting = true;
		}
		 
		 
		VALUE hash = args[1];
		VALUE content_arr;
		if (!is_deleting) {
			content_arr = rb_hash_aref(hash, ID2SYM(rb_intern("content_arr")));
		}
		 
		VALUE index_arr = rb_hash_aref(hash, ID2SYM(rb_intern("index_arr")));
		 
		int size = static_cast<int>(RARRAY_LEN(index_arr));

		for (int i = 0; i < size; ++i) {
			 
			VALUE content_row;
			if (!is_deleting) {
				content_row = rb_ary_entry(content_arr,i);
			}
			 
			VALUE index_row = rb_ary_entry(index_arr,i);

			int content_row_size = static_cast<int>(RARRAY_LEN(content_row));
			int index_row_size = static_cast<int>(RARRAY_LEN(index_row));
			 
			for (int j = 0; j < index_row_size; ++j) {
				 
				std::string content_str;
				 
				if (!is_deleting) {
					VALUE content = rb_ary_entry(content_row,j);
					StaticFunc::ValueToString(content, content_str);
				}else{
					content_str = "";
				}

				VALUE index = rb_ary_entry(index_row,j);
				VALUE row = rb_ary_entry(index,0);
				VALUE col = rb_ary_entry(index,1);
				int row_i = NUM2INT(row);
				int col_i = NUM2INT(col);
				
				m_grid->SetCellValue(row_i, col_i, wxString::FromUTF8(content_str));
				 
			}
		}
		 
	}else if (func_name_str == "get_selection") {
		 
		res = rb_hash_new();
		 
		GetSelectedCellInRubyArr(res);
		 
	}else if (func_name_str == "get_grid_size") {
		std::cout << "get grid size call (in grid.cpp) " << std::endl;
		 
		int row_num = m_grid->GetNumberRows();
		int col_num = m_grid->GetNumberCols();
		 
		res = rb_hash_new();

		rb_hash_aset(res,  ID2SYM(rb_intern("row")), INT2NUM(row_num));
		rb_hash_aset(res,  ID2SYM(rb_intern("col")), INT2NUM(col_num));
		 
		 
	}
	return res;
	 
}
 

