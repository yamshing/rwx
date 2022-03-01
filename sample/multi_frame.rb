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
			@sub_frame.set_size(1000,1000)
			@canvas = Canvas.new(@sub_frame)
			@canvas.set_size(1000,1000)
		end
		 
	end
	 
	class Canvas
		def on_init()
			@image = Image.new
			@image.capture_desktop()
			 
		end
		 
		def on_paint()
			@dc.draw_image(@image, 0, 0)
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
 
