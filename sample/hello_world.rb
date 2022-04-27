module Rwx
	class Frame
		def on_init 
		end
	end
	 
	class App
		def on_init
			@multi = MultipleScript.new
			p "multi ok"
			@frame = Frame.new
			@frame.set_size(1000, 500)
		end
	end
end
 
app = Rwx::App.new
 
