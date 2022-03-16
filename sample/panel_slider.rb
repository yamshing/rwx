module Rwx
	class Panel
		def on_init 
			out_sizer = Sizer.new('box', 'vertical')
			row_1_sizer = Sizer.new('box', 'horizontal')
			 
			slider = Slider.new(self)
			 
			row_1_sizer.add(slider)
			 
			out_sizer.add(row_1_sizer)
			 
			add_sizer(out_sizer)
			 
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
