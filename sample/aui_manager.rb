module Rwx
	 
	class Panel
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
			 
			add_sizer(out_sizer)
		end
		 
		def on_button_click
		end
		 
		def on_button_2_click
		end
		 
	end
	class Frame
		def on_init 
			@auimanager = AuiManager.new(self)
			 
			@toolbar = Toolbar.new(self, {type:'aui'})
			@toolbar.add_tool(type:"button", title:"button1", label:"button1", desc:"This is button 1", cb_inst:self, cb_name:"on_button_1" )
			 
			@auimanager.add_pane(pane:@toolbar)
			 
			@notebook = Notebook.new(self, {type:'aui'})
			 
			@panel = Panel.new(self)
			 
			@notebook.add(@panel, "１番")

			@panel2 = Panel.new(self)
			@notebook.add(@panel2, "第２")
			 
			@auimanager.add_pane(pane:@notebook)
			 
			#@treelist = TreeList.new(self)
			#@sizer.add(@treelist)
			#set_sizer(@sizer)
			 
		end
		 
		def on_button_1
			p "button 1"
		end
		 
		def on_button_2
			p "button 2"
		end
		 
	end
	 
	class App
		def on_init
			 
			@frame = Frame.new
			@frame.set_size(1000, 500)
	
			 
			@treectrl = TreeCtrl.new(@frame)
			 
		end
	end
	 

end
	 
app = Rwx::App.new
