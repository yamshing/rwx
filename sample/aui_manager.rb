module Rwx
	 
	class Frame
		def on_init 
			@auimanager = AuiManager.new(self)
			 
			@toolbar = Toolbar.new(self, {type:'aui'})
			@toolbar.add_tool(type:"button", title:"button1", label:"button1", desc:"This is button 1", cb_inst:self, cb_name:"on_button_1" )
			 
			@auimanager.add_pane(pane:@toolbar)
			 
			@notebook = Notebook.new(self, {type:'aui'})
			 
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
