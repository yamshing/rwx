module Rwx
	class Canvas
		def on_init()
			@mouse_x = 0
			@mouse_y = 0
			@mouse_clicked = false
			 
		end
		def on_paint()
			if @mouse_clicked
				@dc.set_brush('#aaaaaaff')
				@dc.set_pen('#ff0000',2,'dot_dash')  #dot, long_dash, short_dash, dot_dash
				@dc.draw_circle(@mouse_x, @mouse_y, 10)
			end
		end
		 
		def on_mouse_down(event)
			@mouse_x = event[:pos_x]
			@mouse_y = event[:pos_y]
			@mouse_clicked = true
			refresh
		end
		 
		def on_mouse_up(event)
			@mouse_x = event[:pos_x]
			@mouse_y = event[:pos_y]
			refresh
		end
		 
		def on_mouse_dragging(event)
			@mouse_x = event[:pos_x]
			@mouse_y = event[:pos_y]
			refresh
		end
	end
	 
	class Panel
		def on_init 
		end
	end
	class Image 
		def on_init 
		end
	end
	
	 
	 
	class Frame
		def on_init 
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
			@image = Image.new
			p @image
			 
		end
	end
end
	 
app = Rwx::App.new
