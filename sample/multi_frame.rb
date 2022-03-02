module Rwx
	class Panel
		def on_init 
			 
			out_sizer = Sizer.new('box', 'vertical')
			row_sizer = Sizer.new('box', 'horizontal')
			button_1 = Button.new(self, label:'Click Here',cb_inst:self, cb_name:'on_button_click' )
			row_sizer.add_spacer(20)
			row_sizer.add(button_1)
			 
			out_sizer.add_spacer(20)
			out_sizer.add(row_sizer)
			add_sizer(out_sizer)
			 
		end
		 
		def on_button_click
			@sub_frame = SubFrame.new
			 
			 
			@canvas = Canvas.new(@sub_frame)
			@canvas.parent = @sub_frame
			#@canvas.set_size(1000,1000)
			 
			@sub_frame.set_fullscreen()
			 
		end
		 
	end
	 
	class Canvas
		attr_accessor :parent
		def on_init()
			@image = Image.new
			@image.capture_desktop()
			 
			@mouse_down_x = 0
			@mouse_down_y = 0
			 
		end
		 
		def on_paint()
			@dc.draw_image(@image, 0, 0)
		end
		 
		def on_mouse_down(event)
			@mouse_down_x = event[:pos_x]
			@mouse_down_y = event[:pos_y]
		end
		 
		def on_mouse_up(event)
			mouse_x = event[:pos_x]
			mouse_y = event[:pos_y]
			 
			capture_w = mouse_x - @mouse_down_x
			capture_h = mouse_y - @mouse_down_y
			 
			#p "#{@mouse_down_x}, #{@mouse_down_y} : #{capture_w}, #{capture_h}"
			 
			@ocr = Ocr.new
			 
			ocr_result = @ocr.get_ocr_result(@image, @mouse_down_x, @mouse_down_y, capture_w, capture_h)
			 
			p "ocr result #{ocr_result}"
			 
			@parent.close()
			 
		end
		 
	end
	 
	class SubFrame < Frame
		def on_init 
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
 
