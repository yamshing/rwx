module Rwx
	class Frame
		def on_init 
			 
			@image = Image.new(embed_name:"test.png")
			 
			@menubar = MenuBar.new(self)
			save_menu_content ={title:"Save", image:@image, label:"Save", cb_inst:self, cb_name:"save"}
			open_menu_content ={title:"Open", label:"Open", cb_inst:self, cb_name:"open"}
			@file_menu = Menu.new(@menubar,"File",[save_menu_content, open_menu_content])
		end
		def save
			p 'save'
		end
		def open
			p 'open'
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
 
