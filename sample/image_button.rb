module Rwx
	 
	class Panel
		def on_init 
			 
			out_sizer = Sizer.new('box', 'vertical')
			 
			row_2_sizer = Sizer.new('box', 'horizontal')
			button_1 = Button.new(self, label:'Click Here',cb_inst:self, cb_name:'on_button_click' )
			 
			row_2_sizer.add_spacer(20)
			row_2_sizer.add(button_1)
			 
			out_sizer.add_spacer(20)
			out_sizer.add(row_2_sizer)
			 
			add_sizer(out_sizer)
			 
		end
		 
		def on_button_click
			p "click"
		end
		
		 
	end
	class Frame
		def on_init 
			@panel = Panel.new(self)
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



