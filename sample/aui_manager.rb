module Rwx
	 
	class Panel
		attr_accessor:list_ctrl
		 
		def on_init 
			out_sizer = Sizer.new('box', 'vertical')
			row_1_sizer = Sizer.new('box', 'horizontal')
			label_1 = StaticText.new(self, 'あいうえお')
			row_1_sizer.add(label_1)
			out_sizer.add(row_1_sizer)
			 
			row_8_sizer = Sizer.new('box', 'horizontal')
			row_8_sizer.add_spacer(10)
			label = StaticText.new(self, 'リストコントロール')
			row_8_sizer.add(label)
			list_content = [
				['山田太郎','abc-ABC-あいうえお'],
				['木村次郎','abc-ABC-カキクケコ'],
				['木村一郎','abc-ABC-カキクケコ'],
				['山田太郎','abc-ABC-あいうえお'],
				['木村次郎','abc-ABC-カキクケコ'],
				['木村一郎','abc-ABC-カキクケコ'],
				['山田太郎','abc-ABC-あいうえお'],
				['木村次郎','abc-ABC-カキクケコ'],
				['木村一郎','abc-ABC-カキクケコ'],
			]
			 
			@list_ctrl = ListCtrl.new(self, 'header':['氏名','キー'], 'content':list_content);
			row_8_sizer.add(@list_ctrl)
			out_sizer.add(row_8_sizer)
			 
			row_5_sizer = Sizer.new('box', 'horizontal')
				row_5_sizer.add_spacer(10)
				label = StaticText.new(self, 'インプット')
				row_5_sizer.add(label)
				 
				@text_ctrl_1 = TextCtrl.new(self, '123')
				row_5_sizer.add(@text_ctrl_1)
				 
			out_sizer.add(row_5_sizer)
			 
			add_sizer(out_sizer)
		end
		 
	end
	class Frame
		def on_init 
			@auimanager = AuiManager.new(self)
			 
			@toolbar = Toolbar.new(self, {type:'aui'})
			@toolbar.add_tool(type:"button", title:"show", label:"button1", desc:"This is button 1", cb_inst:self, cb_name:"on_button_1" )
			@toolbar.add_tool(type:"button", title:"hide", label:"button2", desc:"This is button 2", cb_inst:self, cb_name:"on_button_2" )
			 
			@auimanager.add_pane(pane:@toolbar)
			 
			@notebook = Notebook.new(self, {type:'aui'})
			 
			@panel = Panel.new(self)
			 
			@notebook.add(@panel, "１番")

			@panel2 = Panel.new(self)
			@notebook.add(@panel2, "第２")
			 
			@auimanager.add_pane(pane:@notebook, name:"notebook_pane", direction:"left", dockable:true, resizable:false)
			 
			tree_content = [
				['ABC',
					[
						['HHH',
							[
								['AAA',[]],
								['BBB',[]],
								['CCC',[]] 
							]
						]
					]
				]
			]
			 
			 
			@treectrl = TreeCtrl.new(self, 'content':tree_content)
			 
			@auimanager.add_pane(pane:@treectrl, name:"tree_pane", direction:"right", dockable:true)
			 
			@grid = Grid.new(self)
			 
			@grid.set_cell_value(2,2,"へろー")
			@grid.set_cell_value(3,2,"abc")
			@grid.set_cell_value(4,2,"abcd")
			 
			@grid.set_cell_value(2,3,"へろー")
			@grid.set_cell_value(3,3,"abc")
			@grid.set_cell_value(4,3,"abcd")
			 
			 
			@auimanager.add_pane(pane:@grid, name:"grid pane",dockable:false)
			 
			#@treelist = TreeList.new(self)
			#@sizer.add(@treelist)
			#set_sizer(@sizer)
			 
		end
		 
		def on_paste(content)
			 
			@grid.set_cell_value(2,3,content)
			 
		end
		 
		def on_button_1
			@auimanager.show_pane()
			#selected = @treectrl.get_selection
			#list_selected = @panel.list_ctrl.get_selection
			#p list_selected
			
			#grid_value = @grid.get_selection
			#p grid_value

			#@grid.set_cell_value_with_index_arr(content_arr:[["hello","world"],["hello","world"],["hello","world"]],index_arr:[[[0,0],[0,1]],[[1,0],[1,1]],[[2,0],[2,1]]])
			#@grid.delete_cell_value_with_index_arr(content_arr:[["hello","world"],["hello","world"],["hello","world"]],index_arr:[[[0,0],[0,1]],[[1,0],[1,1]],[[2,0],[2,1]]])
			 
			 
		end
		 
		def on_button_2
			p "hide"
			@auimanager.hide_pane()
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
