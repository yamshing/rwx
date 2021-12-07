module Rwx
	class Frame
		def on_init 
			@toolbar = Toolbar.new(self)
			@toolbar.add_tool(type:"button", title:"ボタン１", label:"button1", desc:"This is button 1", cb_inst:self, cb_name:"on_button_1" )
			@toolbar.add_tool(type:"button", title:"ボタン２", label:"button2", desc:"This is button 2", cb_inst:self, cb_name:"on_button_2" )
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
		end
	end
end
 
app = Rwx::App.new
 
