
module Rwx
	 
	class Frame
		def on_init 
			@panel = Panel.new(self)
		end
	end
	 
	class App
		def on_init
			 
			@simple = Simple.new
			res = @simple.hello()
			p @simple
			p res
			 
			@frame = Frame.new
			@frame.set_size(1000, 500)
			 
		end
	end
end
	 
app = Rwx::App.new


