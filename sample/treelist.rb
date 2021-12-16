module Rwx
	 
	class Frame
		def on_init 
			 
			#@treelist = TreeList.new(self)
			#@sizer.add(@treelist)
			#set_sizer(@sizer)
			 
		end
	end
	 
	class App
		def on_init
			@frame = Frame.new
			@frame.set_size(1000, 500)
			@sizer = Sizer.new('box', 'horizontal')
			@treelist = TreeList.new(@frame)
			@sizer.add(@treelist)

			@text_ctrl = TextCtrl.new(@frame, '123')
			@sizer.add(@text_ctrl)
			 
			@frame.set_sizer(@sizer)
			 
		end
	end
end
	 
app = Rwx::App.new
