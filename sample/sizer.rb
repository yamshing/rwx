module Rwx

	 
	class Frame
		def on_init 
		end
	end
	 
	class App
		def on_init
			@frame = Frame.new
			@frame.set_size(1000, 500)
			 
			@sizer = Sizer.new('box', 'vertical')
			row_1_sizer = Sizer.new('box', 'horizontal')
			@text_ctrl = TextCtrl.new(@frame, 'hello',{'style':'multi_line','w':9999, 'h':9999})
			row_1_sizer.add(@text_ctrl)
			 
			@sizer.add(row_1_sizer)
			 
			@frame.set_sizer(@sizer)
			 
		end
	end
end
	 
app = Rwx::App.new
