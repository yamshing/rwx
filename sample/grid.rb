module Rwx
	 
	class Frame
		def on_init 
			@auimanager = AuiManager.new(self)
			 
			@toolbar = Toolbar.new(self, {type:'aui'})
			@toolbar.add_tool(type:"button", title:"<", label:"<", desc:"", cb_inst:self, cb_name:"on_button_1" )
			@toolbar.add_tool(type:"button", title:">", label:">", desc:"", cb_inst:self, cb_name:"on_button_2" )
			@toolbar.add_tool(type:"button", title:"ソート", label:"ソート", desc:"", cb_inst:self, cb_name:"on_sort" )
       
			@auimanager.add_pane(pane:@toolbar)
			 
			@grid = Grid.new(self)
			 
			@auimanager.add_pane(pane:@grid, name:"grid pane")

			@grid.set_cell_value_with_index_arr(content_arr:[
        ["abc","def", "30"],
        ["ghi","jkl", "10"],
        ["mno","pqr", "10"]
      ],index_arr:[
        [[0,5],[0,6],[0,7]],
        [[1,5],[1,6],[1,7]],
        [[2,5],[2,6],[2,7]]
      ])
			 
		end
		 
		def move_row(direction)
			 
			grid_size = @grid.get_grid_size()
			grid_col_num = grid_size[:col]
			grid_row_num = grid_size[:row]
			 
			selected = @grid.get_selection
			selection_index_arr = selected[:selection_index_arr]
			move_col_num = 10
			get_cell_index_arr = []
			 
			for selected_row in selection_index_arr do
				row = selected_row[0][0]
				col = selected_row[0][1]
				 
				get_row_index_arr = []
				set_row_index_arr = []
				 
				if direction > 0
					for get_col in col...grid_col_num do
						if get_col < (grid_col_num - 1)
							p get_col
							get_row_index_arr.push [row, get_col]
							set_row_index_arr.push [row, get_col + direction]
						end
					end
				else
					for get_col in col...(grid_col_num) do
						if get_col > 0
							get_row_index_arr.push [row, get_col]
							set_row_index_arr.push [row, get_col + direction]
						end
					end
				end
				 
				get_cell_index_arr = [get_row_index_arr]
				set_cell_index_arr = [set_row_index_arr]
				 
				cell_val = @grid.get_cell_value_with_index_arr(index_arr:get_cell_index_arr)
				 
				@grid.set_cell_value_with_index_arr(content_arr:cell_val,index_arr:set_cell_index_arr)
				 
			end
			 
			if direction > 0
				@grid.delete_cell_value_with_index_arr(index_arr:selection_index_arr)
			end
			 
		end
		 
    def on_sort
      selected = @grid.get_selection
      selection_index_arr = selected[:selection_index_arr]
      selection_arr = selected[:selection_arr]
      get_col_num = 20
      row_i = 0
       
      index_num_hash = {}
      for sel_row in selection_arr do
        order = sel_row[0].to_f
				index_num_hash[order] ||= []
				index_num_hash[order].push selection_index_arr[row_i]
        row_i += 1
      end
			 
      sorted_index_arr = index_num_hash.sort
       
      set_cell_val_arr = []
      set_cell_index_arr = []
       
      set_row_i = 0
			 
      for index_row in sorted_index_arr do
				 
				row_arr = index_row[1]
				 
				for row_col in row_arr do
					row = row_col[0][0]
					 
					cell_index_arr = []
					set_row_index_arr = []
						 
					for col_i in 0...get_col_num do
						cell_index_arr.push [row, col_i]
						set_row_index_arr.push [set_row_i, col_i]
					end
					 
					cell_val = @grid.get_cell_value_with_index_arr(index_arr:[cell_index_arr])
					set_cell_val_arr.push cell_val[0]
					set_cell_index_arr.push set_row_index_arr
					set_row_i += 1
				end
				 

      end
       
      #p set_cell_val_arr
      #p set_cell_index_arr
       
			@grid.set_cell_value_with_index_arr(content_arr:set_cell_val_arr,index_arr:set_cell_index_arr)
       
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
