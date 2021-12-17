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
			@auimanager = AuiManager.new(@frame)
			 
		end
	end
end
	 
app = Rwx::App.new
