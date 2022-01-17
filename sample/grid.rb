module Rwx
	 
	class Frame
		def on_init 
			@auimanager = AuiManager.new(self)
			 
			@toolbar = Toolbar.new(self, {type:'aui'})
			@toolbar.add_tool(type:"button", title:"<", label:"<", desc:"This is button 1", cb_inst:self, cb_name:"on_button_1" )
			@toolbar.add_tool(type:"button", title:">", label:">", desc:"This is button 2", cb_inst:self, cb_name:"on_button_2" )
			@auimanager.add_pane(pane:@toolbar)
			 
			@grid = Grid.new(self)
			 
			@auimanager.add_pane(pane:@grid, name:"grid pane")

			@grid.set_cell_value_with_index_arr(content_arr:[["abc","def"],["ghi","jkl"],["mno","pqr"]],index_arr:[[[0,5],[0,6]],[[1,5],[1,6]],[[2,5],[2,6]]])
			 
		end
		 
		def move_row(direction)
			selected = @grid.get_selection
			selection_index_arr = selected[:selection_index_arr]
			selection_content_arr = selected[:selection_content_arr]
			move_col_num = 10
			get_cell_index_arr = []
			 
			 
			for selected_row in selection_index_arr do
				row = selected_row[0][0]
				col = selected_row[0][1]
				 
				get_row_index_arr = []
				set_row_index_arr = []
				if direction > 0
					for get_col in col...col + move_col_num do
						get_row_index_arr.push [row, get_col]
						set_row_index_arr.push [row, get_col + direction]
					end
				else
					for get_col in col.downto(0) do
						get_row_index_arr.push [row, get_col]
						if get_col > 0
							set_row_index_arr.push [row, get_col + direction]
						end
					end
				end
				 
				get_cell_index_arr = [get_row_index_arr]
				set_cell_index_arr = [set_row_index_arr]
				 
				cell_val = @grid.get_cell_value_with_index_arr(index_arr:get_cell_index_arr)
				 
				@grid.set_cell_value_with_index_arr(content_arr:cell_val,index_arr:set_cell_index_arr)
				 
			end
			 
			@grid.delete_cell_value_with_index_arr(index_arr:selection_index_arr)
			 
		end
		 
		def on_button_1
			 
			move_row(- 1)
			 
		end
		 
		def on_button_2
			 
			move_row(1)
			 
		end
		 
	end
	 
	class App
		def on_init
			@frame = Frame.new
			@frame.set_size(1000, 500)
		end
		 
	end
	 

end
	 
app = Rwx::App.new
