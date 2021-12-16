module Rwx
	 
	class Frame
		def on_init 

			@treelist = TreeList.new(self)
			 
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
