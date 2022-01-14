module Rwx
	 
	class Frame
		def on_init 
			@auimanager = AuiManager.new(self)
			 
			@toolbar = Toolbar.new(self, {type:'aui'})
			@toolbar.add_tool(type:"button", title:"B1", label:"B1", desc:"This is button 1", cb_inst:self, cb_name:"on_button_1" )
			@toolbar.add_tool(type:"button", title:"B2", label:"B2", desc:"This is button 2", cb_inst:self, cb_name:"on_button_2" )
			@auimanager.add_pane(pane:@toolbar)
			 
			@grid = Grid.new(self)
			 
			@auimanager.add_pane(pane:@grid, name:"grid pane")
			 
		end
		 
		def on_button_1
			#selected = @treectrl.get_selection
			#list_selected = @panel.list_ctrl.get_selection
			#p list_selected
			
			#grid_value = @grid.get_selection
			#p grid_value

			#@grid.set_cell_value_with_index_arr(content_arr:[["hello","world"],["hello","world"],["hello","world"]],index_arr:[[[0,0],[0,1]],[[1,0],[1,1]],[[2,0],[2,1]]])
			@grid.delete_cell_value_with_index_arr(content_arr:[["hello","world"],["hello","world"],["hello","world"]],index_arr:[[[0,0],[0,1]],[[1,0],[1,1]],[[2,0],[2,1]]])
			 
			 
		end
		 
		def on_button_2
			p "button 2"
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
