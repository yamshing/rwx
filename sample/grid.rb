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

			@grid.set_cell_value_with_index_arr(content_arr:[["abc","def"],["ghi","jkl"],["mno","pqr"]],index_arr:[[[0,0],[0,1]],[[1,0],[1,1]],[[2,0],[2,1]]])
			 
		end
		 
		def on_button_1
			 
			 
		end
		 
		def on_button_2
			 
			cell_val = @grid.get_cell_value_with_index_arr(index_arr:[[[0,0],[0,1]],[[1,0],[1,1]],[[2,0],[2,1]]])
			p cell_val
			 
			#@grid.delete_cell_value_with_index_arr(content_arr:[["hello","world"],["hello","world"],["hello","world"]],index_arr:[[[0,0],[0,1]],[[1,0],[1,1]],[[2,0],[2,1]]])
			 
			selected = @grid.get_selection
			selection_index_arr = selected[:selection_index_arr]
			selection_content_arr = selected[:selection_content_arr]
			 
			move_col_num = 10
			 
			for selected_row in selection_index_arr do
				row = selected_row[0][0]
				col = selected_row[0][1]
				 
				row_content_arr = []
				 
				#for i in col...col + 10 do
				#end
				 
			end
			 
			#row = selection_index_arr[0][0][0]
			#col = selection_index_arr[0][0][1]
			 
			 
			 
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
