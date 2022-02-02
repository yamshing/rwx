module Rwx
	class Canvas
		def on_init()
		 
			#@image = Image.new(embed_name:"test_jpg")
			#@image = Image.new(file_name:"./asset/test.png")
			 
		end
		def on_paint()
			#@dc.draw_image(@image, @mouse_x, @mouse_y)
		end

	end
	 
	class App
		def on_init
			 
			@frame = Frame.new
			@frame.set_size(1000, 500)
			 
			@canvas = Canvas.new(@frame)
			@canvas.set_size(1000,1000)
			 
			@sizer = Sizer.new('box', 'horizontal')
			@sizer.add(@canvas)
			@frame.set_sizer(@sizer)
			 
		end
	end
end
	 
app = Rwx::App.new
